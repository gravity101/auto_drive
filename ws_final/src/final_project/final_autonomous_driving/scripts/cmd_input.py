#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import sys
import select
import termios
import tty
from autonomous_msg.msg import *

msg = """
Control Your Vehicle!
---------------------------
Moving around:
        i
   j    k    l

q/z : increase/decrease max speeds by 10%
w/x : increase/decrease only linear accel by 10%
e/c : increase/decrease only angular speed by 10%
k: brake
space key: steering 0

CTRL-C to quit
"""

moveBindings = {
    'i': (1, 0),
    # 'k': (-1, 0),
    'j': (0, 1),
    'l': (0, -1)
}

speedBindings = {
    'q': (1.1, 1.1),
    'z': (.9, .9),
    'w': (1.1, 1),
    'x': (.9, 1),
    'e': (1, 1.1),
    'c': (1, .9),
}


def getKey():
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key


def vels(kAccel, kAngle):
    return "accel constant: %s\t angle constant: %s\t" % (kAccel, kAngle)


kAccel = 10.0
kAngle = 5.0
PI = 3.14159265358979323846

if __name__ == '__main__':
    settings = termios.tcgetattr(sys.stdin)

    rospy.init_node('driving_input')

    pub = rospy.Publisher('driving_input', VehicleInput, queue_size=10)

    accel = 0
    frontAngle = 0
    brake = 0
    try:
        print(msg)
        print(vels(kAccel, kAngle))
        rate = rospy.Rate(100)
        while(1):
            key = getKey()
            if key in moveBindings.keys():
                accel += moveBindings[key][0]*kAccel
                accel = sorted([0, accel, 100])[1]
                frontAngle += moveBindings[key][1]*kAngle
                frontAngle = sorted([-45, frontAngle, 45])[1]
                brake = 0.0
                print("accel : %s %%\t frontAngle : %s degree\t" %
                      (accel, frontAngle))

            elif key in speedBindings.keys():
                kAccel = kAccel * speedBindings[key][0]
                kAngle = kAngle * speedBindings[key][1]
                brake = 0.0
                print(vels(kAccel, kAngle))
            elif key == 'k':
                brake += kAccel*2.0
                brake = sorted([0, brake, 100])[1]
                print("brake : %s %%!!!!!!!!!!\t " % (brake))
            elif key == ' ':
                frontAngle = 0.0
                brake = 0.0
            else:
                accel -= kAccel*2.0
                accel = sorted([0, accel, 100])[1]
                brake = 0.0
                if (key == '\x03'):
                    break

            input = VehicleInput()
            input.accel = accel/100.0
            input.steering = frontAngle/180.0*PI
            input.brake = brake/100.0
            pub.publish(input)
            rate.sleep()

    except Exception as e:
        print(e)

    finally:
        input = VehicleInput()
        input.accel = 0
        input.brake = 0
        input.steering = 0
        pub.publish(input)

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
