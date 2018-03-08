#!/usr/bin/env python
#!coding:utf-8
# this is a kind of 'hello world' like program for tensorflow
import tensorflow as tf
# build a simple graph
a = tf.constant(5.0)
b = tf.constant(6.0)
c = a*b

with tf.Session() as sess:
    print(sess.run(c))
