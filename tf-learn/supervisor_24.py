#!usr/bin/env python
#coding:utf-8
# beginner-NN implementation for showingthe usage of tf.train.Supervisor
# Nework structure: input_layer_size = 1, hiddden_layer_size = 10, outpit_layer_size = 1
import tensorflow as tf
import os
import numpy as np
import time


CHECK_POINTS_PATH = "./check_point"
MODEL_NAME = "model"

# set placeholders
x_in = tf.placeholder(tf.float32, [None, 1])
y_in = tf.placeholder(tf.float32, [None, 1])

"""
BEGIN
NETWORK DEFINITION
"""
# basic procedure for net construction
def add_layer(inputs, in_size, out_size, active_fun = lambda x: x):
    """ function to add a layer into NN """
    weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1)
    linear_struct = tf.matmul(inputs, weights) + biases
    outputs = active_fun(linear_struct)
    return outputs

# add a hidden layer
hd_1 = add_layer(x_in, 1, 10, active_fun = tf.nn.relu)

# add output layer
pred = add_layer(hd_1, 10, 1)
"""
END
NETWORK DEFINITION
"""


# loss function, L2
# understand parameter reduction_indicates, just like numpy axis
loss = tf.reduce_mean(tf.reduce_sum(tf.square(y_in - pred), reduction_indices = [1]))
# set lr = 0.1
train_op = tf.train.GradientDescentOptimizer(0.1).minimize(loss)


"""
USE SUPERVISOR
"""
global_step = tf.Variable(0, name = 'global_step')
global_step_inc = tf.assign(global_step, global_step + 1)
saver = tf.train.Saver([var for var in tf.model_variables()] + [global_step])

# summaries collection (although there is only one here)
tf.summary.scalar("total_loss", loss)

init = tf.global_variables_initializer()

sv = tf.train.Supervisor(logdir = CHECK_POINTS_PATH,
                         save_summaries_secs = 0, # do not let supervisor calculate summary automatically
                         saver = None, init_op = init) # do not let supervisor save model automatically

X_tr = np.linspace(-1, 1, 300)[:, np.newaxis] # np.linspace, np.newaxis
noise = np.random.normal(0, 0.05, X_tr.shape)
y_tr = np.square(X_tr) - 0.5 + noise # suppose the data set satisfy 2-level relationship
data_dict = {x_in: X_tr, y_in: y_tr}


def main():
    config = tf.ConfigProto()
    config.gpu_options.allow_growth = True
    
    with sv.managed_session(config = config) as sess:
        print('trainable variables: ')
        for var in tf.trainable_variables():
            print(var.name)
        start_time = time.time()
        for it in range(1000):
            fetches = {"train" : train_op,
                       "global_step" : global_step,
                       "global_step_inc" : global_step_inc}
            # set summary_freq 10
            if it % 10 == 0:
                fetches["loss"] = loss
                fetches["summary"] = sv.summary_op
                
            result = sess.run(fetches, feed_dict = data_dict)
            gs = result["global_step"]
            
            if it % 10 == 0:
                sv.summary_writer.add_summary(result["summary"], gs)
                print("step %d/1000, cost time %4.4f, loss :%f"\
                      %(gs, (time.time() - start_time), result["loss"]))
                start_time = time.time()

            # set model_save_freq 200
            if it % 200 == 0:
                print('Saving checkpoints ..')
                saver.save(sess, os.path.join(CHECK_POINTS_PATH, MODEL_NAME), global_step = gs)
            
if __name__ == "__main__":
    main()
