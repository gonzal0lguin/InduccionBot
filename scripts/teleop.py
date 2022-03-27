#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import Joy

EPS = 0.22
SPEED_FACTOR = 500

class teleJoy(object):
    def __init__(self):
        self.joy = rospy.Subscriber('/joy', Joy, self.__callback_func)
        self.pub = rospy.Publisher('/bot_vel', Float32MultiArray, queue_size=1)
        self.vels = [0.0, 0.0, 0.0, 0.0] #x, y, w, stop
        self.mode = 0

        print('Initialized')

    def __mode(self, mode_truth):
        """This function can be used to select between different
        modes of driving. Assing any button to any action you want.
        """
        pass

    def __callback_func(self, msg):
        """ Function to get called every time a new joystick msg
        is received.
        Args:
            msg (Joy): ROS msg containing bot speeds.
        """
        
        if (abs(msg.axes[1]) > EPS):
            self.vels[0] = msg.axes[1] * SPEED_FACTOR
        else: self.vels[0] = 0.0

        if (abs(msg.axes[0]) > EPS):
            self.vels[1] = msg.axes[0] * SPEED_FACTOR
        else: self.vels[1] = 0.0

        if (abs(msg.axes[3]) > EPS):
            self.vels[2] = msg.axes[3] * SPEED_FACTOR
        else: self.vels[2] = 0.0

        if msg.buttons[0] == 1: # stop button
            self.vels[3] = (self.vels[3] + 1) % 2
        
        arr_msg = Float32MultiArray()
        arr_msg.data = self.vels
        rospy.sleep(0.001)
        self.pub.publish(arr_msg)

        rospy.loginfo('Data received: {}'.format(self.vels))

    def __arr_pub(self, arr_msg):
        """ If there are more than one topic to publish, define a
        function to publish in order to make code cleaner.
        """
        pass



if __name__ == "__main__":
    rospy.init_node("bot_teleop_control")
    joy_ctrl = teleJoy()
    rospy.spin()
