import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
import matplotlib.dates as mdates
import os
from datetime import datetime
from config import data_rootpath


class DataAnalysis:
    """
    visualize the simulation result or processed features. Only for analysis, do not make sense for application
    """

    def __init__(self, partname):
        """

        :param partname: workpiece folder name
        """
        self.df = pd.read_csv(os.path.join(data_rootpath, partname, 'AnalysisData.csv'), sep=",")

    def overview(self, col_names):
        """
        show dataframe overview of statistic properties
        :param col_names: list(str), attribute names in dataframe
        :return: None
        """
        for col in col_names:
            print(self.df[col].describe())

    def tool_specific_overview(self, col_names):
        """
        show statistic properties based on individual used tool
        :param col_names: list(str), attribute names in dataframe
        :return: None
        """
        for id, df_sub in self.df.groupby(by=['ToolID']):
            print(f"Tool : {id}")
            overview = df_sub[col_names].describe()
            print(overview)

    def pair_plot(self, col_names):
        """
        show variable pair plot
        :param col_names: list(str), attribute names in dataframe
        :return: None
        """
        # sns.set(font_scale=1.5)
        p = sns.pairplot(self.df[col_names], diag_kind='kde', plot_kws={'color': 'blue'}, diag_kws={'color': 'blue'})

    def correlation(self, col_names):
        """
        show correlation matrix
        :param col_names: col_names: list(str), attribute names in dataframe
        :return: None
        """
        sns.set(font_scale=1.5)
        sns.set_theme(style="whitegrid")
        sns.heatmap(self.df[col_names].corr(),
                    cbar=True,
                    annot=True,
                    square=True,
                    fmt=".2f",
                    #annot_kws={'fontsize': 10},
                    yticklabels=col_names,
                    xticklabels=col_names,
                    cmap='Blues')
        plt.xticks(rotation=45)


    def distribution(self, col_name):
        """
        show variable zero value distribution pie chart
        :param col_name: str, single attribute name
        :return: None
        """
        ax = sns.displot(self.df, x=col_name, bins=[0,2.5,5,7.5,10,12.5,15,17.5,20], color='blue')
        zero_nums = self.df[self.df[col_name] == 0][col_name].count()
        ax.set_xticklabels(fontsize=16)
        ax.set_yticklabels(fontsize=16)
        plt.xlabel('engagement depth (mm)', fontsize=22)
        plt.ylabel('number', fontsize=22)
        plt.title('Distribution of the engagement depth', fontsize=22)

        colors = sns.color_palette('bright')[:2]
        data = [zero_nums, len(self.df) - zero_nums]
        labels = ['zero value', 'other']
        fig, ax = plt.subplots()
        ax.pie(x=data, labels=labels, colors=colors, autopct='%1.1f%%', textprops={'fontsize': 16})
        ax.set_title("zero value percentage in engagement depth", fontsize=22)
        ax.axis('equal')
        plt.show()


    def time_series(self, col_name):
        """
        show single variable
        :param col_name: str, single attribute name
        :return: None
        """

        fig, ax = plt.subplots()
        ax.tick_params(axis='both', labelsize=16)
        times_x = [datetime.fromtimestamp(x / 1000.) for x in self.df['Timestamp'].values]
        opt_change_idx = self.df[self.df["ToolID"].diff() != 0].index.tolist()

        tool_id_seq = self.df[self.df["ToolID"].diff() != 0]['ToolID'].tolist()
        ax.plot(times_x, self.df[col_name].to_numpy(), color='blue')
        ymin = self.df[col_name].min()
        ymax = self.df[col_name].max()

        for opt_idx, tool_id in zip(opt_change_idx[1:], tool_id_seq[1:]):
            ax.vlines(times_x[opt_idx], ymin, ymax, colors='r', linestyles='dashed')

        ax.set_ylabel("spindle current (A)", fontsize=22)
        ax.set_title(f"Time series of spindle current", fontsize=22)
        plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%d-%m %H:%M'))

    def time_series_cmp(self, feature_col, label_col, **kwargs):
        """
        show comparison of two variables' time series
        :param feature_col: str, feature name
        :param label_col: str, label name
        :param kwargs: additional variables
        :return: None
        """
        if 'toolid' in kwargs:
            df_tmp = self.df[self.df['ToolID'] == kwargs['toolid']]
        else:
            df_tmp = self.df
        fig, ax = plt.subplots()
        ax.tick_params(axis='both', labelsize=16)
        times_x = [datetime.fromtimestamp(x / 1000.) for x in self.df['Timestamp'].values]
        ax.plot(times_x, df_tmp[feature_col].to_numpy(), color="red", label=feature_col)
        # ax.set_xlabel("datetime", fontsize=20)
        ax.set_ylabel(feature_col + ' ($rev/s$)', fontsize=22)
        #ax.set_ylabel(feature_col + ' ($mm^3$)', fontsize=22)
        plt.legend(loc='upper left', prop={'size': 16})
        ax2 = ax.twinx()
        ax2.tick_params(axis='both', labelsize=16)
        ax2.plot(times_x, df_tmp[label_col].to_numpy(), color="blue", label=label_col)
        ax2.set_ylabel(label_col + ' (A)', fontsize=22)
        plt.legend(prop={'size': 16})
        plt.title(f"Comparison of time series {feature_col} and {label_col} {'by'+ kwargs['toolid'] if 'toolid'in kwargs else ' '}", fontsize=22)
        plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%d-%m %H:%M:%S'))
        plt.show()




if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../../")
    print(f"Change the working directory: {os.getcwd()}")

    partname = "Versuchsteil_Quadrant_7"
    sns.set_theme(style="whitegrid")
    #sns.set(font_scale=1.4)
    plt.rcParams.update({'font.size': 16})
    raw_feature_col = ["S1Actrev", "Actfeed", "Area", "Depth", "Width", "Removal_Volume"]
    new_feature_col = ["S1ActAccel", "XCurrAccel", "YCurrAccel", "ZCurrAccel", "Angle_Mean"]
    selected_label = ["S1ActTrq", "XActTrq", "YActTrq", "ZActTrq"]
    single_label = ["S1ActTrq"]
    rel_col = ["XCurrAccel", "YCurrAccel", "XActTrq", "YActTrq"]
    myEDA = DataAnalysis(partname)
    #myEDA.overview(feature_col + selected_label)
    #myEDA.tool_specific_overview(feature_col + selected_label)
    #myEDA.distribution("Depth")
    #myEDA.pair_plot(new_feature_col + single_label)

    # create a new window to plot
    #plt.figure()
    #myEDA.correlation(new_feature_col + single_label)

    myEDA.time_series_cmp("Removal_Volume", "S1ActTrq")
    #myEDA.time_series("S1ActTrq")

    plt.show()









