import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

class RegFunctionWrapper:
    """
    Functions for model learning and evaluation
    """
    @staticmethod
    def standard_to_origin(y_pred_mean, y_true, mean, std, label_cols, **kwargs):
        """
        recover the original value from standardized value

        :param y_pred_mean: ndarray(m,), prediction by model. m is the number of samples
        :param y_true: ndarray(m,), true value. m is the number of samples
        :param mean: dict, mean value of each variable in data set
        :param std: dict, standard deviation value of each variable in data set
        :param label_cols: list[str], output column names
        :param kwargs: y_pred_std: ndarray(m,), uncertainty of the prediction
        :return: None
        """

        mean_list = []
        std_list = []
        for label_col in label_cols:
            mean_list.append(mean[label_col])
            std_list.append(std[label_col])

        mean_np = np.array(mean_list)
        std_np = np.array(std_list)
        y_pred_mean_origin = y_pred_mean * std_np + mean_np
        # original truth value is none, if no truth value is given
        y_true_origin = y_true * std_np + mean_np if isinstance(y_true, np.ndarray) else None

        # if prediction uncertainty is given, also return original uncertainty
        if 'y_pred_std' in kwargs:
            y_pred_std = kwargs['y_pred_std']
            y_pred_upper_origin = (y_pred_mean + y_pred_std) * std_np + mean_np
            y_pred_lower_origin = (y_pred_mean - y_pred_std) * std_np + mean_np


            if isinstance(y_true, np.ndarray):
                return y_pred_mean_origin, y_pred_lower_origin, y_pred_upper_origin, y_true_origin
            # no ground truth return
            else:
                return y_pred_mean_origin, y_pred_lower_origin, y_pred_upper_origin

        else:
            if isinstance(y_true, np.ndarray):
                return y_pred_mean_origin, y_true_origin
            # no ground truth return
            else:
                return y_pred_mean_origin

    @staticmethod
    def evaluation(df, true_col_origin, pred_col_origin, feature_cols, label_cols, results):
        """
        evaluate the prediction

        :param df: DataFrame, prediction data set
        :param true_col_origin: list[str], column names for ground truth in original scale
        :param pred_col_origin: list[str], column names for prediction in original scale
        :param feature_cols: list[str], column names for features(standardized)
        :param label_cols: list[str], column names for ground truth(standardized)
        :param results: dict, storage for the evaluation
        :return: dict, storage for the evaluation
        """

        n_features = len(feature_cols)
        n_samples = len(df)

        # overall evaluation
        y_pred_all_origin = df[pred_col_origin].to_numpy()
        y_true_all_origin = df[true_col_origin].to_numpy()
        # root mean square error
        rmse_all = mean_squared_error(y_true_all_origin, y_pred_all_origin, multioutput='raw_values', squared=False)
        # mean absolute error
        mae_all = mean_absolute_error(y_true_all_origin, y_pred_all_origin, multioutput='raw_values')
        # r square
        r2_all = r2_score(y_true_all_origin, y_pred_all_origin, multioutput='raw_values')
        # adjusted r square
        r2_adjust_all = 1 - (1 - r2_all) * (n_samples - 1) / (n_samples - n_features - 1)
        print(f"{label_cols} overall: RMSE: {rmse_all} MAE: {mae_all} adjusted_r2: {r2_adjust_all}")
        results['all'] = {}
        for i, label in enumerate(label_cols):
            results['all'][label] = dict(rmse=rmse_all[i], mae=mae_all[i], r2_adjust=r2_adjust_all[i])

        # individual evaluation on each tool
        for toolID, df_sub in df.groupby(by=["ToolID"]):
            results[str(toolID)] = {}
            y_pred_mean_origin_this = df_sub[pred_col_origin].to_numpy()
            y_origin_this = df_sub[true_col_origin].to_numpy()
            n_smaple_this = len(df_sub)
            rmse_this = mean_squared_error(y_origin_this, y_pred_mean_origin_this, multioutput='raw_values',
                                           squared=False)
            mae_this = mean_absolute_error(y_origin_this, y_pred_mean_origin_this, multioutput='raw_values')
            r2_this = r2_score(y_origin_this, y_pred_mean_origin_this, multioutput='raw_values')
            r2_adjust_this = 1 - (1 - r2_this) * (n_smaple_this - 1) / (n_smaple_this - n_features - 1)
            print(f"{label_cols} on tool {toolID}: RMSE: {rmse_this} MAE: {mae_this} adjusted_r2: {r2_adjust_this}")
            results[str(toolID)] = {}
            for i, label in enumerate(label_cols):
                results[str(toolID)][label] = dict(rmse=rmse_this[i], mae=mae_this[i], r2_adjust=r2_adjust_this[i])

        return results

    @staticmethod
    def plot(y_true_origin, y_pred_mean_origin, label_cols, results, downsampling_size, modelname, dtype, **kwargs):
        """
        show the learning or inference performance

        :param y_true_origin: ndarray(m,n), ground truth in original scale, m is the number of the samples, n is the number of outputs
        :param y_pred_mean_origin: ndarray(m,n), prediction in original scale, m is the number of the samples, n is the number of outputs
        :param label_cols: list[str], column names for output
        :param results: dict, storage of evaluation
        :param downsampling_size: int, sampling interval to reduce shown points in the graph
        :param modelname: str, model name
        :param dtype: str, type of data set, either train or validation
        :param kwargs: y_pred_lower_origin, ndarray(m,n), lower confident boundary in original scale, m is the number of the samples, n is the number of outputs
        :param kwargs: y_upper_lower_origin, ndarray(m,n), upper confident boundary in original scale, m is the number of the samples, n is the number of outputs
        :return: None
        """
        num_labels = len(label_cols)

        # comparison between prediction and ground truth
        for i in range(num_labels):
            fig, ax = plt.subplots()
            ax.tick_params(axis='both', labelsize=16)
            ax.scatter(range(len(y_true_origin[::downsampling_size, i])), y_true_origin[::downsampling_size, i], s=10,
                       alpha=0.5, label="observation")
            ax.plot(range(len(y_pred_mean_origin[::downsampling_size, i])), y_pred_mean_origin[::downsampling_size, i],
                    color='red', label="predict mean")

            # if confident intervals are given, also plot them in graph
            if 'y_pred_lower_origin' in kwargs and 'y_pred_upper_origin' in kwargs:
                y_pred_lower_origin = kwargs['y_pred_lower_origin']
                y_pred_upper_origin = kwargs['y_pred_upper_origin']
                ax.fill_between(range(len(y_pred_mean_origin[::downsampling_size, i])),
                                y_pred_lower_origin[::downsampling_size, i],
                                y_pred_upper_origin[::downsampling_size, i],
                                color='pink', alpha=0.5, label='predict std')
            # show the sub-processes with different used tools
            if 'taskid' in kwargs:
                task_change_idx = kwargs['taskid']
                #ymin = y_true_origin.min(axis=0)[i]
                #ymax = y_true_origin.max(axis=0)[i]
                for task_idx in task_change_idx[1:]:
                    ax.axvline(int(task_idx / downsampling_size), color='gray', linestyle='dashed')
            ax.set_title(
                f" Prediction of {label_cols[i]} by {modelname} on {dtype} set (down sampling 1/{downsampling_size})",
                fontsize=22)
            ax.set_xlabel(f"cycle times (ms)", fontsize=22)
            ax.set_ylabel(f"{label_cols[i]} (A)", fontsize=22)
            ax.legend(prop={'size': 16})
            plt.tight_layout()

        # show individual performances with each tool
        for eval_metric in ['rmse', 'mae', 'r2_adjust']:
            fig2, ax2 = plt.subplots()
            ax2.tick_params(axis='both', labelsize=16)
            ax2.set_xlabel("tool id", fontsize=22)
            ax2.set_ylabel(f"{eval_metric}", fontsize=22)
            ax2.set_title(f"Individual performance ({modelname}) with different used tools on {dtype} set", fontsize=22)
            ax2.grid(True)
            if len(label_cols) == 1:
                tool_ids, rmse_tool = zip(*(results.items()))
                x = np.arange(len(tool_ids[1:]))
                ax2.bar(x, [item[label_cols[0]][eval_metric] for item in rmse_tool[1:]], 0.2, label=label_cols[0])
                ax2.set_xticks(x, tool_ids[1:])
                ax2.legend(prop={'size': 16})

            elif len(label_cols) == 5:
                width = 0.17
                tool_ids, rmse_tool = zip(*(results.items()))
                x = np.arange(len(tool_ids[1:]))
                rects1 = ax2.bar(x - 2.5 * width, [item[label_cols[0]][eval_metric] for item in rmse_tool[1:]], width, label=label_cols[0])
                rects2 = ax2.bar(x - 1.5 * width, [item[label_cols[1]][eval_metric] for item in rmse_tool[1:]], width,
                        label=label_cols[1])
                rects3 = ax2.bar(x - 0.5 * width, [item[label_cols[2]][eval_metric] for item in rmse_tool[1:]], width,
                        label=label_cols[2])
                ax2.bar(x + 0.5 * width, [item[label_cols[3]][eval_metric] for item in rmse_tool[1:]], width,
                        label=label_cols[3])
                ax2.bar(x + 1.5 * width, [item[label_cols[4]][eval_metric] for item in rmse_tool[1:]], width,
                        label=label_cols[4])
                ax2.set_xticks(x, tool_ids[1:])
                for i in x:
                    ax2.axvline(i + 2.5 * width, linestyle='dashed', color='gray')
                ax2.legend(prop={'size': 16})


        plt.show()
