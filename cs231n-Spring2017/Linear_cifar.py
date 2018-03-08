#!/usr/bin/env python
#!coding:utf-8 
# the main procedure of linear classification
import random
import numpy as np
import matplotlib.pyplot as plt
from cs231n.Linearcon.linearclass import Linearog
from cs231n.csuti.cifartrans import cifar_trans

# first transfer data form
cifar_path = '../dataset/cifar-10-batches-py/'
X_train, y_train, X_val, y_val, X_test, y_test, X_dev, y_dev = cifar_trans(cifar_path)

# show the size of dataset
print (X_train.shape, X_val.shape, X_test.shape, X_dev.shape)

ller = Linearog()
loss_hist = ller.train(X_train, y_train,lr = 1e-7, reg = 5e4, num_iter = 1500,
                       batch_size = 20, observe = True )

plt.plot(loss_hist)
plt.xlabel('Iteration number')
plt.ylabel('Loss value')
plt.show()


              
