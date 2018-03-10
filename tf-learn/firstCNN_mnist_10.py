#!usr/local/env python
#!coding=utf-8
# fist step for CNN learning, a CNN-version mnist sovler 

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
from tensorflow.examples.tutorials.mnist import input_data

"""
 this procedure will download and read the mnist data set automatically
 training data : (55000, 28 * 28 = 784)
 training labels : (10, )   
"""
mnist = input_data.read_data_sets('MNIST_data', one_hot=True)

# function to set weights
# https://www.tensorflow.org/api_docs/python/tf/truncated_normal
def weight_var(shape):
    initial = tf.truncated_normal(shape, stddev = 0.1)
    return tf.Variable(initial)

# function to set bias
# note that the bias should be initialized as small positive number(? => Relu)
def bias_var(shape):
    initial = tf.constant(0,1, shape = shape)
    return tf.Variable(initial)

# convolutional op
# https://www.tensorflow.org/api_docs/python/tf/nn/conv2d
def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides = [1, 1, 1, 1], padding = 'SAME')

# pooling op, 2x2 size
def max_pool(x):
    return tf.nn.max_pool(x, ksize = [1, 2, 2, 1],\
                          strides = [1, 2, 2, 1], padding = 'SAME')

# set placeholders
x_in = tf.placeholder(tf.float32, [None, 784])
y_in = tf.placeholder(tf.float32, [None, 10])
keep_prob = tf.placeholder(tf.float32)
x_image = tf.reshape(x_in, [-1, 28, 28, 1])

# conv-1
W_conv1 = weight_var([5, 5, 1, 32])
b_conv1 = bias_var([32])
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1) # 28x28x32
h_pool1 = max_pool(h_conv1) # 14x14x32

# conv-2
W_conv2 = weight_var([5, 5, 32, 64])
b_conv2 = bias_var([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2) # 14x14x64
h_pool2 = max_pool(h_conv2) # 7x7x64

# full-connection
W_fc1 = weight_var([7 * 7 * 64, 1024])
b_fc1 = bias_var([1024])
h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1) # ->  1x1024
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

# output, also full-connection
W_fec2 = weight_var([1024, 10]) 
b_fc2 = bias_var([10])
pred = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fec2) + b_fc2) # -> 1x10

# cross-entropy loss
loss = tf.reduce_mean(-tf.reduce_sum(y_in * tf.log(pred), reduction_indices = [1]))

# train task
train = tf.train.AdamOptimizer(1e-4).minimize(loss)

# recong accuracy
accuracy = tf.reduce_mean(tf.cast(tf.equal(tf.argmax(pred, 1),\
                                           tf.argmax(y_in, 1)),\
                                  tf.float32))
# variable initializer
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    for it in range(1000):
        x_tr, y_tr = mnist.train.next_batch(50)
        sess.run(train, feed_dict = {x_in : x_tr, y_in: y_tr, keep_prob: 0.5})
        if it % 100 == 0:
            # here, notice your graphic card's memory when calculate the acc
            acc_tr = sess.run(accuracy, feed_dict = {x_in : mnist.train.images[:2000],\
                                                     y_in: mnist.train.labels[:2000],\
                                                     keep_prob: 1.0})
            print('iter-', it, 'the training accuracy is ',acc_tr)
            # here, notice your graphic card's memory when calculate the acc
            acc_vali =  sess.run(accuracy, feed_dict = {x_in: mnist.validation.images[:2000],\
                                                        y_in: mnist.validation.labels[:2000],\
                                                        keep_prob: 1.0})
            print('iter-', it, 'the validation accuracy is ',acc_vali)
    acc_te =  sess.run(accuracy, feed_dict = {x_in: mnist.test.images[:2000],\
                                              y_in: mnist.test.labels[:2000],\
                                              keep_prob: 1.0})
    print('\n the result test accuracy is ', acc_te)
