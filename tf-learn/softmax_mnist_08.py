#!usr/bin/env python
#!coding=utf-8
# in this file, a simple softmax classifier is implemented
# use tensorflow inner function to process the mnist data

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

# define a funtion to add a layer into our network
def add_layer(inputs, in_size, out_size, layer_name = 'layer', active_fun = lambda x:x):
    weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1)
    Wx = tf.matmul(inputs, weights) + biases
    outputs = active_fun(Wx)
    return outputs

# placeholder
x_in = tf.placeholder(tf.float32, [None, 784])
y_in = tf.placeholder(tf.float32, [None, 10])

# just add a layer, use softmax funtion
pred = add_layer(x_in, 784, 10, layer_name = 'output_layer', active_fun = tf.nn.softmax)

# define loss function, cross entropy loss
loss = tf.reduce_mean(-tf.reduce_sum(y_in * tf.log(pred), reduction_indices = [1]))

# train task
train = tf.train.GradientDescentOptimizer(0.5).minimize(loss)

# recong accuracy
accuracy = tf.reduce_mean(tf.cast(tf.equal(tf.argmax(pred, 1),\
                                           tf.argmax(y_in, 1)),\
                                  tf.float32))
# initializer
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    for it in range(1500 + 1):
        # every time, we will send a random batch of data, which is, stochastic training
        batch_x, batch_y = mnist.train.next_batch(100)
        sess.run(train, feed_dict = {x_in: batch_x, y_in: batch_y})
        if it % 50 == 0:
            res = sess.run(accuracy, feed_dict = {x_in: mnist.test.images,\
                                                  y_in: mnist.test.labels})
            print('the accuracy: ', res)
            
        
        



