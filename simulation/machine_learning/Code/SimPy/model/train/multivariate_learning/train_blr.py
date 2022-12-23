"""
This script is used to train a BLR model with multiple outputs. The target values are the motor current in different
axes
"""
from model.LinearRegression import LinearRegression
import pandas as pd
import os
import time
import json
from util.model.RegFunctionWrapper import RegFunctionWrapper

from config import data_rootpath, selected_feature_cols, label_cols, std_train_feature_filename, std_eval_feature_filename, \
    statistics_json_filename, model_rootpath

if __name__ =='__main__':
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../../")
    print(f"Change the working directory: {os.getcwd()}")

    # assumed we have one machining process(Versuchsteil_Quadrant_7) for training, one machining process(Versuchsteil_Quadrant_8) for evaluation
    partname_train = "Versuchsteil_Quadrant_7"
    partname_eval = "Versuchsteil_Quadrant_8"

    # hard coded only for demonstration and experiment
    iters = 100
    results = {}
    model_root_folder = os.path.join(model_rootpath, 'BLR')
    model_name = "multi_all.sav"
    model_path = os.path.join(model_root_folder, model_name)

    # init a BLR model with multi outputs
    lrmodel = LinearRegression("multi", iters)
    df_train = pd.read_csv(os.path.join(data_rootpath, partname_train, std_train_feature_filename), sep=",")
    with open(os.path.join(data_rootpath, partname_train, statistics_json_filename)) as inputfile:
        statistic_dict = json.load(inputfile)

    mean_train, std_train = statistic_dict['all']['mean'], statistic_dict['all']['std']
    df_eval = pd.read_csv(os.path.join(data_rootpath, partname_eval, std_eval_feature_filename), sep=",")
    df_eval.sort_values(by=["Timestamp"], inplace=True)

    X_train = df_train[selected_feature_cols].to_numpy()
    y_train = df_train[label_cols].to_numpy()

    X_eval = df_eval[selected_feature_cols].to_numpy()
    y_eval = df_eval[label_cols].to_numpy()

    start_time = time.time()
    # model learning
    lrmodel.fit(X_train, y_train)
    print(f"running time: {(time.time() - start_time)} s")

    # learning performance
    results['train'] = {}
    y_pred_mean_train = lrmodel.predict(X_train)
    # recover prediction value to original scale
    y_pred_mean_train_origin, y_train_origin = RegFunctionWrapper.standard_to_origin(
                                              y_pred_mean_train.reshape(-1, len(label_cols)),
                                              y_train.reshape(-1, len(label_cols)),
                                              mean_train,
                                              std_train,
                                              label_cols)

    pred_col_names = ['PredOrigin' + col_name for col_name in label_cols]
    true_col_names = ['TrueOrigin' + col_name for col_name in label_cols]
    df_train[pred_col_names] = y_pred_mean_train_origin.reshape(-1, len(label_cols))
    df_train[true_col_names] = y_train_origin.reshape(-1, len(label_cols))

    # calculate metric score on train set and individual error in every used tool
    results['train'] = RegFunctionWrapper.evaluation(df_train,
                                                     true_col_names,
                                                     pred_col_names,
                                                     selected_feature_cols,
                                                     label_cols,
                                                     results['train'])
    lrmodel.save(model_path)
    # get start indices of different sub-processes
    opt_change_idx = df_train[df_train["ToolID"].diff() != 0].index.tolist()
    RegFunctionWrapper.plot(y_train_origin,
                            y_pred_mean_train_origin,
                            label_cols,
                            results['train'],
                            10,
                            modelname='BLR',
                            dtype='train',
                            taskid=opt_change_idx)

    # evaluation performance
    results['eval'] = {}
    lrmodel.load(model_path)
    start_time = time.time()
    y_pred_mean_eval = lrmodel.predict(X_eval)
    print(f"evaluation time: {(time.time() - start_time)} s")

    # recover prediction value to original scale
    y_pred_mean_eval_origin, y_eval_origin = RegFunctionWrapper.standard_to_origin(
                                              y_pred_mean_eval.reshape(-1, len(label_cols)),
                                              y_eval.reshape(-1, len(label_cols)),
                                              mean_train,
                                              std_train,
                                              label_cols)

    df_eval[pred_col_names] = y_pred_mean_eval_origin.reshape(-1, len(label_cols))
    df_eval[true_col_names] = y_eval_origin.reshape(-1, len(label_cols))
    # calculate metric score on test set and individual error in every used tool
    results['eval'] = RegFunctionWrapper.evaluation(df_eval,
                                                    true_col_names,
                                                    pred_col_names,
                                                    selected_feature_cols,
                                                    label_cols,
                                                    results['eval'])
    with open(f"./model/train/multivariate_learning/'result_blr'.json", 'w') as outputfile:
        json.dump(results, outputfile)
    # get start indices of different sub-processes
    opt_change_idx = df_eval[df_eval["ToolID"].diff() != 0].index.tolist()
    RegFunctionWrapper.plot(y_eval_origin,
                            y_pred_mean_eval_origin,
                            label_cols,
                            results['eval'],
                            10,
                            modelname='BLR',
                            dtype='validation',
                            taskid=opt_change_idx)