#ifndef BOT_CONTROLLER_H
#define BOT_CONTROLLER_H

#include <AFMotor.h>
#include <ArduinoSTL.h>

#define N_MOTORS 4
#define _NOCMD_ 9999


// el codigo tiene que estar pensado de tal manera que cada motor
// con un mensaje de ROS que crearemos nosotros que sera del tipo
// float: {speed_m0, speed_m1, speed_m2, speed_m3}

class RobotController {
    public:
        RobotController(AF_DCMotor m0, AF_DCMotor m1, AF_DCMotor m2, AF_DCMotor m3);
        void compute_linear_combination(double x_vel, double y_vel, double w);
        void forward();
        void backward();
        void left();
        void right();
        void forward_right();
        void forward_left();
        void backward_right();
        void backward_left();
        void turn_right();
        void turn_left();
        void stop();
        void set_speeds(); // dsps ver el formato en que se entrgan las velocidades
        void run();
    
    private:
        // mechanical parameters 
        double __width_mm = 140.5 / 2;
        double __lenght_mm = 110.0 / 2;
        double __wheel_radius_mm = 30.0;

        int __def_vel = 200;
        std::vector<AF_DCMotor> __motors;
        std::vector<uint8_t> __dirs;
        std::vector<int> __speeds;
};

#endif
