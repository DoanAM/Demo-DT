import pandas as pd
""" import sys, os
sys.path.append(os.path.abspath(os.path.join('..', '..', 'SimPy'))) """
from ...config import data_rootpath
import os

class TwinCatDataHandler:

    def __init__(self, partname):
        self.filepath = os.path.join(data_rootpath, partname, 'SimPathData.txt')
        self.df = pd.read_csv(self.filepath, sep=" ", index_col=False)

        print("[\033[1;32mOK\033[0m]  Start the TwinCat Data Handler")


    def calibrate(self):

        self.df["XActPos"] = - self.df["XActPos"]

        self.df.to_csv(self.filepath, index=False, sep=" ")



