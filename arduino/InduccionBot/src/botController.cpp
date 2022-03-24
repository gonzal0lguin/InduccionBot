#include "botController.h"

/*

Motors must be arranged such that:
            .______.
    w1-> []-|  x   |-[] <- w2
            |  ^   |
            |  |->y|
    w3-> []-|      |-[] <- w4
            º------º
*/          


RobotController::RobotController(AF_DCMotor m0, AF_DCMotor m1, AF_DCMotor m2, AF_DCMotor m3){
    __motors[0] = m0;
    __motors[1] = m1;
    __motors[2] = m2;
    __motors[3] = m3;
}

void RobotController::compute_linear_combination(double x_vel, double y_vel, double w){
    /*
    This must take an input (like the ROS 4motor vector msg)
    and update the speeds accordingly to the motion algorithm

    TODO: I THINK IT SHOULD TAKE X & Y SPEEDS + AN ANGULAR SPEED, 
    AND THE COMPUTE EACH MOTOR VELOCITY
    */

    //__speeds = ...
    x_vel = x_vel == _NOCMD_ ? 0.0 : x_vel;
    y_vel = y_vel == _NOCMD_ ? 0.0 : y_vel;
    w = w == _NOCMD_ ? 0.0 : w;

    __speeds[0] = (int )((x_vel + y_vel - w * (__width_mm + __lenght_mm)) / __wheel_radius_mm) * 1000;
    __speeds[1] = (int )((x_vel - y_vel + w * (__width_mm + __lenght_mm)) / __wheel_radius_mm) * 1000;
    __speeds[2] = (int )((x_vel - y_vel - w * (__width_mm + __lenght_mm)) / __wheel_radius_mm) * 1000;
    __speeds[3] = (int )((x_vel + y_vel + w * (__width_mm + __lenght_mm)) / __wheel_radius_mm) * 1000;

    set_speeds();
}

void RobotController::forward(){
    for (int i= 0; i< N_MOTORS; i++){
        __speeds[i] = __def_vel;
    }
    set_speeds();
}

void RobotController::backward(){
    for (int i= 0; i< N_MOTORS; i++){
        __speeds[i] = -__def_vel;
    }
    set_speeds();
}

void RobotController::left(){
    __speeds[0] = -__def_vel;
    __speeds[1] = __def_vel;
    __speeds[2] = __def_vel;
    __speeds[3] = -__def_vel;
    set_speeds();
}

void RobotController::right(){
    __speeds[0] = __def_vel;
    __speeds[1] = -__def_vel;
    __speeds[2] = -__def_vel;
    __speeds[3] = __def_vel;
    set_speeds();
}

void RobotController::forward_right(){
    __speeds[0] = 0;
    __speeds[1] = __def_vel;
    __speeds[2] = __def_vel;
    __speeds[3] = 0;
    set_speeds();
}

void RobotController::forward_left(){
    __speeds[0] = __def_vel;
    __speeds[1] = 0;
    __speeds[2] = 0;
    __speeds[3] = __def_vel;
    set_speeds();
}

void RobotController::backward_right(){
    __speeds[0] = -__def_vel;
    __speeds[1] = 0;
    __speeds[2] = 0;
    __speeds[3] = -__def_vel;
    set_speeds();
}

void RobotController::backward_left(){
    __speeds[0] = 0;
    __speeds[1] = -__def_vel;
    __speeds[2] = -__def_vel;
    __speeds[3] = 0;
    set_speeds();
}

void RobotController::turn_right(){
    __speeds[0] = __def_vel;
    __speeds[1] = -__def_vel;
    __speeds[2] = __def_vel;
    __speeds[3] = -__def_vel;
    set_speeds();
}

void RobotController::turn_left(){
    __speeds[0] = -__def_vel;
    __speeds[1] = __def_vel;
    __speeds[2] = -__def_vel;
    __speeds[3] = __def_vel;
    set_speeds();
}

void RobotController::stop(){
    for (int i= 0; i< N_MOTORS; i++){
        __speeds[i] = 0;
    }
    set_speeds();
}

void RobotController::set_speeds(){
    for (int i= 0; i< N_MOTORS; i++){
        __motors[i].setSpeed(abs(__speeds[i]));
    }
}

void RobotController::run(){
    for (int i= 0; i< N_MOTORS; i++)
    {
        __dirs[i] = __speeds[i] > 0 ? FORWARD : BACKWARD;
        if (__speeds[i] == 0) __dirs[i] = RELEASE;
        __motors[i].run(__dirs[i]);
    }
}