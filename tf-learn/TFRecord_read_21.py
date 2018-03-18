#!usr/bin/env python
#coding=utf-8
# show how to read a list of TFRecord files
import tensorflow as tf
import numpy as np

"""
First, we write some code to simulate a big amount of dataset,
which is written in a few files as TFRecord form.
"""
def _int64_feature(val):
    return tf.train.Feature(int64_list = tf.train.Int64List(value = [val]))

# how many files?
num_shards = 5

# the amount of data in every file?
instances_per_shards = 3

# create some phony data and save them in a few number of files
for i in range(num_shards):
    # the name of files is defined as "0000n-of-0000m"
    filename = ('./TFsave/data.tfrecords-%.5d-of-%.5d'%(i, num_shards))
    writer = tf.python_io.TFRecordWriter(filename)
    for j in range(instances_per_shards):
        feature_map = {'i_id': _int64_feature(i),
                       'j_id': _int64_feature(j)}
        example = tf.train.Example(features = tf.train.Features(feature = feature_map))
        writer.write(example.SerializeToString())
    writer.close()

"""
Nowthat the data has been created, here is a procedure to read the file list
and load the data. Use QueueRunner and Coordinator to do this.
"""
# the parameter is a Regular expression like string
files = tf.train.match_filenames_once('./TFsave/data.tfrecords-*')

# create flilename queue
queue = tf.train.string_input_producer(files, shuffle = False)

# create a TFRecord reader
reader = tf.TFRecordReader()
# read an example from queue
_, serialized_example = reader.read(queue)

feature_map = {'i_id': tf.FixedLenFeature([], tf.int64),
               'j_id': tf.FixedLenFeature([], tf.int64)}

features = tf.parse_single_example(serialized_example, features = feature_map)

with tf.Session() as sess:
    # !!!! DO NOT USE tf.global_variables_initializer().run() HERE !!!!
    # here we use tf.local_variables_initializer() to initialize local variable 'num_epoch' in
    # tf.train.string_input_producer() function.
    tf.local_variables_initializer().run()
    print(sess.run(files))
    coord = tf.train.Coordinator()
    threads = tf.train.start_queue_runners(sess = sess, coord = coord)

    for i in range(6):
        print(sess.run([features['i_id'],
                        features['j_id']]))
    coord.request_stop()
    coord.join(threads)


