#include <Arduino.h>
#include "botController.h"
#include "parser.h"
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>


AF_DCMotor m0(1, MOTOR12_64KHZ);
AF_DCMotor m1(2, MOTOR12_64KHZ);
AF_DCMotor m2(3, MOTOR12_64KHZ);
AF_DCMotor m3(4, MOTOR12_64KHZ);

RobotController bot(m3, m2, m1, m0);
ros::NodeHandle nh;

void callback_func(const std_msgs::Float32MultiArray & cmd_msg){
  double x_vel = cmd_msg.data[0];
  double y_vel = cmd_msg.data[1];
  double w = cmd_msg.data[2];
  bot.compute_linear_combination(x_vel, y_vel, w);
  nh.loginfo("info received");

}

ros::Subscriber<std_msgs::Float32MultiArray> bot_vel("/bot_vel", callback_func);


void setup() {
  Serial.begin(BAUD_RATE);
  nh.initNode();
  nh.subscribe(bot_vel);
}

void loop() {
  nh.spinOnce();
  delay(1);
  bot.run();
}