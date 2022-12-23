import pandas as pd
import numpy as np
import os
import json

from ...config import data_rootpath, feature_cols, label_cols, bounds, cycleTime_mw, params_lstm, \
    train_feature_filename, std_train_feature_filename, std_padding_train_feature_filename, std_eval_feature_filename, \
    std_padding_eval_feature_filename, eval_feature_filename


class FeaturePreprocess:
    """
    This class contains methods for feature preprocessing
    """
    def __init__(self, partname, simtype):
        """

        :param partname: workpiece folder name
        :param simtype: data resource of simulation
        """
        self.simtype = simtype

        # real indicates data from real CNC machine
        if simtype == 'real':
            self.path = os.path.join(data_rootpath, partname, 'ResultData.txt')
        # vnck indicates data from vnck simulation result
        elif simtype == 'vnck':
            self.path = os.path.join(data_rootpath, partname, 'SimResultData.txt')
        self.df = pd.read_csv(self.path, sep=";", index_col='Timestamp')


        print(f"[\033[1;32mOK\033[0m]  Start feature preprocessing on the file {partname}.")
        print(f"*  the raw feature file has \033[1;35m{len(self.df)}\033[0m rows")

    def numeric_converter(self, col_name):
        """
        convert engagement angles to list of numerical values
        :param col_name: str, column name for engagement angles
        :return: None
        """
        self.df[col_name] = self.df[col_name].apply(self.str2list)

        print("[\033[1;32mOK\033[0m]  Convert string representation to numerical value")

    @staticmethod
    def str2list(sample):
        """
        convert string to list
        :param sample: row in dataframe
        :return: list[list[float]], 2D lists of engagement angles
        """
        angle_lists = []
        sample_strip = sample.strip("[]")
        if sample_strip != "":
            sample_split1 = sample_strip.split("][")
            for angle_s in sample_split1:
                angle_list = []
                if angle_s != "":
                    sample_split2 = angle_s.split(",")
                    for x in sample_split2:
                        angle_list.append(float(x))
                angle_lists.append(angle_list)

        return angle_lists

    def drop_oob(self, bounds):
        """
        delete the samples, where the TCP coordinates are outside the workpiece dimension
        :param bounds: dict, workpiece dimension boundary
        :return: None
        """
        oob_idx = self.df[
            (bounds['x_init'] > self.df['XCurrPos']) | (bounds['x_end'] < self.df['XCurrPos']) | \
            (bounds['y_init'] > self.df['YCurrPos']) | (bounds['y_end'] < self.df['YCurrPos']) | \
            (bounds['z_end'] < self.df['ZCurrPos'])
            ].index
        self.df.drop(oob_idx, inplace=True)

        # if data comes from vnck, the original point is also be removed
        if self.simtype == 'vnck':
            zero_idx = self.df[(self.df['XCurrPos'] == 0) & (self.df['YCurrPos'] == 0) & (self.df['ZCurrPos'] == 0)].index
            self.df.drop(zero_idx, inplace=True)

        print("[\033[1;32mOK\033[0m]  drop oob value")
        print(f"*  the raw feature file now has \033[1;35m{len(self.df)}\033[0m rows")

    def drop_none(self):
        """
        [deprecated] delete items, where there is no actual cutting process
        :return: None
        """
        none_bool_select = ((self.df[['Area', 'Depth', 'Width', 'Removal_Volume']] == 0).all(axis='columns')) & (self.df['Angles'] == '[]')
        none_idx = self.df[none_bool_select].index
        if len(none_idx):
            self.df.drop(none_idx, inplace=True)

        print("[\033[1;32mOK\033[0m]  drop the none value")
        print(f"*  the raw feature file now has \033[1;35m{len(self.df)}\033[0m")


    def sum_angles(self, col_name):
        """
        sum up all values in 2d array of engagement angles
        :param col_name: column name for engagement angles
        :return: None
        """
        self.df[col_name] = self.df[col_name].apply(self.sum_up)

        print(f"[\033[1;32mOK\033[0m]  down size the list of list feature: {col_name}")

    @staticmethod
    def sum_up(sample) :
        """
        function to sum up the engagement angles
        :param sample: row in dataframe
        :return: float, sum value of 2d array
        """
        if not sample:
            return []

        # ToDO: find proper way to compute the value
        angle_sum_rows = [(sum(x) * np.pi)/180. for x in sample]

        return angle_sum_rows

    def integrate(self, *args):
        """

        :param args: dataframes, that need to be merged
        :return: None
        """
        for df in args:
            self.df = self.df.merge(df, on="Timestamp", how="left")
        self.df.fillna(method='ffill', inplace=True)
        print("[\033[1;32mOK\033[0m]  merge feature and label")


    def design_features(self):
        """
        design new feature for model learning
        :return: None
        """
        self.df['Angle_Mean'] = self.df['Angles'].apply(lambda x: float(sum(x)/len(x) if x else 0))
        self.df['Angle_Sin'] = self.df['Angles'].apply(lambda x: float(sum([np.sin(i) for i in x])/len(x) if x else 0))
        self.df['Angle_Cos'] = self.df['Angles'].apply(lambda x: float(sum([np.cos(i) for i in x])/len(x) if x else 0))
        self.df['ChipThickness'] = self.df['Actfeed'] * self.df['Area']


        print("[\033[1;32mOK\033[0m]  design new features")

    def compute_acceleration(self):
        """
        compute velocity and acceleration of every axis and spindle motor
        :return: None
        """
        # compute spindle acceleration
        self.df['S1ActAccel'] = self.df['S1Actrev'].diff()
        self.df['S1ActAccel'].fillna(0, inplace=True)
        self.df['S1ActAccel'] = (self.df['S1ActAccel'] / 0.01)

        # compute axis velocity and acceleration
        for col_name in ['XCurrPos', 'YCurrPos', 'ZCurrPos']:
            backward_diff = self.df[col_name].diff().fillna(0).to_numpy()
            forward_diff = backward_diff[1:]
            forward_diff = np.append(forward_diff, 0)
            assert backward_diff.shape[0] == forward_diff.shape[0]
            this_accel = (forward_diff - backward_diff)/ (0.01**2)
            self.df[col_name[0] + 'CurrVel'] = backward_diff / 0.01
            self.df[col_name[0] + 'CurrAccel'] = this_accel

        # sanity check
        if self.df.isnull().values.any():
            print("\033[1;33mWARNING: None type value occurs, please check\033[0m]")

        print("[\033[1;32mOK\033[0m]  Compute the acceleration of various axis motors")



    def standardization(self, df, col_name, **kwargs):
        """
        data standardization
        :param df: DataFrame, dataframe that to be standardized
        :param col_name: column name for the variables, that will be standardized
        :param kwargs: additional parameter for pre-defined statistic value
        :return:
        """
        statistic_json = {}

        # if not has kwargs, it needs to execute standardization based on data itself
        if 'statistic' not in kwargs:
            mean, std = df[col_name].mean(), df[col_name].std()
            # avoid dividing by zero
            std = std.replace(0., 1.)
            df.loc[:, col_name] = ((df[col_name] - mean) / std).to_numpy()
            statistic_json['all'] = {'mean': mean.to_dict(), 'std': std.to_dict()}
            print(f"[\033[1;32mOK\033[0m] standardization on train set")

        # if has kwargs, it means the data needs to be standardized by pre-defined statistic properties
        else:
            statistic_json = kwargs['statistic']
            for col, mean_val in statistic_json['all']['mean'].items():
                if col in df.columns:
                    std_val = statistic_json['all']['std'][col]
                    tmp = df[col] - mean_val
                    tmp2 = tmp / std_val
                    df.loc[:, col] = tmp2
                else:
                    print(f"\033[1;33mWARINING: {col} is not in the data set, please check\033[0m")

            print(f"[\033[1;32mOK\033[0m]  execute standard scale on evaluation / test set")

        return df, statistic_json

    def split(self, df):
        """
        find sub-process with different used tools and discontinuous point
        :param df: DataFrame, source data
        :return: DataFrame, data with corresponding task id
        """

        df_info = pd.DataFrame(columns=["Timestamp", "TaskID"])
        for toolid, df_sub in df.groupby(by=["ToolID"]):
            # convert index columns to normal attribute column
            df_sub = df_sub.reset_index()
            # if the timestamps difference of two neighbor samples are not equal to cycle time in mw cam, the data here
            # is discontinuous
            this_split_idx = df_sub[df_sub['Timestamp'].diff() != cycleTime_mw].index.tolist()
            start_idx = df_sub.index.tolist()[0]
            task_id = 1
            # first discontinuous point is the first sample, skip it
            if len(this_split_idx[1:]) > 0:
                for end_idx in this_split_idx[1:]:
                    # get current continuous part and record timestamp
                    this_timestamp_task_np = df_sub.loc[start_idx:end_idx-1, ['Timestamp']].to_numpy().reshape(-1, 1)
                    # create the task id
                    this_task_id = np.array([task_id]*this_timestamp_task_np.shape[0], dtype=np.int32).reshape(-1, 1)
                    df_new = pd.DataFrame(np.hstack((this_timestamp_task_np, this_task_id)), columns=df_info.columns)
                    # sanity check:
                    if (df_new['Timestamp'].diff() != 10)[1:].any():
                        print("\033[1;33mWARNING: The timestamp is still not continuous\033[0m]")
                    # append current task id
                    df_info = pd.concat([df_info, df_new],
                                              ignore_index=True)
                    # prepare for next continuous part
                    start_idx = end_idx
                    task_id += 1
            # add the last subset
            end_idx = df_sub.index.tolist()[-1]
            this_timestamp_task_np = df_sub.loc[start_idx:end_idx, ['Timestamp']].to_numpy().reshape(-1, 1)
            this_task_id = np.array([task_id]*this_timestamp_task_np.shape[0], dtype=np.int32).reshape(-1, 1)
            tmp = np.hstack((this_timestamp_task_np, this_task_id))
            df_info = pd.concat([df_info, pd.DataFrame(tmp, columns=df_info.columns)],
                                      ignore_index=True)
        df_info.sort_values(by=["Timestamp"], inplace=True)
        # set timestamp as index
        df_info.index = df_info['Timestamp'].values
        df_info.drop('Timestamp', axis=1, inplace=True)
        df_info.index.name = 'Timestamp'

        # merge task id to the raw data
        df = df.merge(df_info, on="Timestamp", how="left")
        print("[\033[1;32mOK\033[0m]  set the task id for each tool")

        return df


    def get_df(self):
        """
        return copy of the dataframe
        :return: Dataframe, processed data
        """
        return self.df.copy(deep=True)

    def padding(self, df_clean, df_complete):
        """
        padding the boundary value, this method is only for training a LSTM model
        :return: None
        """
        assert (df_clean.columns == df_complete.columns).all(), "attribute names not match"
        df_padding = pd.DataFrame(columns=df_clean.columns)
        df_padding.index.name = 'Timestamp'
        split_loc = np.insert(np.diff(df_clean.index) != cycleTime_mw, 0, True)
        assert len(split_loc) == len(df_clean), "Dimension not match"
        split_timestamp = df_clean[split_loc].index
        for timestamp in split_timestamp:
            try:
                df_padding_this = df_complete[(df_complete.index > timestamp - cycleTime_mw * params_lstm['window_size']) & \
                                         (df_complete.index < timestamp)]
            except:
                # if previous states are not enough to compensate the split sample: padding with zero:
                df_padding_real = df_complete[df_complete.index < timestamp]
                # how many samples are missing
                zero_padding_num = params_lstm['window_size'] - len(df_padding_real)
                # create fake timestamp:
                timestamp_fake = df_padding_real.index[0] - cycleTime_mw
                zero_padding_np = np.zeros((zero_padding_num, len(df_padding_real.columns)))
                for row in zero_padding_num:
                    line = pd.DataFrame(zero_padding_np[row, :], columns=df_padding_real.columns, index=timestamp_fake)
                    df_padding_real = pd.concat([line, df_padding_real])
                    timestamp_fake -= cycleTime_mw
                df_padding_this = df_padding_real
            assert len(df_padding_this) == params_lstm[
                'window_size'] - 1, f"wrong padding dimension, the padding dimension should be {params_lstm['window_size'] - 1} but get {len(df_padding)}"
            df_clean = pd.concat([df_padding_this, df_clean])
            df_padding = pd.concat([df_padding, df_padding_this])

        df_padding.sort_index(inplace=True)
        df_clean.sort_index(inplace=True)

        return df_clean, df_padding


