# this file shows basic usage of tf.Variable
# variable, which means the value can be changed
import tensorflow as tf

# define a varaible, value is 0, name is 'counter'
counter = tf.Variable(0, name = 'counter')

# define a constant value
num_one = tf.constant(1)

# new value 
new_val = tf.add(counter, num_one)

# use tf.assign to change the value of variable
update = tf.assign(counter, new_val)

# note that, the variable must be initialized
init = tf.global_variables_initializer()

# main process flow
iter_num = 5
with tf.Session() as sess:
    sess.run(init)
    for _ in range(iter_num):
        sess.run(update)
        print(sess.run(counter))
