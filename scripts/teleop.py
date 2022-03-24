#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import Joy

EPS = 0.22
SPEED_FACTOR = 1000

class teleJoy(object):
    def __init__(self):
        self.joy = rospy.Subscriber('/joy', Joy, self.__callback_func)
        self.pub = rospy.Publisher('/bot_vel', Float32MultiArray, queue_size=1)
        self.vels = [0.0, 0.0, 0.0, 0.0] #x, y, w, stop
        self.mode = 0

        print('Initialized')

    def __mode(self, mode_truth):
        pass

    def __callback_func(self, msg):
        if (abs(msg.axes[1]) > EPS):
            self.vels[0] = msg.axes[1] * SPEED_FACTOR
        else: self.vels[0] = 0.0

        if (abs(msg.axes[0]) > EPS):
            self.vels[1] = msg.axes[0] * SPEED_FACTOR
        else: self.vels[1] = 0.0

        if (abs(msg.axes[3]) > EPS):
            self.vels[2] = msg.axes[3] * SPEED_FACTOR
        else: self.vels[2] = 0.0

        self.vels[3] = msg.buttons[0] # stop button

        arr_msg = Float32MultiArray()
        arr_msg.data = self.vels
        rospy.sleep(0.001)
        self.pub.publish(arr_msg)

        rospy.loginfo('Data received: {}'.format(self.vels))

    def __arr_pub(self, arr_msg):
        pass



if __name__ == "__main__":
    rospy.init_node("bot_teleop_control")
    jot_ctrl = teleJoy()
    rospy.spin()


# BUTTONS
#    13
#  11  12  
#    14

# a: 0
# B: 1
# X: 2
# Y: 3  
# LB: 4
# RB: 5
