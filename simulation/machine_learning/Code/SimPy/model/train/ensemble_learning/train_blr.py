import pandas as pd
import numpy as np
import os
import json
from config import data_rootpath
import time
from matplotlib import pyplot as plt
import pickle

# model
from model.LinearRegression import LinearRegression
from util.model.RegFunctionWrapper import RegFunctionWrapper

if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../../")
    print(f"Change the working directory: {os.getcwd()}")

    partname_train = "Versuchsteil_Quadrant_7"
    partname_eval = "Versuchsteil_Quadrant_8"
    iters = 100
    results_train = {}
    results_eval = {}
    model_root_folder = "./model/save/BLR"
    model_name = "base_"

    df_train = pd.read_csv(os.path.join(data_rootpath, partname_train, "TrainDataNorm.csv"), sep=",")
    df_eval = pd.read_csv(os.path.join(data_rootpath, partname_eval, "EvalDataNorm.csv"), sep=",")
    df_eval.sort_values(by=["Timestamp"], inplace=True)

    with open(os.path.join(data_rootpath, partname_train, "statistic.json")) as inputfile:
        statistic_dict = json.load(inputfile)

    selected_feature_cols = ["S1Actrev", "Actfeed", "S1ActAccel", "Area", "Width", "Removal_Volume", "Angle_Mean"]
    label_cols = ["S1ActTrq"]
    ensemble_models = {}
    train_error = []
    train_times = []
    df_result = pd.DataFrame(columns=['Timestamp', 'S1ActTrq_pred_mean', 'S1ActTrq_pred_upper', 'S1ActTrq_pred_lower', 'S1ActTrq_origin'])
    start_time = time.time()
    for toolid, df_train_sub in df_train.groupby(by=["ToolID"]):
        print(f"Starting train set with tool {toolid}")
        X_train = df_train_sub[selected_feature_cols].to_numpy()
        y_train = df_train_sub[label_cols].to_numpy().ravel()
        this_timestamp = df_train_sub['Timestamp'].to_numpy()

        this_blrmodel = LinearRegression("base", iters)
        start_time = time.time()
        this_blrmodel.fit(X_train, y_train)
        train_times.append((time.time() - start_time) / 60.)

        ensemble_models[str(toolid)] = this_blrmodel

        #this_blrmodel.save(os.path.join(model_root_folder, model_name + str(toolid) + '.sav'))

        #show learning performance:
        y_pred_mean_train, y_pred_std_train = ensemble_models[str(toolid)].predict(X_train)
        this_mean_train, this_std_train = statistic_dict[str(toolid)]['mean'], statistic_dict[str(toolid)]['std']
        """
        y_pred_mean_origin = y_pred_mean * this_std + this_mean
        y_pred_upper_origin = (y_pred_mean + y_pred_std) * this_std + this_mean
        y_pred_lower_origin = (y_pred_mean - y_pred_std) * this_std + this_mean
        y_train_origin = y_train * this_std + this_mean
        """
        y_pred_mean_train_origin, y_pred_lower_train_origin, y_pred_upper_train_origin, y_train_origin = \
            RegFunctionWrapper.standard_to_origin(y_pred_mean_train.reshape(-1, len(label_cols)),
                                                  y_train.reshape(-1, len(label_cols)),
                                                  this_mean_train,
                                                  this_std_train,
                                                  label_cols,
                                                  y_pred_std=y_pred_std_train.reshape(-1, len(label_cols)), )

        df_result = pd.concat(
            [df_result,
             pd.DataFrame(np.hstack((this_timestamp.reshape(-1, 1),
                                     y_pred_mean_train_origin.reshape(-1, 1),
                                     y_pred_upper_train_origin.reshape(-1, 1),
                                     y_pred_lower_train_origin.reshape(-1, 1),
                                     y_train_origin.reshape(-1, 1))), columns=df_result.columns)],
            ignore_index=True)
        """
        fig, ax = plt.subplots()
        ax.scatter(range(len(y_train_origin)), y_train_origin, s=10, alpha=0.5, label="observation")
        ax.plot(range(len(y_pred_mean)), y_pred_mean_origin, color='red', label="predict mean")
        ax.fill_between(range(len(y_pred_mean_origin)), y_pred_lower_origin, y_pred_upper_origin,
                        color='pink', alpha=0.5, label='predict std')
        ax.set_title(f"Inference by Bayesian Linear Regression (Tool: {id})")
        ax.set_xlabel("cycle times")
        ax.set_ylabel("Current (A)")
        ax.legend()
        """
        this_rmse = np.sqrt(((y_pred_mean_train_origin - y_train_origin)**2).mean(axis=0))
        print(f"rmse for tool {toolid} is: {this_rmse}")
        results_train[str(toolid)] = this_rmse[0]
        train_error.append(np.sum((y_pred_mean_train_origin - y_train_origin)**2))

    df_result.sort_values(by=['Timestamp'], inplace=True)

    df_train = df_train.merge(df_result, on="Timestamp", how="left")

    # sanity check
    if df_train[['S1ActTrq_pred_mean', 'S1ActTrq_pred_lower', 'S1ActTrq_pred_upper', 'S1ActTrq_origin']].isnull().values.any():
        print("WARNING: data mission in inference data")
    rmse_all = np.sqrt(sum(train_error) / len(df_train))
    print(f"rmse for the complete process of {partname_train} is {rmse_all}")
    print(f"computation time {sum(train_times)} min")

    results_train['all'] = rmse_all

    with open('./model/train/ensemble_learning/result_blr_train.json', 'w') as outputfile:
        json.dump(results_train, outputfile)

    pickle.dump(ensemble_models, open(os.path.join(model_root_folder, model_name + 'ensemble.sav'), 'wb'))



    fig, ax = plt.subplots()
    ax.scatter(range(len(df_train['S1ActTrq_origin'][::50])), df_train['S1ActTrq_origin'][::50], s=10, alpha=0.5, label="observation")
    ax.plot(range(len(df_train['S1ActTrq_pred_mean'][::50])), df_train['S1ActTrq_pred_mean'][::50], color='red', label="predict mean")
    y_lower = df_train['S1ActTrq_pred_lower'][::50].to_numpy(dtype=np.float64)
    y_upper = df_train['S1ActTrq_pred_upper'][::50].to_numpy(dtype=np.float64)
    ax.fill_between(range(len(df_train['S1ActTrq_pred_mean'][::50])), y_lower, y_upper,
                    color='pink', alpha=0.5, label='predict std')
    ax.set_title(f"Inference by Bayesian Linear Regression (downsampling 1/50)")
    ax.set_xlabel("cycle times")
    ax.set_ylabel("Current (A)")
    ax.legend()

    fig2, ax2 = plt.subplots()
    tool_ids, rmse_tool = zip(*(results_train.items()))
    ax2.plot(tool_ids[:-1], rmse_tool[:-1], marker='o')
    ax2.set_xlabel("tool id")
    ax2.set_ylabel("RMSE (A)")
    ax2.set_title("Individual learning performance among used tools (Bayesian linear ridge regression)")
    plt.grid(True)
    plt.show()

    # evaluate
    model_new = pickle.load(open(os.path.join(model_root_folder, model_name + 'ensemble.sav'), 'rb'))
    eval_error = []
    eval_times = []
    df_result_eval = pd.DataFrame(
        columns=['Timestamp', 'S1ActTrq_pred_mean', 'S1ActTrq_pred_upper', 'S1ActTrq_pred_lower', 'S1ActTrq_origin'])
    start_time = time.time()
    for toolid, df_eval_sub in df_eval.groupby(by=["ToolID"]):
        print(f"Starting eval set with tool {toolid}")
        X_eval = df_eval_sub[selected_feature_cols].to_numpy()
        y_eval = df_eval_sub[label_cols].to_numpy().ravel()
        this_timestamp = df_eval_sub['Timestamp'].to_numpy()

        this_blrmodel = model_new[str(toolid)]

        # show learning performance:
        y_pred_mean_eval, y_pred_std_eval = this_blrmodel.predict(X_eval)
        this_mean_train, this_std_train = statistic_dict[str(toolid)]['mean'], statistic_dict[str(toolid)]['std']

        y_pred_mean_eval_origin, y_pred_lower_eval_origin, y_pred_upper_eval_origin, y_eval_origin = \
            RegFunctionWrapper.standard_to_origin(y_pred_mean_eval.reshape(-1, len(label_cols)),
                                                  y_eval.reshape(-1, len(label_cols)),
                                                  this_mean_train,
                                                  this_std_train,
                                                  label_cols,
                                                  y_pred_std=y_pred_std_eval.reshape(-1, len(label_cols)), )

        df_result_eval = pd.concat(
            [df_result_eval,
             pd.DataFrame(np.hstack((this_timestamp.reshape(-1, 1),
                                     y_pred_mean_eval_origin.reshape(-1, 1),
                                     y_pred_upper_eval_origin.reshape(-1, 1),
                                     y_pred_lower_eval_origin.reshape(-1, 1),
                                     y_eval_origin.reshape(-1, 1))), columns=df_result_eval.columns)],
            ignore_index=True)
        """
        fig, ax = plt.subplots()
        ax.scatter(range(len(y_train_origin)), y_train_origin, s=10, alpha=0.5, label="observation")
        ax.plot(range(len(y_pred_mean)), y_pred_mean_origin, color='red', label="predict mean")
        ax.fill_between(range(len(y_pred_mean_origin)), y_pred_lower_origin, y_pred_upper_origin,
                        color='pink', alpha=0.5, label='predict std')
        ax.set_title(f"Inference by Bayesian Linear Regression (Tool: {id})")
        ax.set_xlabel("cycle times")
        ax.set_ylabel("Current (A)")
        ax.legend()
        """
        this_rmse = np.sqrt(((y_pred_mean_eval_origin - y_eval_origin) ** 2).mean(axis=0))
        print(f"rmse for tool {toolid} is: {this_rmse}")
        results_eval[str(toolid)] = this_rmse[0]
        eval_error.append(np.sum((y_pred_mean_eval_origin - y_eval_origin) ** 2))

    df_result_eval.sort_values(by=['Timestamp'], inplace=True)

    df_eval = df_eval.merge(df_result_eval, on="Timestamp", how="left")

    # sanity check
    if df_eval[
        ['S1ActTrq_pred_mean', 'S1ActTrq_pred_lower', 'S1ActTrq_pred_upper', 'S1ActTrq_origin']].isnull().values.any():
        print("WARNING: data mission in inference data")
    rmse_all = np.sqrt(sum(eval_error) / len(df_eval))
    print(f"rmse for the complete process of {partname_eval} is {rmse_all}")
    print(f"computation time {sum(train_times)} min")

    results_eval['all'] = rmse_all

    with open('./model/train/ensemble_learning/result_blr_eval.json', 'w') as outputfile:
        json.dump(results_eval, outputfile)

    fig, ax = plt.subplots()
    ax.scatter(range(len(df_eval['S1ActTrq_origin'][::50])), df_eval['S1ActTrq_origin'][::50], s=10, alpha=0.5,
               label="observation")
    ax.plot(range(len(df_eval['S1ActTrq_pred_mean'][::50])), df_eval['S1ActTrq_pred_mean'][::50], color='red',
            label="predict mean")
    y_lower = df_eval['S1ActTrq_pred_lower'][::50].to_numpy(dtype=np.float64)
    y_upper = df_eval['S1ActTrq_pred_upper'][::50].to_numpy(dtype=np.float64)
    ax.fill_between(range(len(df_eval['S1ActTrq_pred_mean'][::50])), y_lower, y_upper,
                    color='pink', alpha=0.5, label='predict std')
    ax.set_title(f"Inference by Bayesian Linear Regression (downsampling 1/50)")
    ax.set_xlabel("cycle times")
    ax.set_ylabel("Current (A)")
    ax.legend()

    fig2, ax2 = plt.subplots()
    tool_ids, rmse_tool = zip(*(results_eval.items()))
    ax2.plot(tool_ids[:-1], rmse_tool[:-1], marker='o')
    ax2.set_xlabel("tool id")
    ax2.set_ylabel("RMSE (A)")
    ax2.set_title("Individual learning performance among used tools (Bayesian linear ridge regression)")
    plt.grid(True)
    plt.show()


