from sklearn.gaussian_process import GaussianProcessRegressor
import pickle


class GaussianProcessRegression:
    """
    gaussian process model with single output. For detailed information, please see
    https://scikit-learn.org/stable/modules/generated/sklearn.gaussian_process.GaussianProcessRegressor.html
    """

    def __init__(self, kernel, n_iters):
        """

        :param kernel: kernel for gaussian process
        :param n_iters: int, The number of restarts of the optimizer for finding the kernel’s parameters
        """
        self.model = GaussianProcessRegressor(kernel=kernel,
                                              n_restarts_optimizer=n_iters,
                                              normalize_y=False)

    def fit(self, X_train, y_train):
        """
        train a model

        :param X_train: ndarray(m,n), input, m is the number of samples. n is the numbers of the features
        :param y_train: ndarray(m,),  output, m is the number of samples.
        :return: None
        """
        self.model.fit(X_train, y_train)

    def predict(self, X_test):
        """
        model inference

        :param X_test: ndarray(m,n), input, m is the number of samples. n is the numbers of the features
        :return: prediction value by model
        """

        return self.model.predict(X_test, return_std=True)

    def get_kernel_parameters(self):
        """
        get used kernel parameters

        :return: kernel parameters
        """

        return self.model.kernel_.get_params()

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
