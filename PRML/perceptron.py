#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

#------------------------------------------------------------------------------------------------------------
#                               Naive implementation of perceptron algorithm
#------------------------------------------------------------------------------------------------------------
import numpy as np

class Perceptron(object):
    def __init__(self, eta=0.01):
        # \eta is learning rate
        self.eta = eta
        self.iter_errors = []

    def fit(self, X, y, num_epoch=100, info=True):
        # \mathbf{w} = \{w_i\} + w_0
        self.w = np.random.rand(1+X.shape[1])

        for epoch in range(num_epoch):
            error = 0
            for x_i, y_i in zip(X, y):
                # if gt == pred, then oe is zero
                oe = y_i - self.inference(x_i)

                # \mathbf{w}^{(\tau+1)} = \mathbf{w}^{(\tau)} + \eta\mathbf{x}_n t_n
                self.w[1:] += self.eta * oe * x_i
                self.w[0] += self.eta * oe
                error += int(oe != 0.)
            # number of misclassified pattern
            self.iter_errors.append(error)
            if(info): print("Epoch {}, error rate = {}".
                            format(epoch, self.iter_errors[epoch] / X.shape[0]))

    def inference(self, x):
        # y(\mathbf{x}) = f(\mathbf{w}^T\mathbf{x})
        return np.sign(np.dot(self.w[1:], x) + self.w[0])

# Test algorithm
if __name__ == "__main__":
    # ------------------------------ create a test case -----------------------------
    X = np.c_[(1.,2.), (2.,3.), (3.,3.), (2.,1.), (3.,2.)].T
    y = np.array([1.,1.,1.,-1.,-1.])
    perceptron = Perceptron(eta=0.01)
    perceptron.fit(X, y, 35, False)

    # ---------------------------- draw decision boundary ---------------------------
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

        plt.contourf(XX, YY, Z, cmap = plt.cm.Spectral)
        plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Spectral)

    plot_decision_boundary(perceptron.inference, X, step=0.005)
    plt.show()
