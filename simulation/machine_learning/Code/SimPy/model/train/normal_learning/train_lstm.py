"""
This script is used to train a LSTM model. The learning task is train a model to predict the spindle
motor current
"""
import torch
from torch.utils.data import DataLoader
import pandas as pd
import numpy as np
import os
from config import data_rootpath, selected_feature_cols, model_rootpath, std_eval_feature_filename, std_train_feature_filename, statistics_json_filename
import time
import json

from util.model.AICoMSeqDataset import AICoMSeqDataset
from util.model.NNFunctionWrapper import NNFunctionWrapper
from model.LSTMRegression import LSTMRegression

from matplotlib import pyplot as plt

if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../../")
    print(f"Change the working directory: {os.getcwd()}")

    # assumed we have one machining process(Versuchsteil_Quadrant_7) for training, one machining process(Versuchsteil_Quadrant_8) for evaluation
    partname_train = "Versuchsteil_Quadrant_7"
    partname_eval = "Versuchsteil_Quadrant_8"
    results = {}
    # hard coded only for demonstration and experiment
    label_cols = ["S1ActTrq"]
    pred_col_names = ['PredOrigin_' + col_name for col_name in label_cols]
    true_col_names = ['TrueOrigin_' + col_name for col_name in label_cols]

    start_time = time.time()
    # hyperparameter
    batch_size = 64
    learning_rate = 1e-3
    epochs = 50

    hidden_dims = 10
    window_size = hidden_dims
    fc_dims = [32, 64, 32]
    lstm_layers_num = 1

    model_root_folder = os.path.join(model_rootpath, 'LSTM')
    model_name = "base_best.pth"
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

    train_dataloader = DataLoader(myAICoMTrain, batch_size=64, shuffle=True)
    eval_dataloader = DataLoader(myAICoMEval, batch_size=64, shuffle=False)
    test_dataloader = DataLoader(myAICoMTest, batch_size=64, shuffle=False)

    myLSTM = LSTMRegression(input_dims=len(selected_feature_cols),
                            hidden_dims=hidden_dims,
                            output_dims=len(label_cols),
                            lstm_layers_num=lstm_layers_num,
                            fc_dims=fc_dims
                            )
    optimizer = torch.optim.Adam(params=myLSTM.parameters(), lr=learning_rate)
    loss_fn = torch.nn.MSELoss()

    hist = NNFunctionWrapper.train(
            dataloader_train=train_dataloader,
            dataloader_val=eval_dataloader,
            model=myLSTM,
            savepath=model_path,
            loss_fn=loss_fn,
            optimizer=optimizer,
            epochs=epochs)
    print(f"training time: {(time.time() - start_time) / 60.} min")

    # show the learning performance

    # load model
    checkpoint = torch.load(model_path)
    print(f"Load the best trained model with mse {checkpoint['best_mse']}")
    myLSTM.load(checkpoint['model_state_dict'])

    # show the learning performance on train set and prediction result on test set
    for dtype, dataloader in zip(['train', 'validation'], [eval_dataloader, test_dataloader]):
        start_time = time.time()
        y_pred, y_true = NNFunctionWrapper.test(
            dataloader_eval=dataloader,
            model=myLSTM,
            loss_fn=loss_fn
        )
        print(f"evaluation time: {(time.time() - start_time) } s")
        y_pred_np = np.array(y_pred)
        y_true_np = np.array(y_true)

        # recover prediction value to original scale
        y_pred_origin, y_true_origin = NNFunctionWrapper.standard_to_origin(
            y_pred_mean=y_pred_np,
            y_true=y_true_np,
            mean=mean_train,
            std=std_train,
            label_cols=label_cols
        )

        results[dtype] = {}
        df_result = None
        if dtype == 'train':
            df_train[pred_col_names] = y_pred_origin.reshape(-1, 1)
            df_train[true_col_names] = y_true_origin.reshape(-1, 1)
            df_result = df_train
        else:
            df_eval[pred_col_names] = y_pred_origin.reshape(-1, 1)
            df_eval[true_col_names] = y_true_origin.reshape(-1, 1)
            df_result = df_eval
        # get start indices of different sub-processes
        opt_change_idx = df_result[df_result["ToolID"].diff() != 0].index.tolist()
        # calculate metric score on train/test set and individual error in every used tool
        results[dtype] = NNFunctionWrapper.evaluation(
            df=df_result,
            true_col_origin=true_col_names,
            pred_col_origin=pred_col_names,
            feature_cols=selected_feature_cols,
            label_cols=label_cols,
            results=results[dtype])

        with open('./model/train/normal_learning/result_lstm.json', 'w') as outputfile:
            json.dump(results, outputfile)

        NNFunctionWrapper.plot(y_true_origin=y_true_origin.reshape(-1, 1),
                               y_pred_mean_origin=y_pred_origin.reshape(-1, 1),
                               label_cols=label_cols,
                               results=results[dtype],
                               downsampling_size=10,
                               modelname='LSTM',
                               dtype=dtype,
                               taskid=opt_change_idx)

    # show learning curve
    fig3, ax3 = plt.subplots()
    ax3.plot(range(1, len(hist)+1, 1), hist)
    ax3.set_xlabel("epochs", fontsize=22)
    ax3.set_ylabel("RMSE", fontsize=22)
    ax3.set_title("learning performance over all epochs (LSTM)", fontsize=22)
    ax3.tick_params(axis='both', labelsize=16)
    plt.grid(True)
    plt.show()
