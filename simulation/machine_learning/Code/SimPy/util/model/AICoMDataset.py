import torch
from torch.utils.data import Dataset

class AICoMDataset(Dataset):
    """
    Customized dataset inherited by Pytorch dataset. For detailed functionality please read
    https://pytorch.org/tutorials/beginner/basics/data_tutorial.html

    This Dataset is for multilayer perception model learning
    """

    def __init__(self, df, input_cols, **kwargs):
        """

        :param df: DataFrame, dataset for model learning or inference
        :param input_cols: list[str], column names for features
        :param kwargs: output_cols: list[str], column names for outputs
        """
        super(AICoMDataset, self).__init__()
        self.samples = []

        for _, row in df.iterrows():
            x = torch.tensor(row[input_cols]).to(torch.float32)
            if 'output_cols' in kwargs:
                output_cols = kwargs['output_cols']
                y = torch.tensor(row[output_cols]).to(torch.float32)
                self.samples.append((x, y))
            else:
                self.samples.append(x)

    def __len__(self):

        return len(self.samples)

    def __getitem__(self, idx):

        return self.samples[idx]




