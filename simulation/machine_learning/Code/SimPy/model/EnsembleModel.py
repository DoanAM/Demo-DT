
class EnsembleModel:

    def __init__(self, regressor, **kwargs):
        self.container = {}
        self.regressor = regressor
        self.kwargs = kwargs


    def fit(self, df, selected_feature_cols, label_cols, by):
        pass
