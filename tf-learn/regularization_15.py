#!usr/local/env python
#coding=utf-8
# here is an example about regularization method to prevent overfitting
# collection structure in TF is also used
# a basic NN structure is implemented, we use raw API to do this instead of using tf.layers.xx
# to show the whole process better
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# create a weight matrix, and add L2 reg item on it
def get_weight(shape, lambda_val):
    init_weight = tf.Variable(tf.random_normal(shape), dtype = tf.float32)
    # add the reg items to tensorflow collection
    # note that name-param is the key for the collection
    tf.add_to_collection(name = 'losses',
                         value = tf.contrib.layers.l2_regularizer(lambda_val)(init_weight))
    return init_weight

def get_bias(shape):
    return tf.Variable(tf.constant(0.1, shape = shape))

def add_layer(inputs, in_size, out_size, active_fun = lambda x: x):
    weight = get_weight([in_size, out_size], 0.001)
    bias = get_bias([out_size])
    out = active_fun(tf.matmul(inputs, weight) + bias)
    return out

x_in = tf.placeholder(tf.float32, [None, 1])
y_in = tf.placeholder(tf.float32, [None, 1])

# add a hidden layer
hd_1 = add_layer(x_in, 1, 10, active_fun = tf.nn.relu)

# add output layer
pred = add_layer(hd_1, 10, 1)

# loss: mse
mse_loss = tf.reduce_mean(tf.square(y_in - pred))

# add mse_loss item to collection
tf.add_to_collection('losses', mse_loss)

# get all items of final loss funtion and add them up
loss = tf.add_n(tf.get_collection('losses'))

# set fixed lr = 0.1
train = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

# initialize all variables
init = tf.global_variables_initializer()

# create some phony data
X_tr = np.linspace(-1, 1, 300)[:, np.newaxis] # np.linspace, np.newaxis
noise = np.random.normal(0, 0.05, X_tr.shape)
y_tr = np.square(X_tr) - 0.5 + noise # suppose the data set satisfy 2-level relationship

# scatter graph of data
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.scatter(X_tr, y_tr)
plt.ion() # told plt to show images in sequence
plt.show()

# note that x_in and y_in will be changed in training steps
data_dict = {x_in: X_tr, y_in: y_tr}
with tf.Session() as sess:
    sess.run(init)
    for it in range(1000 + 1):
        sess.run(train,data_dict)
        if it % 50 == 0:
            if 'lines' in locals().keys():
                ax.lines.remove(lines[0])
            # calculate prediction value
            predict_val = sess.run(pred, feed_dict = {x_in: X_tr})
            # plot the prediction on graph
            lines = ax.plot(X_tr, predict_val, 'r-', lw = 5)
            plt.pause(0.1) # pause 0.1s 
            print('iter = %d, loss = '%(it), sess.run(loss, data_dict))
    plt.ioff()
    plt.show()