if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../")
    print(f"Change the working directory: {os.getcwd()}")

    partname_train = "Versuchsteil_Quadrant_7"
    partname_eval = "Versuchsteil_Quadrant_8"
    partname = ""
    statistic_dict = {}

    # file type and model learning and  using type:
    # dtype means that the type of file, the file either for training or evaluation
    # simtype means the application scenario, either use real for learning model or vnck for adaptive process planning

    dtype = 'eval'
    simtype = 'real'

    # import different files according to the type of data
    if dtype == 'eval':
        with open(os.path.join(data_rootpath, partname_train, "statistic.json")) as inputfile:
            statistic_dict = json.load(inputfile)
        partname = partname_eval
    else:
        partname = partname_train

    df_drive = pd.read_csv(os.path.join(data_rootpath, partname, 'DriveData.csv'), sep=",", index_col='Timestamp')
    # sanity check:
    if df_drive.isnull().values.any():
        print(f"\033[1;33mWARNING: exist drive data has none type values in following rows \033[0m")
        none_rows_bool = df_drive.isnull().values.any(1)
        print(df_drive[none_rows_bool])
        df_drive = df_drive[~none_rows_bool]
        print(f"[\033[1;32mOK\033[0m]  delete none type value in \033[1;35mdrive data\033[0m")
    if df_drive.index.duplicated().any():
        print(f"\033[1;33mWARNING: exist drive data has duplicate indices in following rows: \033[0m")
        dupl_rows_bool = df_drive.index.duplicated()
        print(df_drive[dupl_rows_bool])
        df_drive = df_drive[~dupl_rows_bool]
        print(f"[\033[1;32mOK\033[0m]  delete duplicated rows in \033[1;35mdrive data\033[0m")

    # convert percent value to real current
    df_drive = df_drive[label_cols]

    myPrePro = FeaturePreprocess(partname, simtype)
    myPrePro.integrate(df_drive)
    myPrePro.compute_acceleration()
    myPrePro.numeric_converter("Angles")
    myPrePro.sum_angles("Angles")
    myPrePro.design_features()
    # only for LSTM please comment following line if you don't train a LSTM model:
    df_complete = myPrePro.get_df()
    myPrePro.drop_oob(bounds)
    df_data = myPrePro.get_df()
    # only for LSTM please comment following line if you don't train a LSTM model:
    df_data, df_padding = myPrePro.padding(df_data.copy(deep=True), df_complete.copy(deep=True))
    df_data = myPrePro.split(df=df_data)

    if dtype == 'train':
        df_norm, statistic_json = myPrePro.standardization(df_data.copy(deep=True),
                                                             feature_cols + label_cols)
    else:
        df_norm, _ = myPrePro.standardization(df_data.copy(deep=True),
                                                feature_cols + label_cols,
                                                statistic=statistic_dict)

    if dtype == 'train':
        # saving raw feature only for data analysis
        # subtract the padding value in the train set
        # only for LSTM please comment following line if you don't train a LSTM model:
        df_padding_norm = df_norm.loc[df_padding.index]
        df_norm.drop(df_padding.index, inplace=True)
        df_data.to_csv(os.path.join(data_rootpath, partname, train_feature_filename), index=True)
        # only for LSTM please comment following line if you don't train a LSTM model:
        df_padding_norm.to_csv(os.path.join(data_rootpath, partname, std_padding_train_feature_filename), index=True)
        df_norm.to_csv(os.path.join(data_rootpath, partname, std_train_feature_filename), index=True)
        with open(os.path.join(data_rootpath, partname, 'statistic.json'), 'w') as outputfile:
            json.dump(statistic_json, outputfile)
    else:
        # saving raw feature only for data analysis
        df_padding_norm = df_norm.loc[df_padding.index]
        df_norm.drop(df_padding.index, inplace=True)
        df_data.to_csv(os.path.join(data_rootpath, partname, eval_feature_filename), index=True)
        df_norm.to_csv(os.path.join(data_rootpath, partname, std_eval_feature_filename), index=True)
        df_padding_norm.to_csv(os.path.join(data_rootpath, partname, std_padding_eval_feature_filename), index=True)






