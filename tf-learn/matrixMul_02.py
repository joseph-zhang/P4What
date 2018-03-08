# this file show a simple matrix multiplication process
import tensorflow as tf

# define two constant tensors 
m1 = tf.constant([[3,3]])
m2 = tf.constant([[2],[2]])
# construct them 
product = tf.matmul(m1, m2)

with tf.Session() as sess:
    resmul = sess.run(product)
    print(resmul)
