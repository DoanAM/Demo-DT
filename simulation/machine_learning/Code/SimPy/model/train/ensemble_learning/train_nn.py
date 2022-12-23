import torch
from torch.utils.data import DataLoader
import pandas as pd
import numpy as np
import os
import json
from config import data_rootpath
import time

from util.model.AICoMDataset import AICoMDataset
from util.model.NNFunctionWrapper import NNFunctionWrapper
from model.NeuralNetwork import NeuralNetwork

from matplotlib import pyplot as plt

if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../../")
    print(f"Change the working directory: {os.getcwd()}")
    partname = "Versuchsteil_Quadrant_test"
    results = {}

    df_train = pd.read_csv(os.path.join(data_rootpath, partname, "TrainDataNorm.csv"), sep=",")
    with open(os.path.join(data_rootpath, partname, "statistic.json")) as inputfile:
        statistic_dict = json.load(inputfile)
    selected_feature_cols = ["S1Actrev", "Actfeed", "S1ActAccel", "XCurrAccel", "YCurrAccel", "ZCurrAccel", "Area",
                             "Width", "Removal_Volume", "Angle_Mean", "ChipThickness"]
    label_cols = ["S1ActTrq"]

    ensemble_models = {}
    train_error = []
    train_times = []

    # hyperparameter
    batch_size = 64
    learning_rate = 1e-3
    epochs = 20
    hidden_dims = [32, 64, 128, 64, 32]

    model_root_folder = "./model/save/NN"

    df_result = pd.DataFrame(
        columns=['Timestamp', 'S1ActTrq_pred_origin', 'S1ActTrq_origin'])

    for toolid, df_train_sub in df_train.groupby(by=["ToolID"]):
        this_timestamp = df_train_sub['Timestamp'].to_numpy()
        myAICoMTrain = AICoMDataset(df_train_sub, selected_feature_cols, label_cols)
        myAICoMTest = AICoMDataset(df_train_sub, selected_feature_cols, label_cols)

        train_dataloader = DataLoader(myAICoMTrain, batch_size=64, shuffle=True)
        test_dataloader = DataLoader(myAICoMTest, batch_size=64, shuffle=False)

        ensemble_models[str(toolid)] = NeuralNetwork(input_dims=len(selected_feature_cols), hidden_dims=hidden_dims, output_dims=len(label_cols))
        optimizer = torch.optim.Adam(params=ensemble_models[str(toolid)].parameters(), lr=learning_rate)
        loss_fn = torch.nn.MSELoss()
        start_time = time.time()
        # train
        NNFunctionWrapper.train(
            dataloader_train=train_dataloader,
            dataloader_val=test_dataloader,
            model=ensemble_models[str(toolid)],
            loss_fn=loss_fn,
            optimizer=optimizer,
            epochs=epochs
        )
        train_times.append((time.time() - start_time) / 60.)
        this_model_path = os.path.join(model_root_folder, 'base_'+str(toolid)+'.pth')
        ensemble_models[str(toolid)].save(this_model_path)

        # evaluate
        ensemble_models[str(toolid)].load(this_model_path)

        y_pred, y_true = NNFunctionWrapper.test(
            dataloader_test=test_dataloader,
            model=ensemble_models[str(toolid)],
            loss_fn=loss_fn
        )

        this_mean, this_std = statistic_dict[str(toolid)]['mean']['S1ActTrq'], statistic_dict[str(toolid)]['std']['S1ActTrq']
        y_pred_np = np.array(y_pred)
        y_true_np = np.array(y_true)
        y_pred_origin = y_pred_np * this_std + this_mean
        y_train_origin = y_true_np * this_std + this_mean

        df_result = pd.concat(
            [df_result,
             pd.DataFrame(np.hstack((this_timestamp.reshape(-1, 1),
                                     y_pred_origin.reshape(-1, 1),
                                     y_train_origin.reshape(-1, 1))), columns=df_result.columns)],
            ignore_index=True)
        this_rmse = np.sqrt(((y_pred_origin - y_train_origin) ** 2).mean())
        print(f"rmse for tool {toolid} is: {this_rmse}")
        results[str(toolid)] = this_rmse
        train_error.append(np.sum((y_pred_origin - y_train_origin) ** 2))


    df_result.sort_values(by=['Timestamp'], inplace=True)

    df_train = df_train.merge(df_result, on="Timestamp", how="left")

    # sanity check
    if df_train[
        ['S1ActTrq_pred_origin', 'S1ActTrq_origin']].isnull().values.any():
        print("WARNING: data mission in inference data")

    rmse_all = np.sqrt(sum(train_error) / len(df_train))
    print(f"rmse for the complete process of {partname} is {rmse_all}")
    print(f"computation time {sum(train_times)} min")

    results['all'] = rmse_all

    with open('./model/train/normal_learning/result_nn.json', 'w') as outputfile:
        json.dump(results, outputfile)

    fig, ax = plt.subplots()
    ax.scatter(range(len(df_train['S1ActTrq_origin'][::50])), df_train['S1ActTrq_origin'][::50], s=10, alpha=0.5,
                label="observation")
    ax.plot(range(len(df_train['S1ActTrq_pred_origin'][::50])), df_train['S1ActTrq_pred_origin'][::50], color='red',
             label="predict mean")
    ax.set_title(f"Learning performance by neural network (down sampling 1/50)")
    ax.set_xlabel("cycle times")
    ax.set_ylabel("Current (A)")
    ax.legend()

    fig2, ax2 = plt.subplots()
    tool_ids, rmse_tool = zip(*(results.items()))
    ax2.plot(tool_ids[:-1], rmse_tool[:-1], marker='o')
    ax2.set_xlabel("tool id")
    ax2.set_ylabel("RMSE (A)")
    ax2.set_title(f"Individual learning performance among used tools (neural network)")
    plt.grid(True)

    plt.show()


