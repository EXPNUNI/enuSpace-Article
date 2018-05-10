import os
import tensorflow as tf
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

a=tf.constant([3,2,-1,0], shape=[2,2])
b=tf.constant([3,5], shape=[2,1])
c=tf.matmul(a,b)

sess = tf.Session()
print(sess.run(c))