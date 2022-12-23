import pandas as pd
import numpy as np
import os
import json
from config import data_rootpath
import time
from matplotlib import pyplot as plt

# model
from model.GaussianProcessRegression import GaussianProcessRegression
from sklearn.gaussian_process.kernels import RBF, ConstantKernel, WhiteKernel, Matern

if __name__ == "__main__":

    partname = "Versuchsteil_Quadrant_7"
    df_train = pd.read_csv(os.path.join(data_rootpath, partname, "TrainDataNorm.csv"), sep=",")
    with open(os.path.join(data_rootpath, partname, "statistic.json")) as inputfile:
        statistic_dict = json.load(inputfile)
    selected_feature_col = ["S1Actrev", "Area", "Width", "Removal_Volume", "Angle_Mean", "ChipThickness"]
    label_col = ['S1ActTrq']
    ensemble_models = {}
    train_error=[]
    df_result = pd.DataFrame(columns=['Timestamp', 'S1ActTrq_pred_mean', 'S1ActTrq_pred_upper', 'S1ActTrq_pred_lower', 'S1ActTrq_origin'])
    start_time = time.time()
    for id, df_train_sub in df_train.groupby(by=["ToolID"]):
        print(f"Starting train set with tool {id}")
        X_train = df_train_sub[selected_feature_col].to_numpy()
        y_train = df_train_sub[label_col].to_numpy().ravel()
        this_timestamp = df_train_sub['Timestamp'].to_numpy()
        kernel_rbf = ConstantKernel(10, (1e-23, 1e23)) * \
                     RBF(length_scale=1 * np.ones(X_train.shape[1]), length_scale_bounds=(1e-23, 1e23)) + \
                     WhiteKernel(0.1, (1e-23, 1e23))

        this_gpmodel = GaussianProcessRegression(kernel_rbf, 25)

        this_gpmodel.fit(X_train, y_train)
        ensemble_models[str(id)] = this_gpmodel

        #show learning performance:
        y_pred_mean, y_pred_std = ensemble_models[str(id)].predict(X_train)
        this_mean, this_std = statistic_dict[str(id)]['mean']['S1ActTrq'], statistic_dict[str(id)]['std']['S1ActTrq']

        y_pred_mean_origin = y_pred_mean * this_std + this_mean
        y_pred_upper_origin = (y_pred_mean + y_pred_std) * this_std + this_mean
        y_pred_lower_origin = (y_pred_mean - y_pred_std) * this_std + this_mean
        y_train_origin = y_train * this_std + this_mean

        df_result = pd.concat(
            [df_result,
             pd.DataFrame(np.hstack((this_timestamp.reshape(-1, 1),
                                     y_pred_mean_origin.reshape(-1, 1),
                                     y_pred_upper_origin.reshape(-1, 1),
                                     y_pred_lower_origin.reshape(-1, 1),
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
        print(f"rmse for tool {id} is: {np.sqrt(((y_pred_mean_origin - y_train_origin)**2).mean())}")
        train_error.append(np.sum((y_pred_mean_origin - y_train_origin)**2))

    df_result.sort_values(by=['Timestamp'], inplace=True)

    df_train = df_train.merge(df_result, on="Timestamp", how="left")

    # sanity check
    if df_train[['S1ActTrq_pred_mean', 'S1ActTrq_pred_lower', 'S1ActTrq_pred_upper', 'S1ActTrq_origin']].isnull().values.any():
        print("WARNING: data mission in inference data")

    print(f"rmse for the complete process of {partname} is {np.sqrt(sum(train_error) / len(df_train))}")


    fig1, ax1 = plt.subplots()
    ax1.scatter(range(len(df_train['S1ActTrq_origin'][::50])), df_train['S1ActTrq_origin'][::50], s=10, alpha=0.5, label="observation")
    ax1.plot(range(len(df_train['S1ActTrq_pred_mean'][::50])), df_train['S1ActTrq_pred_mean'][::50], color='red', label="predict mean")
    y_lower = df_train['S1ActTrq_pred_lower'][::50].to_numpy(dtype=np.float64)
    y_upper = df_train['S1ActTrq_pred_upper'][::50].to_numpy(dtype=np.float64)
    ax1.fill_between(range(len(df_train['S1ActTrq_pred_mean'][::50])), y_lower, y_upper,
                    color='pink', alpha=0.5, label='predict std')
    ax1.set_title(f"Inference by Bayesian Linear Regression (downsampling 1/50)")
    ax1.set_xlabel("cycle times")
    ax1.set_ylabel("Current (A)")
    ax1.legend()

    plt.show()