import torch
import torch.nn as nn

class MultiTaskLSTM(nn.Module):
    """
    multitask LSTM network
    """

    def __init__(self, input_dims, lstm_hidden_dims, share_hidden_dim, sub_hidden_dims, lstm_layers_num):
        """
        #
        :param input_dims: int, the number of the features
        :param lstm_hidden_dims: int, the number of the states as the input
        :param share_hidden_dim: list[int], output dimensions in each layer in share part
        :param sub_hidden_dims: list[int], output dimensions in each layer in task-specific part
        :param lstm_layers_num: int, the number of recurrent layers. E.g., setting num_layers=2 would mean stacking two LSTMs
        """
        super(MultiTaskLSTM, self).__init__()
        self.input_dims = input_dims
        self.lstm_hidden_dims = lstm_hidden_dims
        self.lstm_layers_num = lstm_layers_num
        self.share_hidden_dims = share_hidden_dim
        self.sub_hidden_dims = sub_hidden_dims
        # create input-output dimensions for each layer
        share_dims_pair = list(zip([self.lstm_hidden_dims] + self.share_hidden_dims[:-1], self.share_hidden_dims))
        sub_dims_pair = list(zip([self.share_hidden_dims[-1]] + self.sub_hidden_dims, self.sub_hidden_dims + [1]))
        self.lstm = nn.LSTM(
            input_size=self.input_dims,
            hidden_size=self.lstm_hidden_dims,
            batch_first=True,
            num_layers=self.lstm_layers_num
        )

        self.share_model = nn.Sequential()
        for i, dim_pair in enumerate(share_dims_pair, 1):
            self.share_model.add_module(f'fc_{i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.share_model.add_module(f'relu {i}', nn.ReLU())

        # sub model for multiple outputs
        self.submodel_s1 = nn.Sequential()
        self.submodel_X = nn.Sequential()
        self.submodel_Y = nn.Sequential()
        self.submodel_Y2 = nn.Sequential()
        self.submodel_Z = nn.Sequential()
        for i, dim_pair in enumerate(sub_dims_pair[:-1], 1):
            self.submodel_s1.add_module(f'sub model S1 hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_X.add_module(f'sub model X hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_Y.add_module(f'sub model Y hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_Y2.add_module(f'sub model Y hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.submodel_Z.add_module(f'sub model Z hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))

        # add output layers
        self.submodel_s1.add_module(f'sub model S1 output layer',
                                    nn.Linear(sub_dims_pair[-1][0], sub_dims_pair[-1][1]))
        self.submodel_X.add_module(f'sub model X output layer',
                                   nn.Linear(sub_dims_pair[-1][0], sub_dims_pair[-1][1]))
        self.submodel_Y.add_module(f'sub model Y output layer',
                                   nn.Linear(sub_dims_pair[-1][0], sub_dims_pair[-1][1]))
        self.submodel_Y2.add_module(f'sub model Y output layer',
                                   nn.Linear(sub_dims_pair[-1][0], sub_dims_pair[-1][1]))
        self.submodel_Z.add_module(f'sub model Z output layer',
                                   nn.Linear(sub_dims_pair[-1][0], sub_dims_pair[-1][1]))

    def forward(self, x):
        """
        forward computation

        :param x: torch.tensor(m, n, q), train set. m is the batch size, n is the dimension of the states, q is the dimension of the inputs x in each state
        :return: s1_current(m,), predicted spindle motor current, m is the batch size
        :return: x_current(m,), predicted x-axis motor current, m is the batch size
        :return: y_current(m,), predicted y-axis motor current, m is the batch size
        :return: y2_current(m,), predicted y2-axis motor current, m is the batch size
        :return: z_current(m,), predicted z-axis motor current, m is the batch size
        """
        batch_size = x.shape[0]
        h0 = torch.zeros(self.lstm_layers_num, batch_size, self.lstm_hidden_dims).requires_grad_()
        c0 = torch.zeros(self.lstm_layers_num, batch_size, self.lstm_hidden_dims).requires_grad_()

        # set init state and cell to zero
        _, (hn, _) = self.lstm(x, (h0, c0))

        share_output = self.share_model(hn.view(-1, self.lstm_hidden_dims))

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