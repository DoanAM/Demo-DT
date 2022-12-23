"""
This script is used to train a multilayer perception model with multiple outputs. The target values are the motor current in different
axes
"""
import torch
from torch.utils.data import DataLoader
import pandas as pd
import numpy as np
import os
from config import data_rootpath, selected_feature_cols, label_cols, std_train_feature_filename, std_eval_feature_filename, \
    statistics_json_filename, model_rootpath
import time
import json

from util.model.AICoMDataset import AICoMDataset
from util.model.MTNFunctionWrapper import MTNFunctionWrapper
from model.MultitaskNet import MultitaskNet

from matplotlib import pyplot as plt

if __name__ == "__main__":

    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../../")
    print(f"Change the working directory: {os.getcwd()}")
    start_time = time.time()
    partname_train = "Versuchsteil_Quadrant_7"
    partname_eval = "Versuchsteil_Quadrant_8"
    results = {}


    pred_col_names = ['PredOrigin' + col_name for col_name in label_cols]
    true_col_names = ['TrueOrigin' + col_name for col_name in label_cols]

    # hard coded only for demonstration and experiment
    # hyperparameter
    batch_size = 64
    learning_rate = 1e-3
    epochs = 50
    share_dims = [32, 64, 128]
    sub_dims = [128, 64, 32]

    model_root_folder = "./model/save/NN"
    model_name = "multi_best.pth"
    model_path = os.path.join(model_root_folder, model_name)

    df_train = pd.read_csv(os.path.join(data_rootpath, partname_train, std_train_feature_filename), sep=",")
    df_eval = pd.read_csv(os.path.join(data_rootpath, partname_eval, std_eval_feature_filename), sep=",")
    # load statistic properties of train set
    with open(os.path.join(data_rootpath, partname_train, statistics_json_filename)) as inputfile:
        statistic_dict = json.load(inputfile)
    mean_train, std_train = statistic_dict['all']['mean'], statistic_dict['all']['std']

    myAICoMTrain = AICoMDataset(df_train, selected_feature_cols, output_cols=label_cols)
    myAICoMEval = AICoMDataset(df_train, selected_feature_cols, output_cols=label_cols)
    myAICoMTest = AICoMDataset(df_eval, selected_feature_cols, output_cols=label_cols)

    train_dataloader = DataLoader(myAICoMTrain, batch_size=64, shuffle=True)
    eval_dataloader = DataLoader(myAICoMEval, batch_size=64, shuffle=False)
    test_dataloader = DataLoader(myAICoMTest, batch_size=64, shuffle=False)

    myMTN = MultitaskNet(input_dims=len(selected_feature_cols), share_hidden_dims=share_dims, sub_hidden_dims=sub_dims)
    optimizer = torch.optim.Adam(params=myMTN.parameters(), lr=learning_rate)
    loss_fn = torch.nn.MSELoss()

    # model training
    hist = MTNFunctionWrapper.train(
        dataloader_train=train_dataloader,
        dataloader_val=eval_dataloader,
        model=myMTN,
        savepath=model_path,
        loss_fn=loss_fn,
        optimizer=optimizer,
        epochs=epochs)

    print(f"training time: {(time.time() - start_time) / 60.} min")

    # show the learning performance
    checkpoint = torch.load(model_path)
    print(f"Load the best trained model with mse {checkpoint['best_mse']}")
    myMTN.load(checkpoint['model_state_dict'])
    # show the learning performance on train set and prediction result on test set
    for dtype, dataloader in zip(['train', 'validation'], [eval_dataloader, test_dataloader]):
        results[dtype] = {}
        start_time = time.time()
        y_pred, y_true = MTNFunctionWrapper.test(
            dataloader_eval=dataloader,
            model=myMTN,
            loss_fn=loss_fn
        )
        print(f"prediction time on {dtype} set: {(time.time() - start_time)} s")
        results[dtype]['all'] = {}

        y_pred_np = np.array([y_pred[key] for key in y_pred.keys()]).T
        y_true_np = np.array([y_true[key] for key in y_true.keys()]).T

        assert len(y_pred.keys()) == len(label_cols), "key not match in prediction and true value"

        # transform the standardized value to origin scale
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

        # calculate metric score on train/test set
        results[dtype] = MTNFunctionWrapper.evaluation(
            df=df_result,
            true_col_origin=true_col_names,
            pred_col_origin=pred_col_names,
            feature_cols=selected_feature_cols,
            label_cols=label_cols,
            results=results[dtype])

        # get start indices of different sub-processes
        opt_change_idx = df_result[df_result["ToolID"].diff() != 0].index.tolist()

        MTNFunctionWrapper.plot(y_true_origin=y_true_origin,
                                y_pred_mean_origin=y_pred_origin,
                                label_cols=label_cols,
                                results=results[dtype],
                                downsampling_size=10,
                                modelname='MLP',
                                dtype=dtype,
                                taskid=opt_change_idx
                                )
    with open('./model/train/multivariate_learning/result_nn.json', 'w') as outputfile:
        json.dump(results, outputfile)

    # show the learning curves
    fig, ax = plt.subplots()
    for k, v in hist.items():
        ax.plot(range(len(v)), v, label=k)

    ax.tick_params(axis='both', labelsize=16)
    ax.set_ylabel('RMSE', fontsize=22)
    ax.set_xlabel('epochs', fontsize=22)
    ax.set_title('Learning performance by MLP', fontsize=22)
    plt.legend()
    plt.grid(True)
    plt.show()


