#!/usr/bin/python
#-*- coding: utf-8 -*-

import rospy
import numpy as np
import tf

from geometry_msgs.msg import PoseStamped, Pose, Point, Quaternion
from std_msgs.msg import Float64

class VehicleModel(object):
    def __init__(self, x, y, yaw, v, L=3.14):
        self.x = x
        self.y = y
        self.yaw = yaw
        self.v = v
        self.L = L
        self.a = 0.0
        self.delta = 0.0

        self.sub = rospy.Subscriber("acc_cmd", Float64, self.AccCmdCallBack)
        self.sub2 = rospy.Subscriber("steering_angle_cmd", Float64, self.SaCmdCallBack)

    def Move(self, dt=0.01):
        self.x = self.x + self.v * np.cos(self.yaw) * dt
	self.y = self.y + self.v * np.sin(self.yaw) * dt
	self.yaw += self.v / self.L * np.tan(self.delta) * dt
	self.yaw = self.yaw % (2.0 * np.pi)
	self.v += self.a * dt

    def AccCmdCallBack(self, msg):
        self.a = msg.data
	print(self.a)

    def SaCmdCallBack(self, msg):
        self.delta = msg.data

    def GetPoseStampedMsg(self):
        msg = PoseStamped()
        msg.header.frame_id = "/map"
        msg.header.stamp = rospy.Time.now()

        msg.pose.position.x = self.x
        msg.pose.position.y = self.y
        msg.pose.position.z = 0.0

        quat = tf.transformations.quaternion_from_euler(0, 0, self.yaw)
        msg.pose.orientation = Quaternion(*quat)

        return msg

    def GetSpeedMsg(self):
        msg = Float64()
        msg.data = self.v

        return msg


if __name__ == '__main__':
    rospy.init_node("ego_car_simulation_node")
    ego_pose_pub = rospy.Publisher("ego_pose", PoseStamped, queue_size=1)
    ego_speed_pub = rospy.Publisher("ego_speed", Float64, queue_size=1)
    print("Hello")
    ego_vehicle = VehicleModel(x=0.0, y=0.0, yaw=0.0, v=0.0, L=3.14)
    r = rospy.Rate(100)
    while not rospy.is_shutdown():
        ego_vehicle.Move(dt=0.01)
        pose_msg = ego_vehicle.GetPoseStampedMsg()
        speed_msg = ego_vehicle.GetSpeedMsg()

        ego_pose_pub.publish(pose_msg)
        ego_speed_pub.publish(speed_msg)
	print("Hello")
        r.sleep()
