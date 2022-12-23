from sklearn.linear_model import BayesianRidge
from sklearn.multioutput import MultiOutputRegressor
import pickle


class LinearRegression:
    """
    Bayesian linear regression For detailed information, please see
    https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.BayesianRidge.html
    """

    def __init__(self, mtype: str, n_iter: int):
        """

        :param mtype: str, model type, either 'base' for single output madel or 'multi' for multi-output model
        :param n_iter: int, iterations for optimization
        """
        self.mtype = mtype
        # init a single output model
        if self.mtype == "base":
            self.model = BayesianRidge(compute_score=True, n_iter=n_iter, verbose=True)
        # init a multiple output model
        elif self.mtype == "multi":
            self.model = MultiOutputRegressor(BayesianRidge(compute_score=True, n_iter=n_iter, verbose=True))
        else:
            raise ValueError(f"The input type: {mtype} is not existed in the linear regressor, please enter either 'base' or 'multi' to intial a linear regressor")


    def fit(self, X_train, y_train):
        """
        model training

        :param X_train: ndarray(m,n), input, m is the number of samples. n is the numbers of the features
        :param y_train: ndarray(m,),  output, m is the number of samples.
        :return: None
        """

        self.model.fit(X_train, y_train)

    def predict(self, X_test):
        """

        model inference

        :param X_test: ndarray(m,n), input, m is the number of samples. n is the numbers of the features
        :return: prediction value by model. If mtype is base, the uncertainty is also returned
        """
        if self.mtype == "base":
            return self.model.predict(X_test, return_std=True)
        elif self.mtype == "multi":
            return self.model.predict(X_test)

    def save(self, path):
        """
        save the model

        :param path: str, save path
        :return: None
        """
        pickle.dump(self.model, open(path, 'wb'))
        print(f"BLR model save in path {path}")

    def load(self, path):
        """
        load the model

        :param path: str, model path
        :return: None
        """
        self.model = pickle.load(open(path, 'rb'))
        print(f"BLR model load from path {path}")









