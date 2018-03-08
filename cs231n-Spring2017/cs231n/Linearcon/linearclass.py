# the main class of linear classification
# contains SVM and Softmax methods
import numpy as np
from . import svm
from . import softmax

class Linearog(object):
    # constructor, initialize the method(svm, softmax) and weight variable
    # if select is 0, use svm, else use softmax 
    def __init__(self,select = 0):
        if not select:
            self.lossmethod = svm.svm_loss
            print('svm loss is selected..\n')
        else:
            self.lossmethod = softmax.softmax_loss
            print('softmax loss is selected..\n')
        self.W = None
    # main procedure, training the data
    def train(self, X, y, lr = 1e-3, reg=1e-5, num_iter = 100,
              batch_size = 20, observe = True):
        num_tr, data_dim = X.shape
        num_labels = y.shape[0]
        if self.W is None: self.W = 0.0001 * np.random.randn(data_dim,num_labels)

        loss_table = []

        # iteration procedure, SGD is used
        for i in range(num_iter):
            # select a batch of data from training set randomly
            batchids = np.random.choice(num_tr, batch_size)
            # get the training data and labels
            X_train = X[batchids]
            y_train = y[batchids]

            # calculate loss and gradient by using a kind of method
            loss,grad = self.lossmethod(self.W, X_train, y_train, reg)
            loss_table.append(loss)
            # renew the weights
            self.W -= lr * grad

            if observe and i % 50 == 0:
                print('iter %d, loss = %f' %(i, loss))
        return loss_table

    # predict which label it is from the input data
    def predict(self, X):
        y_pred = np.zeros(X.shape[1])
        y_pred = np.argmax(np.dot(X, self.W), axis = 1)
        return y_pred
    
            
        
