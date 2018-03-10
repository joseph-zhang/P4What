#!usr/local/env python
#!coding=utf-8
# this file will show how to use dropout trick in our network

import tensorflow as tf
from sklearn.datasets import load_digits
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import LabelBinarizer

""" load data set BEGIN """
digits = load_digits()
X = digits['data'] # (1797, 64)
# label Binarization
y = LabelBinarizer().fit_transform(digits.target) # (1797, 10)
# X_tr, X_te : (1794, 64)
# y_tr, y_te : (1794, 10)
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size = 3)
""" load data set END """

# add a layer to graph
def add_layer(inputs, in_size, out_size, layer_name = 'layer', active_fun = lambda x: x):
    """ function to add a layer into NN """
    weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1)
    linear_struct = tf.matmul(inputs, weights) + biases
    outputs = active_fun(linear_struct)
    tf.summary.histogram(layer_name + '-outputs', outputs) # add this information on tensorboard
    return outputs

# set placeholders
keep_prob = tf.placeholder(tf.float32)
x_in = tf.placeholder(tf.float32, [None, 64])
y_in = tf.placeholder(tf.float32, [None, 10])

# add a hidden layer
hidden = add_layer(x_in, 64, 50, layer_name = 'hidden', active_fun = tf.nn.tanh)

# add output layer
pred = add_layer(hidden, 50, 10, layer_name = 'output', active_fun = tf.nn.softmax)

# loss function, cross-entropy loss
loss = tf.reduce_mean(-tf.reduce_sum(y_in * tf.log(pred), reduction_indices = [1]))
tf.summary.scalar('cross-entropy loss', loss) # add this information on tensorboard

# train task
train = tf.train.GradientDescentOptimizer(0.5).minimize(loss)

# variable initializer
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    merger = tf.summary.merge_all()
    train_writer = tf.summary.FileWriter('logs/train', sess.graph)
    test_writer = tf.summary.FileWriter('logs/test', sess.graph)

    # iteration times: 500
    for it in range(500):
        # note that here we add keep_prob item
        sess.run(train, feed_dict = {x_in: X_tr, y_in: y_tr, keep_prob: 1})
        # sess.run(train, feed_dict = {x_in: X_tr, y_in: y_tr, keep_prob: 0.5})
        if it % 50 == 0:
            train_res = sess.run(merger, feed_dict = {x_in: X_tr, y_in: y_tr, keep_prob: 1})
            test_res = sess.run(merger, feed_dict = {x_in: X_te, y_in: y_te, keep_prob: 1})
            train_writer.add_summary(train_res, it)
            test_writer.add_summary(test_res, it)
            
        



