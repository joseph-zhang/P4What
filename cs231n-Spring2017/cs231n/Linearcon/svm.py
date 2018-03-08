# the svm method for linear classification
# calculate svm gradient and svm loss value for current weight W
# L = \sum_{j \neq y_i} \max(0, s_j-s_{y_i} + \Delta)
# s_j = f(x_i,W)_j
# grad(L,w) = \frac{\partial L}{\partial s} \frac{\partial s}{\partial w}

import numpy as np

def svm_loss(W, X, y, reg):
    num_train = X.shape[0]
    num_labels = W.shape[1]

    """ calculate the loss value, forward flow"""
    # initialize the weight gradient matrix
    calc = np.dot(X, W)
    real_calc = calc[np.arange(num_train), y] # understanced what this line do!
    # understance the usage of np.maximum
    margins = np.maximum(0, calc - real_calc.reshape(num_train,1) + 1.0) # note that delta here is 1
    margins[np.arange(num_train), y] = 0 # note that it should not be y_i
    # calculate loss value
    L = np.sum(margins) / float(num_train)
    # add regularization item
    L += 0.5 * reg * np.sum(W * W)

    """ calculate the gradient, backward flow"""
    dW = np.zeros(W.shape)
    ds = np.zeros_like(calc)
    ds[margins > 0] = 1
    ds[np.arange(num_train), y] -= np.sum(ds, axis = 1)
    
    # Matrix-Matrix multiply gradient
    # reference http://cs231n.stanford.edu/handouts/linear-backprop.pdf
    dW = np.dot(X.T, ds)
    # regularization item
    dW /= num_train
    dW += reg * W
    
    return L, dW
    
    
    
