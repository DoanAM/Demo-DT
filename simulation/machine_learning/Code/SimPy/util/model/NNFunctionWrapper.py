import torch
from util.model.RegFunctionWrapper import  RegFunctionWrapper


class NNFunctionWrapper(RegFunctionWrapper):
    """
    This class contains specific functions for training a multilayer perception model and get the prediction. Learning
    method are based on the official tutorial https://pytorch.org/tutorials/beginner/basics/optimization_tutorial.html

    This class is only for single output model
    """
    @staticmethod
    def train_loop(dataloader_train, model, loss_fn, optimizer):
        """
        one training epoch with the whole train set

        :param dataloader_train: pytorch dataloader for train set
        :param model: model to be trained
        :param loss_fn: loss function
        :param optimizer: optimizer to update the weight
        :return: loss value
        """
        model.train()
        size = len(dataloader_train)
        total_loss = 0
        for batch_id, (X, y) in enumerate(dataloader_train):
            # forward
            pred = model(X)
            loss = loss_fn(pred, y)

            # Backpropagation
            # before a new update, it needs to clean the previous gradient
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            loss_this = loss.item()
            total_loss += loss_this
            if batch_id % 10 == 0:
                print(f"Loss: {loss_this} batch: [{batch_id + 1} / {size}]")
        print(f"Train Loss: {total_loss / size}")
        return total_loss

    @staticmethod
    def val_loop(dataloader_val, model, loss_fn):
        """
        validate the whole data set

        :param dataloader_val: pytorch dataloader for validation set
        :param model: pre-trained model
        :param loss_fn: torch loss function
        :return: average loss value on the whole validation set
        """
        # freeze weight
        model.eval()
        num_batches = len(dataloader_val)
        val_loss = 0.
        with torch.no_grad():
            for (X, y) in dataloader_val:
                pred = model(X)
                val_loss += loss_fn(pred, y).item()

        avg_val_loss = val_loss / num_batches
        print(f"Average MSE on Validation Set: {avg_val_loss}")
        return avg_val_loss

    @staticmethod
    def train(dataloader_train, dataloader_val, model, savepath, loss_fn, optimizer, epochs):
        """
        model learning

        :param dataloader_train: pytorch dataloader for train set
        :param dataloader_val: pytorch dataloader for validation set
        :param model: model to be trained
        :param savepath: model storage path
        :param loss_fn: pytorch loss function
        :param optimizer: pytorch optimizer
        :param epochs: int, number of training epochs
        :return: list[int], mes score in each epoch
        """
        history = []
        best_mse = float('inf')
        for e in range(epochs):
            print(f"Epoch {e+1} \n---------------------------------------")
            NNFunctionWrapper.train_loop(dataloader_train, model, loss_fn, optimizer)
            curr_val_loss = NNFunctionWrapper.val_loop(dataloader_val, model, loss_fn)
            history.append(curr_val_loss)
            if curr_val_loss < best_mse:
                best_mse = curr_val_loss
                model.save(savepath, best_mse)

        print("Done")
        return history

    @staticmethod
    def test(dataloader_eval, model, loss_fn):
        """
        model test, assumed the ground truth is given

        :param dataloader_eval: pytorch dataloader for test set
        :param model: pre-trained model
        :param loss_fn: pytorch loss function
        :return: y_pred: list[int], prediction value by model
        :return: y_true: list[int], ground truth
        """

        # freeze the weight
        model.eval()
        num_batches = len(dataloader_eval)
        eval_loss = 0.
        y_pred = []
        y_true = []
        with torch.no_grad():
            for (X, y) in dataloader_eval:
                pred = model(X)
                eval_loss += loss_fn(pred, y).item()
                y_pred.extend(pred.flatten().tolist())
                y_true.extend(y.flatten().tolist())
        avg_eval_loss = eval_loss / num_batches
        print(f"Average MSE on Validation Set: {avg_eval_loss}")

        return y_pred, y_true

    @staticmethod
    def predict(dataloader_test, model):
        """
        model inference, assumed that ground truth is not known

        :param dataloader_test: pytorch dataloader without true value
        :param model: pre-trained model
        :return: y_pred: list[int], prediction value by model
        """
        model.eval()
        y_pred = []
        with torch.no_grad():
            for X in dataloader_test:
                pred = model(X)
                y_pred.extend(pred.flatten().tolist())

        return y_pred


