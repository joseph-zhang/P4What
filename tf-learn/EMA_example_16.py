#!usr/local/env python
#coding=utf-8
# here a simple example of Exponential moving average method is shown
# When training a model, it is often beneficial to maintain moving averages of the trained parameters
# Evaluations that use averaged parameters sometimes produce significantly better results than the final trained values.
"""
 shadow_variable = decay * shadow_variable + (1 - decay) * variable
"""
# The optional num_updates parameter allows one to tweak the decay rate dynamically.
# This makes moving averages move faster. If passed, the actual decay rate used is:
"""
min(decay, (1 + num_updates) / (10 + num_updates))
"""
import tensorflow as tf
import numpy as np

# define two variables
v1 = tf.Variable(0, dtype = tf.float32)
v2 = tf.Variable(0, dtype = tf.float32)

# here, we use a variable to represent the it number in training process
it = tf.Variable(0, trainable = False)

# note that the decay is usually similar to 1
ema = tf.train.ExponentialMovingAverage(decay = 0.99,
                                        num_updates = it)

# define an operation 
main_averages_op = ema.apply([v1, v2])

# global iniitializer 
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    print('the original value of v1, v2 and their shadow values are')
    print(sess.run(([v1, ema.average(v1)], # [0., 0.]
                    [v2, ema.average(v2)]))) # [0., 0.]

    # suppose iter at 0, v1 and v2 have changed
    print('if v1 = 5, v2 = 3')
    sess.run(tf.assign(v1, 5)) 
    sess.run(tf.assign(v2, 3))
    sess.run(main_averages_op)
    print('now, the value become..')
    print(sess.run(([v1, ema.average(v1)], # min{0.99, (1+0)/(10+0)} = 0.1, 0.1*0+(1-0.1)*5 = 4.5 => [5., 4.5]]
                    [v2, ema.average(v2)])))  # 0.1*0+(1-0.1)*3 = 2.7 => [3., 2.7]

    print('\n')
    # suppose the iter become 1000
    print('now suppose 1000 iteration has been reached..')
    sess.run(tf.assign(it, 1000))
    print('if v1 = 10, v2 = 25')
    sess.run(tf.assign(v1, 10)) 
    sess.run(tf.assign(v2, 25))
    sess.run(main_averages_op)
    print('now, the value become..')
    print(sess.run(([v1, ema.average(v1)],
                    [v2, ema.average(v2)])))  
