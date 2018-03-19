#!usr/bin/env python
#coding=utf-8
import os
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import mnist_inference as MI

BATCH_SIZE = 100
LEARNING_RATE_BASE = 0.2
LEARNING_RATE_DECAY = 0.99
REGULARIZATION_RATE = 0.0001
TRAINING_STEPS = 10000
MOVING_AVERAGE_DECAY = 0.99

MODEL_SAVE_PATH = "./models"
MODEL_NAME = "model.ckpt"
TRAIN_SUMMARY_SAVE_PATH = "./logs/train"
VALI_SUMMARY_SAVE_PATH = "./logs/vali"

x_in = tf.placeholder(tf.float32, [None, MI.INPUT_NODE], name = 'x-input')
y_in = tf.placeholder(tf.float32, [None, MI.OUTPUT_NODE], name = 'y-input')

def evaluate(mnist):    
    vali_pred = MI.inference(x_in, None, True)
    correct_pred = tf.equal(tf.argmax(vali_pred, 1), tf.argmax(y_in, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))
    return accuracy
    
def train(mnist):
    reg = tf.contrib.layers.l2_regularizer(REGULARIZATION_RATE)
    pred = MI.inference(x_in, reg)

    global_step = tf.Variable(0, trainable = False)

    ema = tf.train.ExponentialMovingAverage(MOVING_AVERAGE_DECAY, global_step)
    ema_op = ema.apply(tf.trainable_variables())
    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits = pred,
                                                                   labels = tf.argmax(y_in, 1))

    cross_entropy_mean = tf.reduce_mean(cross_entropy)
    loss = cross_entropy_mean + tf.add_n(tf.get_collection('losses'))
    loss_log = tf.summary.scalar('loss', loss)

    lr = tf.train.exponential_decay(LEARNING_RATE_BASE,
                                    global_step,
                                    mnist.train.num_examples / BATCH_SIZE,
                                    LEARNING_RATE_DECAY)
    lr_log = tf.summary.scalar('learning_rate', lr)

    train = tf.train.GradientDescentOptimizer(lr).minimize(loss, global_step = global_step)

    with tf.control_dependencies([train, ema_op]):
        train_op = tf.no_op(name = 'train')
        
    validate_feed = {x_in: mnist.validation.images,
                     y_in: mnist.validation.labels}
    acc_rate = evaluate(mnist)
    acc_log = tf.summary.scalar('acc_rate', acc_rate)
    
    saver = tf.train.Saver()
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        #merger = tf.summary.merge_all()
        train_writer = tf.summary.FileWriter(TRAIN_SUMMARY_SAVE_PATH, sess.graph)
        vali_writer = tf.summary.FileWriter(VALI_SUMMARY_SAVE_PATH, sess.graph)
        
        for it in range(TRAINING_STEPS):
            xs, ys = mnist.train.next_batch(BATCH_SIZE)
            _, loss_val, step = sess.run([train_op, loss, global_step],
                                         feed_dict = {x_in: xs, y_in : ys})

            if it % 1000 == 0:
                print('After %d training steps, trianing loss is %g.'%(step, loss_val))

                acc_val = sess.run(acc_rate, feed_dict = validate_feed)
                print('After %d training steps, evaluation accuracy is %g.'%(step, acc_val))

                loss_train, lr_train = sess.run([loss_log, lr_log],
                                                feed_dict = {x_in: xs, y_in: ys})
                acc_vali = sess.run(acc_log, validate_feed)
                train_writer.add_summary(loss_train, step)
                train_writer.add_summary(lr_train, step)
                vali_writer.add_summary(acc_vali, step)
                
            if it % 5000 == 0: 
                saver.save(sess, os.path.join(MODEL_SAVE_PATH, MODEL_NAME),
                           global_step=global_step)


mnist = input_data.read_data_sets('/MNIST_data', one_hot = True)
train(mnist)
