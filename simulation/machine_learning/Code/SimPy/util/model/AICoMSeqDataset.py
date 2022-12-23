import torch
from torch.utils.data import Dataset
import numpy as np

from ...config import cycleTime_mw

class AICoMSeqDataset(Dataset):
    """
    Customized dataset inherited by Pytorch dataset. For detailed functionality please read
    https://pytorch.org/tutorials/beginner/basics/data_tutorial.html

    This Dataset is for LSTM model learning
    """
    def __init__(self, df, df_padding, input_cols, window_size, **kwargs):
        """
        :param df: DataFrame, dataset for model learning or inference
        :param input_cols: list[str], column names for features
        :param window_size: int, number of samples that are taken as input at one time
        :param kwargs: output_cols: list[str], column names for outputs
        """
        super(AICoMSeqDataset, self).__init__()
        self.X = torch.tensor(df[input_cols].values).to(torch.float32)
        if 'output_cols' in kwargs:
            output_cols = kwargs['output_cols']
            self.y = torch.tensor(df[output_cols].values).to(torch.float32)
        #self.split_idx = df[(df['ToolID'].diff() != 0) | (df['TaskID'].diff() != 0)].index.to_numpy()
        self.split_idx = df[df['Timestamp'].diff() != cycleTime_mw].index.to_numpy()
        self.window_size = window_size
        self.train_timestamp = df['Timestamp'].to_numpy()
        self.df_padding = df_padding
        self.input_cols = input_cols

    def __len__(self):
        return self.X.shape[0]

    def __getitem__(self, idx):
        # calculate distance between current idx and each split idx
        split_dist = idx - self.split_idx
        # only consider the split index that before current index
        split_dist = split_dist[split_dist >= 0]
        # if distance between current idx and all previous split indexes are greater than window size, no padding
        if (split_dist >= self.window_size - 1).all():
            idx_start = idx - self.window_size + 1
            x = self.X[idx_start:idx+1, :]
        # if there is split idx in current window
        else:
            # find the position of the nearest split index in the whole split index array
            nearest_split_idx_idx = np.argmin(split_dist)
            idx_start = self.split_idx[nearest_split_idx_idx]
            # get how many samples could be retrieved normally
            exist_size = split_dist[nearest_split_idx_idx] + 1
            # compute how many samples need to be replaced
            padding_size = self.window_size - exist_size
            start_valid_timestamp = self.train_timestamp[idx + 1 - exist_size]
            padding_timestamp = start_valid_timestamp - cycleTime_mw
            x = self.X[idx_start:idx + 1]
            for i in range(padding_size):
                x_padding_this = torch.tensor(self.df_padding[self.df_padding['Timestamp'] == padding_timestamp] \
                                              [self.input_cols].values).to(torch.float32)
                padding_timestamp -= cycleTime_mw
                x = torch.cat((x_padding_this, x), 0)
            """
            # create zero vector
            feature_dims = self.X[idx_start].shape[0]
            zero_padding = torch.zeros(feature_dims)
            padding = zero_padding.repeat(padding_size, 1)
            x = self.X[idx_start:idx+1]
            # add zero vector into the current window
            x = torch.cat((padding, x), 0)
            """

        assert x.shape[0] == self.window_size, f"sliding window fetch data with wrong size, wrong index: {idx}"

        # if current data set is for model learning
        if hasattr(self, 'y'):
            return x, self.y[idx]
        else:
            return x



