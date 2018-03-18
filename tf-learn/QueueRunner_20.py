#!usr/bin/env python
#coding=utf-8
# example to show QueueRunner, which is used to control queue with multi-threading
import tensorflow as tf
import numpy as np

# define a FIFO queue
queue = tf.FIFOQueue(100, 'float')

# define an en-queue operation, which puts only one value
en_queue = queue.enqueue([tf.random_normal([1])])

# use 5 thread to put val in FIFO queue that we created concurrently
qrunner = tf.train.QueueRunner(queue, [en_queue] * 5)

# add this QueueRunner in default set tf.GraphKeys.QUEUE_RUNNERS
tf.train.add_queue_runner(qrunner)

# define dequeue operation
out_tensor = queue.dequeue()

with tf.Session() as sess:
    # create a coordinator
    coord = tf.train.Coordinator()
    # use this function to start all threads
    threads = tf.train.start_queue_runners(sess = sess, coord = coord)
    for _ in range(5):
        print(sess.run(out_tensor)[0])

    coord.request_stop()
    coord.join(threads)
