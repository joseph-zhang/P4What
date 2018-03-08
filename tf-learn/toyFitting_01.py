#!/usr/bin/env python
#!coding:utf-8
# step-01: use tensor flow to fitting an simple linear function

import tensorflow as tf
import numpy as np

# suppose we have some data wait for fitting task
# create some phony data
X_tr = np.random.rand(200).astype(np.float32) # float64 is default
y_tr = X_tr * 0.1 + 0.3 # actually, we know that the relationship is just a simple linear function

""" tensorflow structure defination """
# define some tensors
# tf.random_uniform: https://www.tensorflow.org/api_docs/python/tf/random_uniform
weights = tf.Variable(tf.random_uniform([1], -1.0, 1.0))
biases = tf.Variable(tf.zeros([1]))
y = weights * X_tr + biases

# L2 loss
loss = tf.reduce_mean(tf.square(y-y_tr))

# Inherits From Optimizer, set lr = 0.5
# tf.train.GradientDescentOptimizer: https://www.tensorflow.org/api_docs/python/tf/train/GradientDescentOptimizer
opti = tf.train.GradientDescentOptimizer(learning_rate = 0.5)

# throw our loss function in optimizer
train = opti.minimize(loss)
""" tensorflow structure defination """

# create a tensorflow session
sess = tf.Session()

# init variables
init = tf.global_variables_initializer()

# .run method: Runs operations and evaluates tensors in fetches
sess.run(init)

# 200 times iteration
for it in range(201):
    # run our optimization task once
    sess.run(train)
    if it % 10 == 0:
        print('itertime = %d'%(it), sess.run(weights), sess.run(biases))

