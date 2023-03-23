import sys

from .TwinCATSim import TwinCATSim
from .mwCamSim import mwCamSim
from .util.auxiliary.TwinCatDataHandler import TwinCatDataHandler
from .util.data.FeaturePreprocess import FeaturePreprocess
from .config import data_rootpath, bounds, feature_cols, selected_feature_cols, label_cols, params_lstm, \
    test_feature_filename, std_test_feature_filename, std_padding_test_feature_filename, pred_filename

# model
from .util.model.MTNFunctionWrapper import MTNFunctionWrapper
from .model.MultiTaskLSTM import MultiTaskLSTM
from .util.model.AICoMSeqDataset import AICoMSeqDataset

# visualization
from .evaluation.EvalSim import EvalSim

import time
import json
import os
import numpy as np

import torch
from torch.utils.data import DataLoader
from matplotlib import pyplot as plt

"""
This function could be triggered by the offline process planning 
"""


def SimHandler(foldername, mwdll, precision, kernelKey='abc', simType='vnck'):

    #######################
    #       VNCK sim      #
    #######################

    start_time_vnck = time.time()
    # init vnck kernel
    twincat_wrapper = TwinCATSim(kernelKey)

    # cnc simulation from twincat
    twincat_wrapper.read_file(foldername)
    twincat_wrapper.warmup()
    twincat_wrapper.sim()

    # init twincat data handler to calibrate the coordinates
    myTCDH = TwinCatDataHandler(foldername)
    myTCDH.calibrate()

    print(
        f"*  VNCK simulation running time: \033[1;35m{(time.time() - start_time_vnck)} s\033[0m")
    time.sleep(2)

    #######################
    #      cam sim        #
    #######################

    start_time_mw = time.time()
    mwcam_wrapper = mwCamSim(mwdll, precision, simType)
    mwcam_wrapper.load_file(foldername)
    mwcam_wrapper.set_stock(bounds)
    mwcam_wrapper.load_toolset()

    # set visualization as false to acceleration the simulation and set write trace true to record the analysis
    mwcam_wrapper.sim(False, True)
    print(
        f"*  MW CAM simulation running time: \033[1;35m{(time.time() - start_time_mw) / 60.} min\033[0m")

    ######################
    #    Preprocess      #
    ######################

    start_time_pp = time.time()
    myPrePro = FeaturePreprocess(foldername,  simType)
    df_raw = myPrePro.get_df().reset_index()
    myPrePro.compute_acceleration()
    myPrePro.numeric_converter("Angles")
    myPrePro.sum_angles("Angles")
    myPrePro.design_features()
    df_complete = myPrePro.get_df()
    myPrePro.drop_oob(bounds)
    df_data = myPrePro.get_df()
    df_data, df_padding = myPrePro.padding(
        df_data.copy(deep=True), df_complete.copy(deep=True))
    df_data = myPrePro.split(df=df_data)

    # ToDo: for further application, the function should know where to find the corresponding data for the standardization (here supposed quadrant 7 as train set used before)
    # load statistic parameter
    mean_train = None
    std_train = None

    # ToDo: hard coded
    with open(os.path.join(data_rootpath, "Versuchsteil_Quadrant_7", "statistic.json")) as inputfile:
        statistic_dict = json.load(inputfile)

    try:
        mean_train, std_train = statistic_dict['all']['mean'], statistic_dict['all']['std']
    except KeyError:
        print("No statistic value in the loaded file, please check")
        sys.exit(-1)

    df_norm, _ = myPrePro.standardization(df_data.copy(deep=True),
                                          feature_cols,
                                          statistic=statistic_dict)
    df_padding_norm = df_norm.loc[df_padding.index]
    df_norm.drop(df_padding.index, inplace=True)
    df_data.to_csv(os.path.join(data_rootpath, foldername,
                   test_feature_filename), index=True)
    df_norm.to_csv(os.path.join(data_rootpath, foldername,
                   std_test_feature_filename), index=True)
    df_padding_norm.to_csv(os.path.join(
        data_rootpath, foldername, std_padding_test_feature_filename), index=True)
    print(
        f"*  Preprocess running time: \033[1;35m{(time.time() - start_time_pp) } s\033[0m")

    #######################
    #     Inference       #
    #######################
    start_time_infer = time.time()
    pred_col_names = ['PredOrigin' + col_name for col_name in label_cols]
    df_test = df_norm.reset_index()
    df_padding_test = df_padding_norm.reset_index()
    myAICoMTest = AICoMSeqDataset(
        df_test, df_padding_test, selected_feature_cols, params_lstm['window_size'])
    test_dataloader = DataLoader(
        myAICoMTest, batch_size=params_lstm['batch_size'], shuffle=False)
    myMTLSTM = MultiTaskLSTM(input_dims=len(selected_feature_cols),
                             lstm_hidden_dims=params_lstm['lstm_hidden_dims'],
                             share_hidden_dim=params_lstm['share_hidden_dim'],
                             sub_hidden_dims=params_lstm['sub_hidden_dims'],
                             lstm_layers_num=params_lstm['lstm_layers_num'])

    checkpoint = torch.load(params_lstm['modelpath'])
    print(
        f"[\033[1;32mOK\033[0m] Load the best trained model with mse {checkpoint['best_mse']}")
    myMTLSTM.load(checkpoint['model_state_dict'])

    y_pred = MTNFunctionWrapper.predict(
        dataloader_test=test_dataloader,
        model=myMTLSTM)
    y_pred_np = np.array([y_pred[key] for key in y_pred.keys()]).T

    y_pred_origin = MTNFunctionWrapper.standard_to_origin(y_pred_mean=y_pred_np,
                                                          y_true=None,
                                                          mean=mean_train,
                                                          std=std_train,
                                                          label_cols=label_cols)

    df_test[pred_col_names] = y_pred_origin
    df_test.to_csv(os.path.join(data_rootpath, foldername, pred_filename))

    # create a drive data for visualization:

    df_drive_sim = df_raw.merge(df_test, on="Timestamp", how='left')
    df_drive_sim = df_drive_sim[['Timestamp', 'PredOriginS1ActTrq']]
    df_drive_sim.fillna(0, inplace=True)
    print(
        f"*  Prediction running time: \033[1;35m{(time.time() - start_time_infer) } s\033[0m")

    # if you want to see the static graph, please uncomment following lines
    # for i, label in enumerate(label_cols):
    #fig, ax = plt.subplots()
    #ax.tick_params(axis='both', labelsize=16)
    #ax.plot(range(len(y_pred_origin[::10, i])), y_pred_origin[::10, i], color='blue')
    #ax.set_xlabel("cycle times (ms)", fontsize=22)
    #ax.set_ylabel(f"{label} (A)", fontsize=22)
    #ax.set_title(f"Prediction of {label} by LSTM model", fontsize=22)
    # plt.show()

    del mwcam_wrapper
    """
    #######################
    #    Visualization    #
    #######################
    myES = EvalSim('vnck')
    myES.load_file(foldername)
    myES.set_stock(bounds)
    myES.load_toolset()
    myES.sim(df_drive_sim)
    """


if __name__ == "__main__":

    SimHandler('Versuchsteil_Quadrant_test')
