import os
import tensorflow as tf
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

x_data = [1., 2., 3.]
y_data = [1., 2., 3.]

W = tf.Variable(tf.random_uniform([1],-10.0, 10.0))

X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

hyphothesis = W * X

cost = tf.reduce_mean(tf.square(hyphothesis - Y))

descent = W - tf.multiply(0.1,tf.reduce_mean(tf.multiply((tf.multiply(W,X)-Y),X)))

sess = tf.Session()
sess.run(tf.global_variables_initializer())

for step in range(31):
    sess.run(W.assign(descent), feed_dict={X:x_data, Y:y_data})
    print( step, sess.run(cost, feed_dict={X:x_data, Y:y_data}), sess.run(W))

