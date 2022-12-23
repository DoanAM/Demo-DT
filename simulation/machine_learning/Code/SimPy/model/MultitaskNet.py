import torch
import torch.nn as nn


class MultitaskNet(nn.Module):
    """
    multitask multilayer perception
    """
    def __init__(self, input_dims, share_hidden_dims, sub_hidden_dims):
        """

        :param input_dims: int, the number of the features
        :param share_hidden_dims: list[int], output dimensions in each share layer
        :param sub_hidden_dims: list[int], output dimensions in each task-specific layer
        """
        super(MultitaskNet, self).__init__()

        self.share_model = nn.Sequential()
        # create input-output dimension pair for each layer
        share_layer_dim_pair = list(zip([input_dims] + share_hidden_dims[:-1], share_hidden_dims))
        sub_layer_dim_pair = list(zip([share_hidden_dims[-1]] + sub_hidden_dims, sub_hidden_dims + [1]))

        for i, dim_pair in enumerate(share_layer_dim_pair, 1):
            self.share_model.add_module(f'share hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.share_model.add_module(f'relu {i}', nn.ReLU())

        # ToDo: create sub model automatically
        self.submodel_s1 = nn.Sequential()
        self.submodel_X = nn.Sequential()
        self.submodel_Y = nn.Sequential()
        self.submodel_Y2 = nn.Sequential()
        self.submodel_Z = nn.Sequential()
        for i, dim_pair in enumerate(sub_layer_dim_pair[:-1], 1):
            self.submodel_s1.add_module(f'sub model S1 hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_X.add_module(f'sub model X hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_Y.add_module(f'sub model Y hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_Y2.add_module(f'sub model Y hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_Z.add_module(f'sub model Z hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))

        # add output layer individually
        self.submodel_s1.add_module(f'sub model S1 output layer', nn.Linear(sub_layer_dim_pair[-1][0], sub_layer_dim_pair[-1][1]))
        self.submodel_X.add_module(f'sub model X output layer', nn.Linear(sub_layer_dim_pair[-1][0], sub_layer_dim_pair[-1][1]))
        self.submodel_Y.add_module(f'sub model Y output layer', nn.Linear(sub_layer_dim_pair[-1][0], sub_layer_dim_pair[-1][1]))
        self.submodel_Y2.add_module(f'sub model Y output layer', nn.Linear(sub_layer_dim_pair[-1][0], sub_layer_dim_pair[-1][1]))
        self.submodel_Z.add_module(f'sub model Z output layer', nn.Linear(sub_layer_dim_pair[-1][0], sub_layer_dim_pair[-1][1]))

    def forward(self, X):
        """
        forward computation

        :param X: torch.tensor(m, n), train set. m is the batch size, n is the dimension of the features
        :return: s1_current(m,), predicted spindle motor current, m is the batch size
        :return: x_current(m,), predicted x-axis motor current, m is the batch size
        :return: y_current(m,), predicted y-axis motor current, m is the batch size
        :return: y2_current(m,), predicted y2-axis motor current, m is the batch size
        :return: z_current(m,), predicted z-axis motor current, m is the batch size
        """
        share_output = self.share_model(X)

        s1_current = self.submodel_s1(share_output)
        x_current = self.submodel_X(share_output)
        y_current = self.submodel_Y(share_output)
        y2_current = self.submodel_Y2(share_output)
        z_current = self.submodel_Z(share_output)

        return s1_current, x_current, y_current, y2_current, z_current

    def load(self, model_state_dict):
        """
        load pre-trained weight

        :param model_state_dict: weight dict
        :return: None
        """

        self.load_state_dict(model_state_dict)

    def save(self, path, loss):
        """
        save the learned weight

        :param path: str, save path
        :param loss: total train loss
        :return: None
        """

        torch.save({'model_state_dict': self.state_dict(), 'best_mse': loss}, path)



















