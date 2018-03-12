#!usr/local/env python
#coding=utf-8
# a method to setting proper learning rate should make sure it would not be too large or small
# some function in tensorflow will help us to do this， (eg. tf.train.exponential_decay)
# here, we use baisc NN structure to show this
# the learning rate of this method can be represented as
"""
decayed_learning_rate = learning_rate * \
                        decay_rate ^ (global_step / decay_steps)
"""
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

# Global step to use for the decay computation. Must not be negative.
global_step = tf.Variable(0, trainable=False)

# note that if the argument staircase is True,
# then global_step / decay_steps is an integer division 
lr = tf.train.exponential_decay(learning_rate = 0.1,
                                global_step = global_step,
                                decay_steps = 100,
                                decay_rate = 0.96,
                                staircase = True)

# set decayed lr
train = tf.train.GradientDescentOptimizer(lr)\
                .minimize(loss, global_step = global_step)

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
