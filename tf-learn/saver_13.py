#!usr/local/env python
#coding=utf-8
# this file shows how to save and reload the model we trained
# matmaul example is used here, use function tf.train.Saver()
import tensorflow as tf
import numpy as np

# define two constant tensors 
m1 = tf.Variable([[3,3]], dtype = tf.int32)
m2 = tf.Variable([[2],[2]], dtype = tf.int32)
# construct them 
res = tf.matmul(m1, m2)

# set a saver
all_saver = tf.train.Saver()
saver = tf.train.Saver({"my_m1": m1,
                        "my_m2": m2})

# initializer
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    save_Path = saver.save(sess, './store/') # save current session variables here
    print('trained-model has been saved')
    
m1_reload = tf.Variable([[0,0]])
m2_reload = tf.Variable([[0],[0]])

# set a new saver
saver1 = tf.train.Saver({"my_m1": m1_reload,
                         "my_m2": m2_reload})

with tf.Session() as sess:
    print('now reload this model..')
    saver1.restore(sess, './store/')
    print('reloading end.')
    print('reload m1 is ', sess.run(m1_reload))
    print('reload m2 is ', sess.run(m2_reload))
