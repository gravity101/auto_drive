#!/usr/bin/python
#-*- coding: utf-8 -*-
import rospy
import numpy as np
import pickle
import tf
import time
import math

from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped, Quaternion
from std_msgs.msg import Float64
from frenet_converter import get_frenet, get_cartesian
from polynomials import QuinticPolynomial, QuarticPolynomial

def normalize_angle(angle):
    while angle > np.pi:
        angle -= 2.0 * np.pi

    while angle < -np.pi:
        angle += 2.0 * np.pi

    return angle


class FrenetPlanner(object):
    def __init__(self):
        self.rear_x = 0.0
        self.rear_y = 0.0
        self.yaw = 0.0
        self.v = 0.0

        self.acc_cmd = 0.0

        with open("map-file-path", "rb") as f:
            path = pickle.load(f)
            self.path = {
                'x': path['x'],
                'y': path['y'],
                'yaw': path['yaw'],
                's': [0.0]
            }
	    front_x = 0
	    front_y = 0 
            for i in range(len(path))
	    {
		path['s'][i] = math.hypot(path['x'][i] - front_x, path['y'][i] - front_y)
		front_x = path['x'][i]
		front_y = path['y'][i] 
            }

        self.ego_pose_sub = rospy.Subscriber("ego_pose", PoseStamped, self.PoseCallBack)
        self.speed_sub = rospy.Subscriber("ego_speed", Float64, self.CurSpeedCallBack)
        self.acc_cmd_sub = rospy.Subscriber("acc_cmd", Float64, self.AccCmdCallBack)


    def PoseCallBack(self, msg):
        self.rear_x = msg.pose.position.x
        self.rear_y = msg.pose.position.y
        orientation_q = msg.pose.orientation
        _, _, self.yaw = tf.transformations.euler_from_quaternion([
            orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w
        ])

    def CurSpeedCallBack(self, msg):
        self.v = msg.data

    def AccCmdCallBack(self, msg):
        self.acc_cmd = msg.data

    def Plan(self, target_speed):
        ## 1. get initial state in frenet

        ## 2. candidate conditions


        ## 3. longitudinal traj. candidates

        ## 4. lateral traj. candidates

        ## 5. Evaluate candidates

        ## 6. Get best trajectory

        ## 7. Transform the best traj into Cartesian
        xs, ys, yaws = [], [], []

        return xs, ys, yaws

    def GetPathMsg(self, xs, ys, yaws):
        ## transform planned trajectory xs, ys, yaws to PathMsg
        path_msg = Path()
        return path_msg

    def PlanAndGetPathMsg(self, target_speed):
        xs, ys, yaws = self.Plan(target_speed)
        path_msg = self.GetPathMsg(xs, ys, yaws)
        return path_msg



if __name__ == '__main__':
    rospy.init_node("planner_node")
    trajectory_pub = rospy.Publisher("planner/best_trajectory", Path, queue_size=1)

    planner = FrenetPlanner()
    r = rospy.Rate(10)
    while not rospy.is_shutdown():
        t0 = time.time()
        path_msg = planner.PlanAndGetPathMsg(20.0)
        t1 = time.time()
        print("t: %.1f ms" % ((t1-t0)*1e3))
        trajectory_pub.publish(path_msg)
        r.sleep()
