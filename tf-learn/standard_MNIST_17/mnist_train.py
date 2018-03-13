#!usr/local/env python
#coding=utf-8
import os
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
from . import mnist_inference as MI

BATCH_SIZE = 100
LEARNING_RATE_BASE = 0.2
LEARNING_RATE_DECAY = 0.99
REGULARIZATION_RATE = 0.0001
TRAINING_STEPS = 30000
MOVING_AVERAGE_DECAY = 0.99

MODEL_SAVE_PATH = "./models/"
MODEL_NAME = "model.ckpt"

def train(mnist):
    x_in = tf.placeholder(tf.float32, [None, MI.INPUT_NODE], name = 'x-input')
    y_in = tf.placeholder(tf.float32, [None, MI.OUTPUT_NODE], name = 'y-input')
    
    reg = tf.contrib.layers.l2_regularizer(REGULARIZATION_RATE)
    pred = MI.inference(x_in, reg)

    global_step = tf.Variable(0, trainable = False)

    ema = tf.train.ExponentialMovingAverage(MOVING_AVERAGE_DECAY, global_step)
    ema_op = ema.apply(tf.trainable_variables())
    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits = pred,
                                                                   labels = tf.argmax(y_in, 1))
    cross_entropy_mean = tf.reduce_mean(cross_entropy)
    loss = cross_entropy_mean + tf.add_n(tf.get_collection('losses'))
    lr = tf.train.exponential_decay(LEARNING_RATE_BASE,
                                    global_step,
                                    mnist.train.num_examples / BATCH_SIZE,
                                    LEARNING_RATE_DECAY)
    train = tf.train.GradientDescentOptimizer(lr).minimize(loss, global_step = global_step)

    with tf.control_dependencies([train, ema_op]):
        train_op = tf.no_op(name = 'train')

    saver = tf.train.Saver()
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())

        for it in range(TRAINING_STEPS):
            xs, ys = mnist.train.next_batch(BATCH_SIZE)
            _, loss_val, step = sess.run([train_op, loss, global_step],
                                         feed_dict = {x_in: xs, y_in : ys})

            if it % 1000 == 0:
                print('After %d training steps, trianing loss is %g.'%(step, loss_val))
                saver.save(sess, os.path.join(MODEL_SAVE_PATH, MODEL_NAME),
                           global_step=global_step)

def main(argv = None):
    mnist = input_data.read_data_sets('../MNIST_data', one_hot = True)
    train(mnist)

if __name__ == '__main__':
    tf.app.run()
