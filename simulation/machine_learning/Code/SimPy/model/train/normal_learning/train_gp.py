"""
[Deprecated]: This script is used to train a GP model. Due to high computation resource and low data efficiency, the GP
model should not be used in the further application. This training process is only for experiment.
"""
import numpy as np
import pandas as pd
import os
import time
import json

# model
from model.GaussianProcessRegression import GaussianProcessRegression
from sklearn.gaussian_process.kernels import RBF, ConstantKernel, WhiteKernel
from util.model.RegFunctionWrapper import RegFunctionWrapper

from config import data_rootpath, std_train_feature_filename, std_eval_feature_filename, statistics_json_filename

if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../../")
    print(f"Change the working directory: {os.getcwd()}")

    # assumed we have one machining process(Versuchsteil_Quadrant_7) for training one machining process(Versuchsteil_Quadrant_8) for evaluation
    partname_train = "Versuchsteil_Quadrant_7"
    partname_eval = "Versuchsteil_Quadrant_8"


    selected_feature_cols = ["S1Actrev", "Actfeed", "S1ActAccel", "Area", "Width", "Removal_Volume", "Angle_Mean"]
    label_cols = ["S1ActTrq"]
    results = {}
    model_root_folder = "./model/save/GP"
    model_name = "base_all.sav"
    model_path = os.path.join(model_root_folder, model_name)

    df_train = pd.read_csv(os.path.join(data_rootpath, partname_train, std_train_feature_filename), sep=",")
    df_eval = pd.read_csv(os.path.join(data_rootpath, partname_eval, std_eval_feature_filename), sep=",")
    df_eval.sort_values(by=["Timestamp"], inplace=True)

    with open(os.path.join(data_rootpath, partname_train, statistics_json_filename)) as inputfile:
        statistic_dict = json.load(inputfile)

    mean_train, std_train = statistic_dict['all']['mean'], statistic_dict['all']['std']

    # down sampling the data size because GP need large computation resource
    X_train = df_train[selected_feature_cols].to_numpy()[::4]
    y_train = df_train[label_cols].to_numpy().ravel()[::4]

    X_eval = df_eval[selected_feature_cols].to_numpy()[::4]
    y_eval = df_eval[label_cols].abs().to_numpy().ravel()[::4]

    # hard coded kernel only for demonstration and experiment
    kernel_rbf = ConstantKernel(10, (1e-23, 1e23)) * \
                 RBF(length_scale=1 * np.ones(X_train.shape[1]), length_scale_bounds=(1e-23, 1e23)) + \
                 WhiteKernel(0.1, (1e-23, 1e23))
    start_time = time.time()
    # init a single output model
    gpr = GaussianProcessRegression(kernel_rbf, 25)

    gpr.fit(X_train, y_train)

    print(f"training time: {(time.time()-start_time) / 60.} min")
    print("learned kernel parameters:")
    print(gpr.get_kernel_parameters())

    results['train'] = {}

    # learning performance
    y_pred_mean_train, y_pred_std_train = gpr.predict(X_train)

    # recover prediction value to original scale
    y_pred_mean_train_origin, y_pred_lower_train_origin, y_pred_upper_train_origin, y_train_origin = \
        RegFunctionWrapper.standard_to_origin(y_pred_mean_train.reshape(-1, len(label_cols)),
                                              y_train.reshape(-1, len(label_cols)),
                                              mean_train,
                                              std_train,
                                              label_cols,
                                              y_pred_std=y_pred_std_train)

    pred_col_names = ['PredOrigin' + col_name for col_name in label_cols]
    true_col_names = ['TrueOrigin' + col_name for col_name in label_cols]
    df_train[pred_col_names] = y_pred_mean_train_origin.reshape(-1, len(label_cols))
    df_train[true_col_names] = y_train_origin.reshape(-1, len(label_cols))

    # calculate metric score on train set
    results['train'] = RegFunctionWrapper.evaluation(df_train,
                                                     true_col_names,
                                                     pred_col_names,
                                                     selected_feature_cols,
                                                     label_cols,
                                                     results['train'])

    gpr.save(model_path)

    RegFunctionWrapper.plot(y_train_origin,
                            y_pred_mean_train_origin,
                            label_cols,
                            results['train'],
                            2,
                            modelname='GP',
                            dtype='train',
                            y_pred_lower_origin=y_pred_lower_train_origin,
                            y_pred_upper_origin=y_pred_upper_train_origin)

    # evaluation performance
    gpr.load(model_path)
    results['eval'] = {}
    start_time = time.time()
    y_pred_mean_eval, y_pred_std_eval = gpr.predict(X_eval)
    print(f"evaluation time: {(time.time() - start_time)} s")

    # recover prediction value to original scale
    y_pred_mean_eval_origin, y_pred_lower_eval_origin, y_pred_upper_eval_origin, y_eval_origin = \
        RegFunctionWrapper.standard_to_origin(y_pred_mean_eval.reshape(-1, len(label_cols)),
                                              y_eval.reshape(-1, len(label_cols)),
                                              mean_train,
                                              std_train,
                                              label_cols,
                                              y_pred_std=y_pred_std_eval)

    df_eval[pred_col_names] = y_pred_mean_eval_origin.reshape(-1, len(label_cols))
    df_eval[true_col_names] = y_eval_origin.reshape(-1, len(label_cols))

    # calculate metric score on validation set
    results['eval'] = RegFunctionWrapper.evaluation(df_eval,
                                                    true_col_names,
                                                    pred_col_names,
                                                    selected_feature_cols,
                                                    label_cols,
                                                    results['eval'])
    with open('./model/train/normal_learning/result_gp.json', 'w') as outputfile:
        json.dump(results, outputfile)

    RegFunctionWrapper.plot(y_eval_origin,
                            y_pred_mean_eval_origin,
                            label_cols,
                            results['eval'],
                            2,
                            modelname='GP',
                            dtype='validation',
                            y_pred_lower_origin=y_pred_lower_eval_origin,
                            y_pred_upper_origin=y_pred_upper_eval_origin)