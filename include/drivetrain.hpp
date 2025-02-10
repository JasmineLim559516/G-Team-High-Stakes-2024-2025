#pragma once
#include "api.h"

class Drivetrain {
    private: 
        //initializes drivetrain motors
        pros::MotorGroup leftMotors;
        pros::MotorGroup rightMotors;
        
    public:
        //getters and setters

        //int32_t get_vertical_velocity(); //gets forward/backward velocity
        //int32_t get_turning_velocity(); //gets left/right velocity
        //int32_t get_avg_velocity(); //gets total velocity

        //constructor
        Drivetrain(int8_t left1, int8_t left2, int8_t left3, int8_t right1, int8_t right2, int8_t right3);


        void move_velocity(int left_velocity, int right_velocity);

        void arcade_control(int power, int turn);
        void tank_control(int left_power, int right_power);
};