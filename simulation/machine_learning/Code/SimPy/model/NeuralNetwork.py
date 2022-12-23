import torch
import torch.nn as nn


class NeuralNetwork(nn.Module):
    """
    multilayer perception with single output
    """

    def __init__(self, input_dims: int, hidden_dims: list[int], output_dims: int):
        """

        :param input_dims: int, the number of the features
        :param hidden_dims: list[int], output dimensions in each layer
        :param output_dims: int, the number of the output variables
        """
        super(NeuralNetwork, self).__init__()
        # create input-output dimension pair for each layer
        self.layer_dim_pair = list(zip([input_dims] + hidden_dims, hidden_dims + [output_dims]))
        self.model = nn.Sequential()

        for i, dim_pair in  enumerate(self.layer_dim_pair[:-1], 1):
            self.model.add_module(f'hidden layer {i}', nn.Linear(dim_pair[0], dim_pair[1]))
            self.model.add_module(f'relu {i}', nn.ReLU())

        # add output layer individually
        self.model.add_module(f'output', nn.Linear(self.layer_dim_pair[-1][0], self.layer_dim_pair[-1][1]))


    def forward(self, x):
        """

        forward computation

        :param x: torch.tensor(m, n, q), train set. m is the batch size, n is the dimension of the features
        :return: torch.tensor(m, p), model output, m is the batch size, n is the dimension of the output
        """

        return self.model(x)

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

    def print_model(self):
        """
        print the model structure

        :return: None
        """
        print(self.model)

