#!/usr/bin/python
#-*- coding: utf-8 -*-

import rospy
import numpy as np
import tf

from geometry_msgs.msg import PoseStamped, Pose, Point, Quaternion
from std_msgs.msg import Float64

class PIDController(object):
    def __init__(self):
        self.current_speed = 0.0
        self.p_gain = 0.5
        self.d_gain = 0.15
        self.i_gain = 0.01
        self.speed_sub = rospy.Subscriber("ego_speed", Float64, self.CurSpeedCallBack)

    def GetAccCmdMsg(self, target_speed):
        acc_cmd_msg = Float64()
	
	acc_cmd_msg.data = self.p_gain * (target_speed - self.current_speed)
	
	
	
	
	return acc_cmd_msg
	

    def CurSpeedCallBack(self, msg):
        self.current_speed = msg.data


if __name__ == '__main__':
    rospy.init_node("test_acc_node")
    acc_cmd_pub = rospy.Publisher("acc_cmd", Float64, queue_size=1)
    steering_angle_pub = rospy.Publisher("steering_angle_cmd", Float64, queue_size=1)

    target_speed = 7.0

    target_radius = 50.0
    delta = np.arctan2(3.14, target_radius)
    print(np.degrees(delta))

    controller = PIDController()
    r = rospy.Rate(100)

    while not rospy.is_shutdown():
        acc_cmd_msg = controller.GetAccCmdMsg(target_speed)
        acc_cmd_pub.publish(acc_cmd_msg)

        tmp_steering_angle_msg = Float64()
        tmp_steering_angle_msg.data = delta
        steering_angle_pub.publish(tmp_steering_angle_msg)
        r.sleep()
