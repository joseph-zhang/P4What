#!usr/local/env python
#!coding=utf-8
# fist step for CNN learning, a better CNN-version mnist sovler than the 10 one
# use advanced API and functions, optimizer structure at the same time

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

# set placeholders
x_in = tf.placeholder(tf.float32, [None, 784])
y_in = tf.placeholder(tf.float32, [None, 10])
drop_switch = tf.placeholder(tf.bool)
x_image = tf.reshape(x_in, [-1, 28, 28, 1])


# conv-1, used in tensorflow newversion
# this version is Packaging better than old tf.nn.conv2d
conv_1 = tf.layers.conv2d(inputs = x_image, filters = 32, kernel_size = 5,
                          strides = 1, padding = 'same', activation = tf.nn.relu)

# pool-1, used in tensorflow nerversion
# this version is Packaging better than old tf.nn.max_pool
pool_1 = tf.layers.max_pooling2d(inputs = conv_1, pool_size = 2,
                                 strides = 2, padding = 'same')

# conv-2
conv_2 = tf.layers.conv2d(pool_1, filters = 64, kernel_size = 5,
                          strides = 1, padding = 'same', activation = tf.nn.relu)

# pool-2
pool_2 = tf.layers.max_pooling2d(inputs = conv_2, pool_size = 2,
                              strides = 2, padding = 'same')

# fc-1
pool2_flat = tf.reshape(pool_2, [-1, 7*7*64])
dense_1 = tf.layers.dense(inputs = pool2_flat, units = 1024,
                          activation = tf.nn.relu)
# drop out layer
dropout = tf.layers.dropout(inputs=dense_1, rate=0.4, training = drop_switch)

# fc-2
dense_2 = tf.layers.dense(inputs = dropout, units = 10,
                          activation = None)

# y_pred
pred = tf.nn.softmax(dense_2)

# loss: cross-loss
loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels = y_in, logits = dense_2))

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
        sess.run(train, feed_dict = {x_in : x_tr, y_in: y_tr, drop_switch: True})
        if it % 100 == 0:
            # here, notice your graphic card's memory when calculate the acc
            acc_tr = sess.run(accuracy, feed_dict = {x_in : mnist.train.images[:2000],\
                                                     y_in: mnist.train.labels[:2000],\
                                                     drop_switch: False})
            print('iter-', it, 'the training accuracy is ',acc_tr)
            # here, notice your graphic card's memory when calculate the acc
            acc_vali =  sess.run(accuracy, feed_dict = {x_in: mnist.validation.images[:2000],\
                                                        y_in: mnist.validation.labels[:2000],\
                                                        drop_switch: False})
            print('iter-', it, 'the validation accuracy is ',acc_vali)
    acc_te =  sess.run(accuracy, feed_dict = {x_in: mnist.test.images[:2000],\
                                              y_in: mnist.test.labels[:2000],\
                                            drop_switch: False})
    print('\n the result test accuracy is ', acc_te)
                                                

