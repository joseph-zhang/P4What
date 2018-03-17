#!usr/bin/env python
#coding=utf-8
# An example of TFRecord data structure
# this program transfer MNIST data to TFRecord form
# use tf.train.Example to define the structure we need to save
# use tf.python_io.TFRecordWriter to write it
# Example <= Features <= map<string, Feature> <= 3 types
"""
message Example{
  Features features = 1;
};

message Features{
  map<string, Feature> feature = 1;
};

message Feature{
  oneof kind{
    Byteslist bytes_list = 1;
    FloatList float_list = 2;
    Int64List int64_list = 3;
  }
}
"""
import tensorflow as tf
import numpy as np
from tensorflow.examples.tutorials.mnist import input_data

# read mnist data in 'mnist'
mnist = input_data.read_data_sets('./MNIST_data', dtype = tf.uint8, one_hot = True)
images = mnist.train.images
labels = mnist.train.labels
pixels = images.shape[1]
# num_examples = images.shape[0]
num_examples = mnist.train.num_examples

# procedures to create feature
def _int64_feature(val):
    return tf.train.Feature(int64_list = tf.train.Int64List(value = [val]))

def _bytes_feature(val):
    return tf.train.Feature(bytes_list = tf.train.BytesList(value = [val]))

# the parameter is where you want to save
writer = tf.python_io.TFRecordWriter("./TFsave/mnist.tfrecords")

for i in range(num_examples):
    # use numpy.ndarray.tostring() to transfer numpy structure into a bytes string 
    image_raw = images[i].tostring()
    # define example
    map_feature = {'pixels': _int64_feature(pixels),
                   'label': _int64_feature(np.argmax(labels[i])),
                   'image_raw': _bytes_feature(image_raw)}
    features = tf.train.Features(feature = map_feature)
    example = tf.train.Example(features = features)
    writer.write(example.SerializeToString())
writer.close()
