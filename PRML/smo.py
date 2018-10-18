#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

#------------------------------------------------------------------------------------------------------------
#                              Naive Implementation of SMO Algorithm for SVM
#------------------------------------------------------------------------------------------------------------
import numpy as np

class SMO(object):
    def __init__(self, C=100):
        # parameter C is the penalty coefficient of SVM
        self.C = C

    def fit(self, X, y, num_epoch=100, info=True):
        """
        This function will fit the svm model on a given dataset (X,y)
        -----
        X: Data set of input points. [ndarray] (x1, x2, x3, ...)
        y: lable of data points. [1D array]
        num_epoch: total iteration number of whole data set.
        info: to print learning information or not.
        -----
        """
        # the shape of data set
        num_point, dim_point = X.shape

        # initialize training parameters
        self.X = X
        self.y = y
        self.alphas = np.zeros(num_point)
        self.bias = 0

        for epoch in range(num_epoch):
            for i in range(num_point):
                # select another point randomly
                j = self.random_select(i, num_point)

                # error value on first point
                alpha_i, x_i, y_i  = self.alphas[i], self.X[i], self.y[i]
                E_i = self.get_error(x_i, y_i)

                # error value on second point
                alpha_j, x_j, y_j = self.alphas[j], self.X[j], self.y[j]
                E_j = self.get_error(x_j, y_j)

                # calculate clip range
                if y_i != y_j:
                    L = max(0, alpha_j - alpha_i)
                    H = min(self.C, self.C + alpha_j - alpha_i)
                else:
                    L = max(0, alpha_i + alpha_j - self.C)
                    H = min(self.C, alpha_j + alpha_i)

                # calculate new alpha_j
                K_ii, K_jj, K_ij = np.dot(x_i, x_i), np.dot(x_j, x_j), np.dot(x_i, x_j)
                eta = K_ii + K_jj - 2 * K_ij
                new_alpha_j = alpha_j + y_j * (E_i - E_j) / eta
                new_alpha_j = self.clip(new_alpha_j, L, H)
                # calculate new alpha_i
                new_alpha_i = alpha_i + y_i * y_j * (alpha_j - new_alpha_j)

                # update alphas
                self.alphas[i] = new_alpha_i
                self.alphas[j] = new_alpha_j

                # update bias
                bias_1 = -E_i - y_i * K_ii * (new_alpha_i - alpha_i) - y_j * K_ij * (new_alpha_j - alpha_j) + self.bias
                bias_2 = -E_j - y_i * K_ij * (new_alpha_i - alpha_i) - y_j * K_jj * (new_alpha_j - alpha_j) + self.bias
                if new_alpha_i > 0 and new_alpha_i < self.C:
                    self.bias = bias_1
                elif new_alpha_j > 0 and new_alpha_i < self.C:
                    self.bias = bias_2
                else:
                    self.bias = np.mean([bias_1, bias_2])

    def inference(self, x):
        x = np.matrix(x).T
        X = np.matrix(self.X)
        pred = np.matrix(self.alphas * self.y) * X * x + self.bias
        return pred[0, 0]

    def get_error(self, x, gt):
        """
        get the error of a data point
        -----
        x: a point vector
        gt: true label
        alpha alpha value relate to the point x
        -----
        """
        pred = self.inference(x)
        return pred - gt

    def random_select(self, except_item, top):
        """
        This function will select a number randomly from
        range [0, top] except except_item.
        """
        interval = list(range(top))
        selected = np.random.choice(interval)
        return selected if selected != except_item else self.random_select(except_item, top)

    def clip(self, val, low, high):
        if val < low:
            return low
        elif val > high:
            return high
        else:
            return val

# Test algorithm
if __name__ == "__main__":
    # ---------------------------- create a test case -----------------------------
    X = np.c_[(1.,2.), (2.,3.), (3.,3.), (2.,1.), (3.,2.)].T
    y = np.array([1.,1.,1.,-1.,-1.])
    svm = SMO(C=100)
    svm.fit(X, y, 100, False)

    # -------------------------- draw decision boundary ---------------------------
    import matplotlib.pyplot as plt
    def plot_decision_boundary(func, X = None, step=0.01):
        """
        Function to draw 2D decision boundary for 2D classification.
        -------
        func: pred function
        X: Dataset of input points
        step: interval from min to max value.
        -------
        """
        x_min, x_max = X[:,0].min() - 0.5, X[:,0].max() + 0.5
        y_min, y_max = X[:,1].min() - 0.5, X[:,1].max() + 0.5

        XX,YY = np.meshgrid(np.arange(x_min, x_max, step), np.arange(y_min, y_max, step))
        P = np.dstack([XX.ravel(), YY.ravel()])[0]
        Z = np.array(list(map(func, P)))
        Z = Z.reshape(XX.shape)

        plt.pcolormesh(XX, YY, Z > 0, cmap=plt.cm.Paired)
        plt.contour(XX, YY, Z, colors=['k', 'k', 'k'], linestyles=['--', '-', '--'], levels=[-1, 0, 1])
        plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Spectral)

    plot_decision_boundary(svm.inference, X, step=0.01)
    plt.show()
