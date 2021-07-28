#!/usr/bin/python
#-*- coding: utf-8 -*-

import rospy
import numpy as np
import tf
import pickle
import math
from stanley import StanleyControl

from geometry_msgs.msg import PoseStamped, Pose, Point, Quaternion
from std_msgs.msg import Float64

class StanleyController(object):
    def __init__(self):
        self.rear_x = 0.0
        self.rear_y = 0.0
        self.yaw = 0.0
        self.v = 0.0
        self.k_gain = 0.0

        with open("/home/a/xycar_ws/src/grepp_project_ws_template/src/path_follower/src/path.pkl") as f:
            self.path = pickle.load(f)

        self.ego_pose_sub = rospy.Subscriber("ego_pose", PoseStamped, self.PoseCallBack)
        self.ego_speed_sub = rospy.Subscriber("ego_speed", Float64, self.SpeedCallBack)

    def PoseCallBack(self, msg):
        self.rear_x = msg.pose.position.x
        self.rear_y = msg.pose.position.y
        
        _, _, yaw = tf.transformations.euler_from_quaternion((msg.pose.orientation.x,msg.pose.orientation.y,msg.pose.orientation.z,msg.pose.orientation.w))
        self.yaw = yaw

    def SpeedCallBack(self, msg):
        self.v = msg.data

    def GetSteeringAngleMsg(self):
        steer = StanleyControl(self.rear_x, self.rear_y, self.yaw, self.v, self.path['x'], self.path['y'], self.path['yaw'], 3.14, 0.5)
        steering_angle_msg = Float64()
        steering_angle_msg.data = steer
        return steering_angle_msg


class PIDController(object):
    def __init__(self):
        self.current_speed = 0.0
        self.p_gain = 0.5
        self.d_gain = 0.15
        self.i_gain = 0.01
        self.speed_sub = rospy.Subscriber("ego_speed", Float64, self.CurSpeedCallBack)

    def GetAccCmdMsg(self, target_speed):
        acc_cmd_msg = Float64()
        acc_cmd_msg = -self.p_gain*(self.current_speed-target_speed)
        return acc_cmd_msg

    def CurSpeedCallBack(self, msg):
        self.current_speed = msg.data

if __name__ == '__main__':
    rospy.init_node("stanley_follower_node")

    steering_angle_pub = rospy.Publisher("steering_angle_cmd", Float64, queue_size=1)
    acc_cmd_pub = rospy.Publisher("acc_cmd", Float64, queue_size=1)

    stanley = StanleyController()
    controller = PIDController()

    target_speed = 5.0

    r = rospy.Rate(10)
    while not rospy.is_shutdown():
        steering_angle_msg = stanley.GetSteeringAngleMsg()
        steering_angle_pub.publish(steering_angle_msg)

        acc_cmd_msg = controller.GetAccCmdMsg(target_speed)
        acc_cmd_pub.publish(acc_cmd_msg)
        r.sleep()
