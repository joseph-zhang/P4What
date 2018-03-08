# this file give a simple example about how to set placeholder
# a placeholder can hold data from outer form
import tensorflow as tf

# define two holders as float32 type
input1 = tf.placeholder(tf.float32)
input2 = tf.placeholder(tf.float32)

# define multiply structure
output = tf.multiply(input1, input2)

# create some phony data
data_in = {input1: [7.], input2: [2.]}

# the data will be send in tf through .run() method
with tf.Session() as sess:
    res = sess.run(output, data_in)
    print(res) # [14.]
