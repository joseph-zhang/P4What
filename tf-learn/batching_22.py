#!usr/bin/env python
#coding=utf-8
# suppose that we have used method in _21 to read data from TFRecords 
import tensorflow as tf
import numpy as np

"""
code in TFRecord_read_21.py
"""
# create phony data
def _int64_feature(val):
    return tf.train.Feature(int64_list = tf.train.Int64List(value = [val]))
num_shards = 5
instances_per_shards = 3
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

# read from TFRecord files
files = tf.train.match_filenames_once('./TFsave/data.tfrecords-*')
queue = tf.train.string_input_producer(files, shuffle = False)
reader = tf.TFRecordReader()
_, serialized_example = reader.read(queue)
feature_map = {'i_id': tf.FixedLenFeature([], tf.int64),
               'j_id': tf.FixedLenFeature([], tf.int64)}
features = tf.parse_single_example(serialized_example, features = feature_map)

"""
Now, 'features' is what we have gained, 
here we can do some pre-transfer on data
"""
pass


"""
to enhance the performance of training stpes, it is better to 
compose these data become batches.

here, the method is: create a composition queue for composing examples.
function to create this kind of queue:
-   tf.train.batch()
-   tf.train.shuffle_batch()
there is a parameter named 'num_threads' in these functions, 
allowing queue use multi-thread to read examples.
"""

# an example of data
val, label = features['i_id'], features['j_id']
# thebatch size 
batch_size = 3
# the max capacity of batching queue
capacity = 1000 + 3 * batch_size
# create the batching queue contact with example data
"""
val_batch, label_batch = tf.train.batch([val, label],
                                        batch_size = batch_size,
                                        capacity = capacity,
                                        num_threads = 3)
"""

val_batch, label_batch = tf.train.shuffle_batch([val, label],
                                                batch_size = batch_size,
                                                capacity = capacity,
                                                min_after_dequeue = 30,
                                                num_threads = 3)
with tf.Session() as sess:
    tf.local_variables_initializer().run()
    tf.global_variables_initializer().run()
    coord = tf.train.Coordinator()
    threads = tf.train.start_queue_runners(sess = sess, coord = coord)

    # test the data
    for i in range(2):
        cur_val_batch, cur_label_batch = sess.run([val_batch, label_batch])
        print(cur_val_batch, cur_label_batch)

    coord.request_stop()
    coord.join(threads)
