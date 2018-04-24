#!/usr/bin/env pyhthon
#coding=utf-8
#here is a simple implementation of alexnet, but with some modification
from __future__ import absolute_import # refuse implicit inner relative import
from __future__ import division
from __future__ import print_function

import tensorflow as tf
import numpy as np
import tensorflow.contrib.slim as slim # slim lib, today's leader

NUM_CLASSES = 1000
ALEX_TRAIN_ON = True
ALEX_TRAIN_OFF = False

def get_arg_scope(init_bias = 0.1, init_weight_decay = 0.0005):
    with slim.arg_scope([slim.conv2d, slim.fully_connected],
                        activation_fn = tf.nn.relu,
                        biases_initializer = tf.constant_initializer(init_bias),
                        weights_regularizer = slim.l2_regularizer(init_weight_decay)):
        with slim.arg_scope([slim.conv2d], padding = 'SAME'):
            with slim.arg_scope([slim.max_pool2d], padding = 'VALID') as scope_initializer:
                return scope_initializer

def alex_net(inputs,
             num_res = NUM_CLASSES,
             switch = ALEX_TRAIN_ON,
             dropout = 0.5,
             spatial_squeeze = True,
             scope_name = 'AlexNet'):
    with tf.variable_scope(scope_name, 'alex', [inputs]) as var_scope:
        endpoints_collection = var_scope.name + '_endpoints'
        with slim.arg_scope([slim.conv2d, slim.fully_connected, slim.max_pool2d],
                            outputs_collections = [endpoints_collection]):
            conv1 = slim.conv2d(inputs, 96, [11, 11], 4, padding = 'VALID', scope = 'conv1')
            pool1 = slim.max_pool2d(conv1, [3, 3], 2, scope = 'pool1')
            conv2 = slim.conv2d(pool1, 256, [5, 5], scope = 'conv2')
            pool2 = slim.max_pool2d(conv2, [3, 3], 2, scope = 'pool2')
            conv3 = slim.conv2d(pool2, 384, [3, 3], scope = 'conv3')
            conv4 = slim.conv2d(conv3, 384, [3, 3], scope = 'conv4')
            conv5 = slim.conv2d(conv4, 256, [3, 3], scope = 'conv5')
            pool5 = slim.max_pool2d(conv5, [3, 3], 2, scope = 'pool5')

            # fc layers is replaced of conv-layers
            with slim.arg_scope([slim.conv2d],
                                weight_initializer = tf.truncated_normal_initializer(0., 0.005),
                                biases_initializer = tf.constant_initializer(0.1)):
                net = slim.conv2d(pool5, 4096, [5, 5], padding = 'VALID', scope = 'fc6')
                net = slim.dropout(net, dropout, switch, scope = 'droptout6')
                net = slim.conv2d(net, 4096, [1, 1], scope = 'fc7')
                net = slim.dropout(net, dropout, switch, scope = 'dropout7')
                pred = slim.conv2d(net, NUM_CLASSES, [1, 1],
                                   activation_fn = None,
                                   normalizer_fn = None,
                                   biases_initializer = tf.zeros_initializer(),
                                   scope = 'fc8')
            end_points = slim.utils.convert_collection_to_dict(endpoints_collection)
            if spatial_squeeze:
                pred = tf.squeeze(pred, [1, 2], name = 'fc8/squeezed')
                end_points[var_scope.name + '/fc8'] = pred
            return pred, end_points
                
                
                
            

