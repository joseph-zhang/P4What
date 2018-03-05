# KNN interface for dataset
import numpy as np

class KNNer(object):
    def __init__(self):
        pass
    
    def train(self, X, y):
        """ 
        nothing to do/
        but memorize the data and labels
        """
        self.X_tr = X
        self.y_tr = y

    def predict(self, X, k = 1):
        """
        the vote number is k, preset 1/
        X is a test data from test set/
        return the predicted labels
        """
        
        num_test = X.shape[0]
        num_train = self.X_tr.shape[0]
        distance = np.zeros((num_test, num_train))
        distance = np.sqrt((-2 * np.dot(X, self.X_tr.T)) + np.sum(X**2, axis=1, keepdims=True) + np.sum(self.X_tr**2, axis=1))

        y_pred = np.zeros(num_test)
        for i in xrange(num_test):
            closest_y = []
            closest_y = self.y_train[np.argsort(dists[i, :])[:k]]
            y_pred[i] = np.argmax(np.bincount(closest_y))
        return y_pred

    
