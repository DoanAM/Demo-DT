import torch
from collections import defaultdict
from .RegFunctionWrapper import RegFunctionWrapper

class MTNFunctionWrapper(RegFunctionWrapper):
    """
    This class contains specific functions for training a multilayer perception model and get the prediction. Learning
    method are based on the official tutorial https://pytorch.org/tutorials/beginner/basics/optimization_tutorial.html

    This class is for the model with multi-outputs
    """

    @staticmethod
    def train_loop(dataloader_train, model, loss_fn, optimizer):
        """
        one training epoch with the whole train set

        :param dataloader_train: pytorch dataloader for train set
        :param model: model to be trained
        :param loss_fn: loss function
        :param optimizer: optimizer to update the weight
        :return: various loss values (total and each output variable)
        """
        # activate weight update
        model.train()
        size = len(dataloader_train)
        total_loss_sum = 0
        total_loss_s1 = 0
        total_loss_x = 0
        total_loss_y = 0
        total_loss_y2 = 0
        total_loss_z = 0

        for batch_id, (X, y) in enumerate(dataloader_train):
            # forward
            pred_s1, pred_x, pred_y, pred_y2, pred_z = model(X)
            y_s1 = y[:, 0].view(y.size(0), 1)
            y_x = y[:, 1].view(y.size(0), 1)
            y_y = y[:, 2].view(y.size(0), 1)
            y_y2 = y[:, 3].view(y.size(0), 1)
            y_z = y[:, 4].view(y.size(0), 1)

            loss_s1 = loss_fn(pred_s1, y_s1)
            loss_x = loss_fn(pred_x, y_x)
            loss_y = loss_fn(pred_y, y_y)
            loss_y2 = loss_fn(pred_y2, y_y2)
            loss_z = loss_fn(pred_z, y_z)

            loss_sum = loss_s1 + loss_x + loss_y + loss_y2 + loss_z

            # backpropagation
            optimizer.zero_grad()
            loss_sum.backward()
            optimizer.step()

            loss_sum_this = loss_sum.item()
            loss_s1_this = loss_s1.item()
            loss_x_this = loss_x.item()
            loss_y_this = loss_y.item()
            loss_y2_this = loss_y2.item()
            loss_z_this = loss_z.item()

            total_loss_sum += loss_sum_this
            total_loss_s1 += loss_s1_this
            total_loss_x += loss_x_this
            total_loss_y += loss_y_this
            total_loss_y2 += loss_y2_this
            total_loss_z += loss_z_this

            if batch_id % 10 == 0:
                print(f"Loss: {loss_sum_this} batch: [{batch_id + 1} / {size}]")
        print(f"Train Loss: {total_loss_sum / size}")
        return total_loss_sum, total_loss_s1, total_loss_x, total_loss_y, total_loss_y2, total_loss_z

    @staticmethod
    def val_loop(dataloader_val, model, loss_fn):
        """
        validate the whole data set

        :param dataloader_val: pytorch dataloader for validation set
        :param model: pre-trained model
        :param loss_fn: torch loss function
        :return: various average loss values(total and each output variable) on the whole validation set
        """

        # freeze the weight
        model.eval()
        num_batches = len(dataloader_val)
        val_loss_sum = 0.
        val_loss_s1 = 0.
        val_loss_x = 0.
        val_loss_y = 0.
        val_loss_y2 = 0.
        val_loss_z = 0.

        with torch.no_grad():
            for (X, y) in dataloader_val:
                y_s1 = y[:, 0].view(y.size(0), 1)
                y_x = y[:, 1].view(y.size(0), 1)
                y_y = y[:, 2].view(y.size(0), 1)
                y_y2 = y[:, 3].view(y.size(0), 1)
                y_z = y[:, 4].view(y.size(0), 1)
                pred_s1, pred_x, pred_y, pred_y2, pred_z = model(X)

                # summarize the batch mse
                val_loss_s1 += loss_fn(pred_s1, y_s1).item()
                val_loss_x += loss_fn(pred_x, y_x).item()
                val_loss_y += loss_fn(pred_y, y_y).item()
                val_loss_y2 += loss_fn(pred_y2, y_y2).item()
                val_loss_z += loss_fn(pred_z, y_z).item()

            val_loss_sum = val_loss_s1 + val_loss_x + val_loss_y + val_loss_y2 + val_loss_z

        # compute mse on the whole data set
        avg_val_loss_sum = val_loss_sum / num_batches
        avg_val_loss_s1 = val_loss_s1 / num_batches
        avg_val_loss_x = val_loss_x / num_batches
        avg_val_loss_y = val_loss_y / num_batches
        avg_val_loss_y2 = val_loss_y2 / num_batches
        avg_val_loss_z = val_loss_z / num_batches

        print(f"Average MSE on Validation Set: {avg_val_loss_sum}")
        return avg_val_loss_sum, avg_val_loss_s1, avg_val_loss_x, avg_val_loss_y, avg_val_loss_y2, avg_val_loss_z

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
        :return: dict, mes score of different outputs in each epoch
        """
        history = defaultdict(list)
        best_mse = float('inf')
        for e in range(epochs):
            print(f"Epoch {e + 1} \n---------------------------------------")
            MTNFunctionWrapper.train_loop(dataloader_train, model, loss_fn, optimizer)
            curr_val_loss_sum, curr_val_loss_s1, curr_val_loss_x, curr_val_loss_y, curr_val_loss_y2, curr_val_loss_z = MTNFunctionWrapper.val_loop(dataloader_val, model, loss_fn)
            history['total'].append(curr_val_loss_sum)
            history['S1ActTrq'].append(curr_val_loss_s1)
            history['XActTrq'].append(curr_val_loss_x)
            history['YActTrq'].append(curr_val_loss_y)
            history['Y2ActTrq'].append(curr_val_loss_y2)
            history['ZActTrq'].append(curr_val_loss_z)

            if curr_val_loss_sum < best_mse:
                best_mse = curr_val_loss_sum
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
        :return: y_pred: dict[list[float]], various prediction values by model
        :return: y_true: dict[list[float]], various ground truths
        """

        # freeze the weight
        model.eval()
        num_batches = len(dataloader_eval)
        eval_loss_sum = 0.
        eval_loss_s1 = 0.
        eval_loss_x = 0.
        eval_loss_y = 0.
        eval_loss_y2 = 0.
        eval_loss_z = 0.

        y_pred = defaultdict(list)
        y_true = defaultdict(list)
        with torch.no_grad():
            for (X, y) in dataloader_eval:
                y_s1 = y[:, 0].view(y.size(0), 1)
                y_x = y[:, 1].view(y.size(0), 1)
                y_y = y[:, 2].view(y.size(0), 1)
                y_y2 = y[:, 3].view(y.size(0), 1)
                y_z = y[:, 4].view(y.size(0), 1)
                pred_s1, pred_x, pred_y, pred_y2, pred_z = model(X)

                eval_loss_s1 += loss_fn(pred_s1, y_s1).item()
                eval_loss_x += loss_fn(pred_x, y_x).item()
                eval_loss_y += loss_fn(pred_y, y_y).item()
                eval_loss_y2 += loss_fn(pred_y2, y_y2).item()
                eval_loss_z += loss_fn(pred_z, y_z).item()

                y_pred['S1ActTrq'].extend(pred_s1.flatten().tolist())
                y_pred['XActTrq'].extend(pred_x.flatten().tolist())
                y_pred['YActTrq'].extend(pred_y.flatten().tolist())
                y_pred['Y2ActTrq'].extend(pred_y2.flatten().tolist())
                y_pred['ZActTrq'].extend(pred_z.flatten().tolist())

                y_true['S1ActTrq'].extend(y_s1.flatten().tolist())
                y_true['XActTrq'].extend(y_x.flatten().tolist())
                y_true['YActTrq'].extend(y_y.flatten().tolist())
                y_true['Y2ActTrq'].extend(y_y2.flatten().tolist())
                y_true['ZActTrq'].extend(y_z.flatten().tolist())

            eval_loss_sum = eval_loss_s1 + eval_loss_x + eval_loss_y + eval_loss_y2 + eval_loss_z
        avg_eval_loss = eval_loss_sum / num_batches
        print(f"Average MSE on Validation Set: {avg_eval_loss}")

        return y_pred, y_true

    @staticmethod
    def predict(dataloader_test, model):
        """
        model inference, assumed that ground truth is not known

        :param dataloader_test: pytorch dataloader without true value
        :param model: pre-trained model
        :return: y_pred, dict[list[float]], various prediction values by model
        """
        model.eval()
        y_pred = defaultdict(list)
        with torch.no_grad():
            for X in dataloader_test:
                pred_s1, pred_x, pred_y, pred_y2, pred_z = model(X)
                y_pred['S1ActTrq'].extend(pred_s1.flatten().tolist())
                y_pred['XActTrq'].extend(pred_x.flatten().tolist())
                y_pred['YActTrq'].extend(pred_y.flatten().tolist())
                y_pred['Y2ActTrq'].extend(pred_y2.flatten().tolist())
                y_pred['ZActTrq'].extend(pred_z.flatten().tolist())

        return y_pred


