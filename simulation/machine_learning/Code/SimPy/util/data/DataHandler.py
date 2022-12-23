import numpy as np
import pandas as pd
import os
from matplotlib import pyplot as plt
from scipy.spatial.transform import Rotation as R

from config import data_rootpath, cnc_filename, toolpath_filename, tool_filename


class DataHandler:
    """
    This class contains the function to handle the raw data from real CNC machine
    """

    def __init__(self, partname):
        """

        :param partname: str, workpiece folder name
        """
        self.data_folder = os.path.join(data_rootpath, partname)

        cncname = os.path.join(self.data_folder, cnc_filename)
        toolname = os.path.join(self.data_folder, tool_filename)

        self.df_cnc = pd.read_csv(cncname, sep=",", index_col='Timestamp')
        self.df_tool = pd.read_csv(toolname, sep=",", index_col='Timestamp')

        # in order to load this file in dll library, here use text file
        self.pathname = os.path.join(self.data_folder, toolpath_filename)

        self.df_path = None

        # sanity check if any data is missing or duplicated:
        self._sanity_check('cnc')

    def sort(self):
        """
        sort the raw data by timestamp in ascend order
        :return: None
        """
        self.df_cnc.sort_values(by=['Timestamp'], inplace=True)
        print("[\033[1;32mOK\033[0m]  Sort the value in time ascend stamp order")

        # sanity check if any data is still missing or duplicated
        self._sanity_check('cnc')

    def drop_duplicates(self):
        """
        drop duplicated items in cnc data
        :return:None
        """
        self.df_cnc = self.df_cnc[~self.df_cnc.index.duplicated(keep='last')]
        print("[\033[1;32mOK\033[0m]  drop the value with duplicate timestamp")

        self._sanity_check('cnc')


    def truncate(self):
        """
        delete unnecessary columns in cnc data
        :return: None
        """
        # truncate cnc file
        self.df_cnc.drop(
            ['XCurrPos', 'YCurrPos', 'Y2CurrPos', 'ZCurrPos', 'Y2ActPos', 'S1Currrev', 'S1Cmdrev', 'tbvec0', 'tbvec1',
             'tbvec2'],
            axis=1,
            inplace=True)

        # truncate tool file
        self.df_tool.drop(['ID', 'ArtNr', 'category', 'Name', 'Length', 'Diameter'], axis=1, inplace=True)

        print("[\033[1;32mOK\033[0m]  delete the unnecessary columns")

    def dropna(self):
        """
        drop none type items in the cnc and tool data
        :return: None
        """

        self.df_cnc.dropna(axis=0, inplace=True)
        self.df_tool.dropna(axis=0, inplace=True)

        print("[\033[1;32mOK\033[0m]  delete the rows which has none type attributes")

    def calibrate(self, **kwargs):
        """
        TCP coordinates transformation and unit calibration
        :param kwargs: coordinate offset
        :return: None
        """

        self.df_cnc[["XActPos", "YActPos", "ZActPos"]] = self.df_cnc[["XActPos", "YActPos", "ZActPos"]].divide(10000.)

        if 'df_wcs' in kwargs.keys():

            df_wcs = kwargs['df_wcs']
            # merge cnc file and wcs file
            self.df_cnc = pd.merge(self.df_cnc, df_wcs, how="left", on='Timestamp')
            self.df_cnc.fillna(method='ffill', inplace=True)
            self.df_cnc.dropna(axis=0, inplace=True)
            self.df_cnc.index.name = 'Timestamp'

            euler_angles_unique = self.df_cnc[['alpha', 'beta', 'gamma']].drop_duplicates().to_numpy()

            # extract transformation information:
            for euler_angle in euler_angles_unique:

                # get coordinates that are matched to current offset
                curr_boolean_selection = (self.df_cnc['alpha'] == euler_angle[0]) & \
                                         (self.df_cnc['beta'] == euler_angle[1]) & \
                                         (self.df_cnc['gamma'] == euler_angle[2])

                # rotation matrix
                r = R.from_euler('zyx', [-euler_angle[2], euler_angle[1], euler_angle[0]], degrees=True)
                curr_r_matrix = r.as_matrix()

                p_acs = self.df_cnc[curr_boolean_selection][["XActPos", "YActPos", "ZActPos"]].to_numpy()
                # translation
                p_offset = self.df_cnc[curr_boolean_selection][["X", "Y", "Z"]].to_numpy()

                assert p_acs.shape == p_offset.shape, "offset and acs coordinates not match"
                # transformation with current offset varialbes
                p_transform = np.dot(curr_r_matrix, (p_acs - p_offset).T)
                p_transform = np.around(p_transform, decimals=3)

                assert len(self.df_cnc[curr_boolean_selection]) == p_transform.shape[
                    1], "wrong dimension of calibrate coordinates"

                """
                tmp = self.df_cnc.loc[self.df_cnc[curr_boolean_selection].index]

                df_diff = pd.DataFrame(columns=['Timestamp'])
                df_diff['Timestamp'] = tmp.index
                df_diff['Dist'] = df_diff['Timestamp'].diff()
                df_diff.dropna(inplace=True)
                if len(df_diff[df_diff['Dist'] != 1]) != 0:
                    print("WARNING: Timestamp is not continuous in raw data, following rows are uncontentious")
                """

                self.df_cnc.loc[self.df_cnc[curr_boolean_selection].index, ["XActPos"]] = p_transform[0, :]
                self.df_cnc.loc[self.df_cnc[curr_boolean_selection].index, ["YActPos"]] = p_transform[1, :]
                self.df_cnc.loc[self.df_cnc[curr_boolean_selection].index, ["ZActPos"]] = p_transform[2, :]

            self.df_cnc.drop(['X', 'Y', 'Z', 'alpha', 'beta', 'gamma'], axis=1, inplace=True)


        elif 'offsets' in kwargs.keys():
            # only translation of cnc data
            offsets = kwargs['offsets']
            self.df_cnc["XActPos"] = self.df_cnc["XActPos"] - offsets['x_offset']
            self.df_cnc["YActPos"] = self.df_cnc["YActPos"] - offsets['y_offset']
            self.df_cnc["ZActPos"] = self.df_cnc["ZActPos"] - offsets['z_offset']


        # change unit of spindle speed and feed rate
        self.df_cnc['S1Actrev'] = (self.df_cnc['S1Actrev'] / (100. * 360)).round(3)
        self.df_cnc['Actfeed'] = self.df_cnc['Actfeed'] / 1000.

        if self.df_cnc.isnull().values.any():
            print("\033[1;33mWARNING: None type value appears after calibration, please check\033[0m")

        print("[\033[1;32mOK\033[0m]  coordinates calibration")

    def compute_tool_id(self):
        """
        join tool number
        :return: None
        """

        self.df_tool.columns = ['ToolID']
        self.df_path = pd.merge(self.df_cnc, self.df_tool, how='left', on='Timestamp')
        self.df_path.fillna(method='ffill', inplace=True)
        self.df_path.dropna(axis=0, inplace=True)

        print("[\033[1;32mOK\033[0m]  set tool id")
        if self.df_path.isnull().values.any():
            print("\033[1;33mWARNING: None type value appears after calibration, please check\033[0m")

    def save(self):
        """
        save the calibrated data
        :return: None
        """
        if self.df_path.isnull().values.any():
            print("\033[1;33mWARNING: None type value in Path Data, please check\033[0m")

        # change the order of columns for loading in simulation
        self.df_path = self.df_path[
            ['XActPos', 'YActPos', 'ZActPos', 'S1Actrev', 'Actfeed', 'ToolID']]

        # sanity check the continual for the path data
        self._sanity_check('path')

        self.df_path.to_csv(self.pathname, index=True, sep=" ")

        print("[\033[1;32mOK\033[0m]  save the trajectory data")
        print(f"*  trajectory data is saved in \033[1;34m{self.pathname}\033[0m")

    def plot_trajectory(self, bounds):
        """
        show the calibrated result in X and Y coordinates
        :param bounds: dict, workpiece dimension boundary
        :return: None
        """

        if self.df_path is not None:

            # only show the TCP positions, that are inside the workpiece
            oob_idx = self.df_path[
                (bounds['x_init'] > self.df_path['XActPos']) | (bounds['x_end'] < self.df_path['XActPos']) | \
                (bounds['y_init'] > self.df_path['YActPos']) | (bounds['y_end'] < self.df_path['YActPos']) | \
                (bounds['z_end'] < self.df_path['ZActPos'])
                ].index

            df_temp = self.df_path.drop(oob_idx)[['XActPos', 'YActPos', 'ZActPos']]

            fig, ax = plt.subplots()
            ax.scatter(df_temp["XActPos"], df_temp["YActPos"])


        else:
            print("\033[1;33mWARNING: handling process not be executed, please call the handling functions first\033[0m")

    def _sanity_check(self, df_type):
        """
        check if selected data is continuous
        :param df_type: str, type of dataframe either 'path' for calibrated tool path file or raw cnc file
        :return: None
        """
        df_diff = pd.DataFrame(columns=['Timestamp'])
        if df_type == 'path':
            df_diff['Timestamp'] = self.df_path.index
        elif df_type == 'cnc':
            df_diff['Timestamp'] = self.df_cnc.index
        df_diff['Dist'] = df_diff['Timestamp'].diff()
        df_diff.dropna(inplace=True)
        if len(df_diff[df_diff['Dist'] != 1]) != 0:
            print(f"\033[1;33mWARNING: Timestamp is not continuous in {df_type} data, following rows are uncontentious\033[0m")
            print(df_diff[df_diff['Dist'] != 1])






