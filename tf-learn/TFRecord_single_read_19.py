#!usr/bin/env python
#coding=utf-8
# suppose there is just a single TFRecord file
import tensorflow as tf

# create a reader
reader = tf.TFRecordReader()

file_queue = tf.train.string_input_producer(['./TFsave/mnist.tfrecords'])

_, serialized_example = reader.read(file_queue)

# names of key should be the same of previous one
feature_map = {'image_raw': tf.FixedLenFeature([], tf.string),
               'pixels': tf.FixedLenFeature([], tf.int64),
               'label': tf.FixedLenFeature([], tf.int64)} 

# here, use tf.parse_single_example() to deal with only one example
features = tf.parse_single_example(serialized_example, features = feature_map)

images = tf.decode_raw(features['image_raw'], tf.uint8)
pixels = tf.cast(features['pixels'], tf.int32)
labels = tf.cast(features['label'], tf.int32)


init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    coord = tf.train.Coordinator()
    threads = tf.train.start_queue_runners(sess = sess, coord = coord)
    for i in range(10):
        image, label, pixel = sess.run([images, labels, pixels])

