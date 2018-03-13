#!usr/local/env python
#coding=utf-8
import time
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
from . import mnist_inference as MI
from . import mnist_train as MT
 
# load new model every 10s
EVAL_INTERVAL_SECS = 3

def evaluate(mnist):
    with tf.Graph().as_default() as g:
	# if you have only one server, use cpu to do validation
        with tf.device('/cpu:0'):
            x_in = tf.placeholder(tf.float32, [None, MI.INPUT_NODE], name = 'x-input')
            y_in = tf.placeholder(tf.float32, [None, MI.OUTPUT_NODE], name = 'y-input')

            validate_feed = {x_in: mnist.validation.images,
			     y_in: mnist.validation.labels}

            pred = MI.inference(x_in, None)

            correct_pred = tf.equal(tf.argmax(pred, 1), tf.argmax(y_in, 1))

            accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))

            # load model by using alias
            ema = tf.train.ExponentialMovingAverage(MT.MOVING_AVERAGE_DECAY)
            # create the dict we need
            variables_to_restore = ema.variables_to_restore()
            # reloader
            saver = tf.train.Saver(variables_to_restore)

        while True:
            # use config=tf.ConfigProto(log_device_placement=True) to check which device is used
            with tf.Session(config=tf.ConfigProto(log_device_placement=True)) as sess:
            	with tf.device('/cpu:0'):
                    # tf.train.get_checkpoint_state can load newest model by reading checkpoint file 
                    ckpt = tf.train.get_checkpoint_state(MT.MODEL_SAVE_PATH)
                    if ckpt and ckpt.model_checkpoint_path:
                        saver.restore(sess, ckpt.model_checkpoint_path)
                        global_step = ckpt.model_checkpoint_path.split('/')[-1].split('-')[-1]
                        accuracy_score = sess.run(accuracy, feed_dict = validate_feed)
                        print('After %s training steps, validation accuracy is %g.'%(global_step, accuracy_score))
                    else:
                        print('No checkpoint file found!')
                        return
                    time.sleep(EVAL_INTERVAL_SECS)

def main(argv = None):
    mnist = input_data.read_data_sets('../MNIST_data', one_hot = True)
    evaluate(mnist)

if __name__ == '__main__':
    tf.app.run()
