#!usr/bin/env python
#coding=utf-8
import tensorflow as tf
import numpy as np
"""
training data : (55000, 28 * 28 = 784)
training labels : (10, )  
"""

INPUT_NODE = 784
LAYER1_NODE = 500
OUTPUT_NODE = 10

def get_weight(shape, regularizer):
    weights = tf.get_variable('weights', shape,
                             initializer = tf.truncated_normal_initializer(stddev=0.1))
    if not regularizer == None:
        tf.add_to_collection('losses', regularizer(weights))
    return weights

def inference(inputs, regularizer, reuse = False):
    with tf.variable_scope('layer1', reuse = reuse):
        weights = get_weight([INPUT_NODE, LAYER1_NODE], regularizer)
        biases = tf.get_variable('biases', [LAYER1_NODE],
                                 initializer = tf.constant_initializer(0.0))
        layer1 = tf.nn.relu(tf.matmul(inputs, weights) + biases)
    with tf.variable_scope('layer2', reuse = reuse):
        weights = get_weight([LAYER1_NODE, OUTPUT_NODE], regularizer)
        biases = tf.get_variable('biases', [OUTPUT_NODE],
                                 initializer = tf.constant_initializer(0.0))
        layer2 = tf.nn.relu(tf.matmul(layer1, weights) + biases)
        
    return layer2
