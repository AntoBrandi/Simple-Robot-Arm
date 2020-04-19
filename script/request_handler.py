#!/usr/bin/env python
import rospy
from std_msgs.msg import Float64MultiArray
from sensor_msgs.msg import JointState

# function that publishes a message on the topic ,on which the 
# arduino is listening
def publish(msg):
    pub = rospy.Publisher('servo_actuator', Float64MultiArray, queue_size=10)
    pub.publish(msg)

# a new message has been published on the topic /move_group/fake_controller_joint_states
# this message is a sensor_msg/JointState message type
# get the data and publish those on the connected arduino as joint angles
def callback(data):
    anglesRad = data.position
    # conversion between radiants and degees
    anglesDeg = [angle*180/3.14 for angle in anglesRad]
    publish(anglesDeg)
    
def listener():
    rospy.init_node('request_handler', anonymous=True)
    # init the subscriber
    rospy.Subscriber("/move_group/fake_controller_joint_states", JointState, callback)
    
if __name__ == '__main__':
    listener()
    # keep this going
    rospy.spin()