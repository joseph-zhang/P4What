#!/usr/bin/env python
#!coding:utf-8
# here is just a beginner-NN implementation
# Nework structure: input_layer_size = 1, hiddden_layer_size = 10, outpit_layer_size = 1
# note that this is tensorflow-2017 version, some advanced APIs are used
# compare this program to first_NN_05.py
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# phony data
x_tr = np.linspace(-1, 1, 100)[:, np.newaxis]
noise = np.random.normal(0, 0.1, size = x_tr.shape)
y_tr = np.power(x_tr, 2) + noise

# set placeholders
x_in = tf.placeholder(tf.float32, [None, 1])
y_in = tf.placeholder(tf.float32, [None, 1])


# add a hidden layer
hd_1 = tf.layers.dense(x_in, 10, tf.nn.relu,
                       bias_initializer = tf.constant_initializer(0.1))

# add output layer
pred = tf.layers.dense(hd_1, 1,
                       bias_initializer = tf.constant_initializer(0.1))

# loss function, L2
loss = tf.losses.mean_squared_error(y_in, pred)

# set lr = 0.1
train = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

# initialize all variables
init = tf.global_variables_initializer()

# scatter graph of data
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.scatter(x_tr, y_tr)
plt.ion() # told plt to show images in sequence
plt.show()

data_dict = {x_in: x_tr, y_in: y_tr}
with tf.Session() as sess:
    sess.run(init)
    for it in range(1000 + 1):
        sess.run(train, data_dict)
        if it % 50 == 0:
            if 'lines' in locals().keys():
                ax.lines.remove(lines[0])
            # calculate prediction value
            predict_val = sess.run(pred, feed_dict = {x_in: x_tr, y_in: y_tr})
            # plot the prediction on graph
            lines = ax.plot(x_tr, predict_val, 'r-', lw = 5)
            plt.pause(0.1) # pause 0.1s 
            print('iter = %d, loss = '%(it), sess.run(loss, data_dict))
    plt.ioff()
    plt.show()


