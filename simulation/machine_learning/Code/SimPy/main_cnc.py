import matplotlib.pyplot as plt

from util.data.DataHandler import DataHandler
from util.data.FeaturePreprocess import FeaturePreprocess
from mwCamSim import mwCamSim

from config import data_rootpath, bounds, feature_cols, selected_feature_cols, label_cols, params_lstm, \
    train_feature_filename, std_train_feature_filename, std_padding_train_feature_filename, statistics_json_filename

# model
from model.MultiTaskLSTM import MultiTaskLSTM
from util.model.AICoMSeqDataset import AICoMSeqDataset
from util.model.MTNFunctionWrapper import MTNFunctionWrapper
import torch
from torch.utils.data import DataLoader


import pandas as pd
import numpy as np
import os
import time
import json

def CNCHandler(foldername, simType="real"):
    print(f"Start Model Training process")

    #######################
    #  raw data handling  #
    #######################
    # load wcs file
    df_wcs = pd.read_csv(os.path.join(data_rootpath, foldername, 'WcsData.csv'), sep=",", index_col='Timestamp')
    df_wcs.drop(['isActive'], axis=1, inplace=True)
    df_wcs.drop(
        df_wcs[(df_wcs["X"] == 0) | (df_wcs["Y"] == 0) | (df_wcs["Z"] == 0) | (df_wcs["gamma"] == 0)].index,
        inplace=True)

    print(f'*  Start data processing on \033[1;35mreal CNC machine\033[0m, current workpiece: \033[1;35m{foldername}\033[0m')

    start_time_dh = time.time()
    myDH = DataHandler(foldername)
    myDH.drop_duplicates()
    myDH.sort()
    myDH.truncate()
    myDH.dropna()
    myDH.calibrate(df_wcs=df_wcs)
    myDH.compute_tool_id()
    myDH.save()
    print(f"*  Data handling running time: \033[1;35m{(time.time() - start_time_dh) } s\033[0m")

    #######################
    #      cam sim        #
    #######################

    start_time_mw = time.time()
    mwcam_wrapper = mwCamSim(simType)
    mwcam_wrapper.load_file(foldername)
    mwcam_wrapper.set_stock(bounds)
    mwcam_wrapper.load_toolset()

    # set visualization as true to pop up animation window
    mwcam_wrapper.sim(False, True)

    print(f"* MW CAM simulation running time: \033[1;35m{(time.time() - start_time_mw) / 60.} min\033[0m")

    #######################
    #     Preprocess      #
    #######################

    start_time_pp = time.time()
    df_drive = pd.read_csv(os.path.join(data_rootpath, foldername, 'DriveData.csv'), sep=",", index_col='Timestamp')
    # sanity check:
    if df_drive.isnull().values.any():
        print(f"\033[1;33mWARNING: exist drive data has none type values in following rows \033[0m")
        none_rows_bool = df_drive.isnull().values.any(1)
        print(df_drive[none_rows_bool])
        df_drive = df_drive[~none_rows_bool]
        print(f"[\033[1;32mOK\033[0m]  delete none type value in \033[1;35mdrive data\033[0m")
    if df_drive.index.duplicated().any():
        print(f"\033[1;33mWARNING: exist drive data has duplicate indices in following rows: \033[0m")
        dupl_rows_bool = df_drive.index.duplicated()
        print(df_drive[dupl_rows_bool])
        df_drive = df_drive[~dupl_rows_bool]
        print(f"[\033[1;32mOK\033[0m]  delete duplicated rows in \033[1;35mdrive data\033[0m")

    df_drive = df_drive[label_cols]

    myPrePro = FeaturePreprocess(foldername, simType)
    myPrePro.integrate(df_drive)
    myPrePro.compute_acceleration()
    myPrePro.numeric_converter("Angles")
    myPrePro.sum_angles("Angles")
    myPrePro.design_features()
    df_complete = myPrePro.get_df()
    myPrePro.drop_oob(bounds)
    df_data = myPrePro.get_df()
    df_data, df_padding = myPrePro.padding(df_data.copy(deep=True), df_complete.copy(deep=True))
    df_data = myPrePro.split(df=df_data)
    df_norm, statistic_json = myPrePro.standardization(df_data.copy(deep=True), feature_cols + label_cols)
    df_padding_norm = df_norm.loc[df_padding.index]
    df_norm.drop(df_padding.index, inplace=True)
    df_data.to_csv(os.path.join(data_rootpath, foldername, train_feature_filename), index=True)
    df_norm.to_csv(os.path.join(data_rootpath, foldername, std_train_feature_filename), index=True)
    df_padding_norm.to_csv(os.path.join(data_rootpath, foldername, std_padding_train_feature_filename), index=True)

    with open(os.path.join(data_rootpath, foldername, statistics_json_filename), 'w') as outputfile:
        json.dump(statistic_json, outputfile)
    print(f"*  Preprocess running time: \033[1;35m{(time.time() - start_time_pp)} s\033[0m")

    #######################
    #      Training       #
    #######################
    start_time_train = time.time()
    pred_col_names = ['PredOrigin' + col_name for col_name in label_cols]
    true_col_names = ['TrueOrigin' + col_name for col_name in label_cols]
    df_train = df_norm.reset_index()
    df_padding_train = df_padding_norm.reset_index()
    myAICoMTrain = AICoMSeqDataset(df_train, df_padding_train, selected_feature_cols, params_lstm['window_size'], output_cols=label_cols)
    myAICoMEval = AICoMSeqDataset(df_train, df_padding_train, selected_feature_cols, params_lstm['window_size'], output_cols=label_cols)
    train_dataloader = DataLoader(myAICoMTrain, batch_size=params_lstm['batch_size'], shuffle=True)
    eval_dataloader = DataLoader(myAICoMEval, batch_size=params_lstm['batch_size'], shuffle=False)
    myMTLSTM = MultiTaskLSTM(input_dims=len(selected_feature_cols),
                             lstm_hidden_dims=params_lstm['lstm_hidden_dims'],
                             share_hidden_dim=params_lstm['share_hidden_dim'],
                             sub_hidden_dims=params_lstm['sub_hidden_dims'],
                             lstm_layers_num=params_lstm['lstm_layers_num'])

    mean_train, std_train = statistic_json['all']['mean'], statistic_json['all']['std']
    loss_fn = torch.nn.MSELoss()
    optimizer = torch.optim.Adam(params=myMTLSTM.parameters(), lr=params_lstm['learning_rate'])


    # ToDo: for the continual learning concept. the pre-trained model should be loaded before starting a new learning process
    hist = MTNFunctionWrapper.train(
        dataloader_train=train_dataloader,
        dataloader_val=eval_dataloader,
        model=myMTLSTM,
        savepath=params_lstm['modelpath'],
        loss_fn=loss_fn,
        optimizer=optimizer,
        epochs=params_lstm['epochs'])

    # show the learning performance
    y_pred, y_true = MTNFunctionWrapper.test(
        dataloader_eval=eval_dataloader,
        model=myMTLSTM,
        loss_fn=loss_fn)
    y_pred_np = np.array([y_pred[key] for key in y_pred.keys()]).T
    y_true_np = np.array([y_true[key] for key in y_true.keys()]).T

    assert len(y_pred.keys()) == len(label_cols), "key not match in prediction and true value"

    # recover value to original scale
    y_pred_origin, y_true_origin = MTNFunctionWrapper.standard_to_origin(y_pred_mean=y_pred_np,
                                                                         y_true=y_true_np,
                                                                         mean=mean_train,
                                                                         std=std_train,
                                                                         label_cols=label_cols)

    df_train[pred_col_names] = y_pred_origin
    df_train[true_col_names] = y_true_origin

    # evaluate the learning performance
    results = {}
    results = MTNFunctionWrapper.evaluation(
        df=df_train,
        true_col_origin=true_col_names,
        pred_col_origin=pred_col_names,
        feature_cols=selected_feature_cols,
        label_cols=label_cols,
        results=results)

    # get tool change index
    opt_change_idx = df_train[df_train["ToolID"].diff() != 0].index.tolist()

    # show the learning results
    print(f"* Model learning running time: \033[1;35m{(time.time() - start_time_train) / 60.} min\033[0m")
    # TODO: suppress the pop up window in the real application
    MTNFunctionWrapper.plot(y_true_origin=y_true_origin,
                            y_pred_mean_origin=y_pred_origin,
                            label_cols=label_cols,
                            results=results,
                            downsampling_size=10,
                            modelname='LSTM',
                            dtype='train',
                            taskid=opt_change_idx)

    fig, ax = plt.subplots()
    for k, v in hist.items():
        ax.plot(range(len(v)), v, label=k)

    ax.set_xlabel('RMSE', fontsize=16)
    ax.set_ylabel('epochs', fontsize=16)
    ax.set_title('Learning performance by LSTM', fontsize=20)
    plt.legend()

    # clean up
    del mwcam_wrapper

if __name__ == '__main__':

    CNCHandler('Versuchsteil_Quadrant_test')





