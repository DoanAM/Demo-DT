import torch
import torch.nn as nn

class LSTMRegression(nn.Module):
    """
    LSTM model with single output. For detail information about building LSTM model, please see
    https://pytorch.org/docs/stable/generated/torch.nn.LSTM.html
    """

    def __init__(self, input_dims, hidden_dims, output_dims, lstm_layers_num, fc_dims):
        """

        :param input_dims: int, the number of the features
        :param hidden_dims: int, the number of the states as the input
        :param output_dims: int, the number of the output variables
        :param lstm_layers_num: int, the number of recurrent layers. E.g., setting num_layers=2 would mean stacking two LSTMs
        :param fc_dims: list[int], output dimensions in each layer
        """
        super(LSTMRegression, self).__init__()
        self.input_dims = input_dims
        self.hidden_dims = hidden_dims
        self.output_dims = output_dims
        self.lstm_layers_num = lstm_layers_num
        self.fc_dims = fc_dims
        # create input-output dimension pair for fully connect layers
        fc_dims_pair = list(zip([self.hidden_dims] + self.fc_dims, self.fc_dims + [self.output_dims]))
        self.lstm = nn.LSTM(
            input_size=self.input_dims,
            hidden_size=self.hidden_dims,
            batch_first=True,
            num_layers=self.lstm_layers_num
        )

        self.fcs = nn.Sequential()
        for i, dim_pair in enumerate(fc_dims_pair[:-1], 1):
            self.fcs.add_module(f'fc_{i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.fcs.add_module(f'relu {i}', nn.ReLU())

        self.fcs.add_module(f'output', nn.Linear(fc_dims_pair[-1][0], fc_dims_pair[-1][1]))

    def forward(self, x):
        """
        forward computation

        :param x: torch.tensor(m, n, q), train set. m is the batch size, n is the dimension of the states, q is the dimension of the inputs x in each state
        :return: out: torch.tensor(m, p), model output, m is the batch size, n is the dimension of the output
        """
        batch_size = x.shape[0]
        # init hidden state and cell to zero
        h0 = torch.zeros(self.lstm_layers_num, batch_size, self.hidden_dims).requires_grad_()
        c0 = torch.zeros(self.lstm_layers_num, batch_size, self.hidden_dims).requires_grad_()

        _, (hn, _) = self.lstm(x, (h0, c0))

        out = self.fcs(hn.view(-1, self.hidden_dims))

        return out

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



