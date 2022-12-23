"""
This script is used to train a LSTM model with multiple outputs. The target values are the motor current in different
axes
"""
import torch
from torch.utils.data import DataLoader
import pandas as pd
import numpy as np
import os
from config import data_rootpath, selected_feature_cols, label_cols, params_lstm, model_rootpath, std_train_feature_filename, \
    std_eval_feature_filename, statistics_json_filename
import time
import json

from util.model.AICoMSeqDataset import AICoMSeqDataset
from util.model.MTNFunctionWrapper import MTNFunctionWrapper
from model.MultiTaskLSTM import MultiTaskLSTM

from matplotlib import pyplot as plt

if __name__ == "__main__":

    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../../")
    print(f"Change the working directory: {os.getcwd()}")
    # assumed we have one machining process(Versuchsteil_Quadrant_7) for training, one machining process(Versuchsteil_Quadrant_8) for evaluation
    partname_train = "Versuchsteil_Quadrant_7"
    partname_eval = "Versuchsteil_Quadrant_8"
    results = {}


    pred_col_names = ['PredOrigin' + col_name for col_name in label_cols]
    true_col_names = ['TrueOrigin' + col_name for col_name in label_cols]


    batch_size = params_lstm['batch_size']
    learning_rate = params_lstm['learning_rate']
    epochs = params_lstm['epochs']

    lstm_hidden_dims = params_lstm['lstm_hidden_dims']
    share_hidden_dim = params_lstm['share_hidden_dim']
    sub_hidden_dims = params_lstm['sub_hidden_dims']
    window_size = lstm_hidden_dims
    lstm_layers_num = params_lstm['lstm_layers_num']

    model_root_folder = os.path.join(model_rootpath, 'LSTM')
    model_name = "multi_best.pth"
    model_path = os.path.join(model_root_folder, model_name)


    df_train = pd.read_csv(os.path.join(data_rootpath, partname_train, std_train_feature_filename), sep=",")
    df_eval = pd.read_csv(os.path.join(data_rootpath, partname_eval, std_eval_feature_filename), sep=",")
    df_padding_train = pd.read_csv(os.path.join(data_rootpath, partname_train, 'TrainPaddingData.csv'), sep=",")
    df_padding_eval = pd.read_csv(os.path.join(data_rootpath, partname_eval, 'EvalPaddingData.csv'), sep=",")
    # load statistic properties of train set
    with open(os.path.join(data_rootpath, partname_train, statistics_json_filename)) as inputfile:
        statistic_dict = json.load(inputfile)
    mean_train, std_train = statistic_dict['all']['mean'], statistic_dict['all']['std']

    myAICoMTrain = AICoMSeqDataset(df_train, df_padding_train, selected_feature_cols, window_size, output_cols=label_cols)
    # validation set is also the train set due to limited data source
    myAICoMEval = AICoMSeqDataset(df_train, df_padding_train, selected_feature_cols, window_size, output_cols=label_cols)
    myAICoMTest = AICoMSeqDataset(df_eval, df_padding_eval, selected_feature_cols, window_size, output_cols=label_cols)

    train_dataloader = DataLoader(myAICoMTrain, batch_size=batch_size, shuffle=True)
    eval_dataloader = DataLoader(myAICoMEval, batch_size=batch_size, shuffle=False)
    test_dataloader = DataLoader(myAICoMTest, batch_size=batch_size, shuffle=False)

    myMTLSTM = MultiTaskLSTM(input_dims=len(selected_feature_cols),
                          lstm_hidden_dims=lstm_hidden_dims,
                          share_hidden_dim=share_hidden_dim,
                          sub_hidden_dims=sub_hidden_dims,
                          lstm_layers_num=lstm_layers_num)


    optimizer = torch.optim.Adam(params=myMTLSTM.parameters(), lr=learning_rate)
    loss_fn = torch.nn.MSELoss()
    start_time = time.time()
    hist = MTNFunctionWrapper.train(
        dataloader_train=train_dataloader,
        dataloader_val=eval_dataloader,
        model=myMTLSTM,
        savepath=model_path,
        loss_fn=loss_fn,
        optimizer=optimizer,
        epochs=epochs)

    print(f"training time: {(time.time() - start_time) / 60.} min")

    # show the learning performance
    checkpoint = torch.load(model_path)
    print(f"Load the best trained model with mse {checkpoint['best_mse']}")
    myMTLSTM.load(checkpoint['model_state_dict'])
    # show the learning performance on train set and prediction result on test set
    for dtype, dataloader in zip(['train', 'validation'], [eval_dataloader, test_dataloader]):
        results[dtype] = {}
        start_time = time.time()
        y_pred, y_true = MTNFunctionWrapper.test(
            dataloader_eval=dataloader,
            model=myMTLSTM,
            loss_fn=loss_fn
        )
        print(f"prediction time on {dtype} set: {(time.time() - start_time)} s")
        results[dtype]['all'] = {}
        y_pred_np = np.array([y_pred[key] for key in y_pred.keys()]).T
        y_true_np = np.array([y_true[key] for key in y_true.keys()]).T

        assert len(y_pred.keys()) == len(label_cols), "key not match in prediction and true value"

        # recover prediction value to original scale
        y_pred_origin, y_true_origin = MTNFunctionWrapper.standard_to_origin(y_pred_mean=y_pred_np,
                                                                             y_true=y_true_np,
                                                                             mean=mean_train,
                                                                             std=std_train,
                                                                             label_cols=label_cols)
        results[dtype] = {}
        df_result = None
        if dtype == 'train':
            df_train[pred_col_names] = y_pred_origin.reshape(-1, len(label_cols))
            df_train[true_col_names] = y_true_origin.reshape(-1, len(label_cols))
            df_result = df_train
        else:
            df_eval[pred_col_names] = y_pred_origin.reshape(-1, len(label_cols))
            df_eval[true_col_names] = y_true_origin.reshape(-1, len(label_cols))
            df_result = df_eval
        # calculate metric score on train/test set and individual error in every used tool
        results[dtype] = MTNFunctionWrapper.evaluation(
            df=df_result,
            true_col_origin=true_col_names,
            pred_col_origin=pred_col_names,
            feature_cols=selected_feature_cols,
            label_cols=label_cols,
            results=results[dtype])
        # get start indices of different sub-processes
        opt_change_idx = df_result[df_result["ToolID"].diff() != 0].index.tolist()
        tool_id_seq = df_result[df_result["ToolID"].diff() != 0]['ToolID'].tolist()

        MTNFunctionWrapper.plot(y_true_origin=y_true_origin,
                                y_pred_mean_origin=y_pred_origin,
                                label_cols=label_cols,
                                results=results[dtype],
                                downsampling_size=10,
                                modelname='LSTM',
                                dtype=dtype,
                                taskid=opt_change_idx)

    with open('./model/train/multivariate_learning/result_lstm.json', 'w') as outputfile:
        json.dump(results, outputfile)

    # show learning curves
    fig, ax = plt.subplots()
    ax.tick_params(axis='both', labelsize=16)
    for k, v in hist.items():
        ax.plot(range(len(v)), v, label=k)

    ax.set_ylabel('RMSE', fontsize=22)
    ax.set_xlabel('epochs', fontsize=22)
    ax.set_title('Learning performance by LSTM', fontsize=22)
    plt.legend()
    plt.grid(True)
    plt.show()