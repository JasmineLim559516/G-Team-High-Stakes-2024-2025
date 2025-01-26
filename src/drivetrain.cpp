#pragma once
#include "api.h"
#include "drivetrain.hpp"

        //drivetrain constructor
        Drivetrain::Drivetrain(int8_t left1, int8_t left2, int8_t left3, int8_t right1, int8_t right2, int8_t right3) :
            leftMotors {{left1, left2, left3}},
            rightMotors {{right1, right2, right3}}
        {};

        // Drivetrain::Drivetrain(Drivetrain& t) :
        //     leftMotors {{t.leftMotors[0], t.leftMotors[1], t.leftMotors[2]}},
        //     rightMotors {{ t.rightMotors[0], t.rightMotors[1], t.rightMotors[2]}}
        // {};

        //getters and setters

        //int32_t get_vertical_velocity(); //gets forward/backward velocity
        //int32_t get_turning_velocity(); //gets left/right velocity
        //int32_t get_avg_velocity(); //gets total velocity

        void Drivetrain::move_velocity(int left_velocity, int right_velocity)
        {
            leftMotors.move_velocity(left_velocity);
            rightMotors.move_velocity(right_velocity);
        }

        void Drivetrain::arcade_control(int power, int turn) {
            int left = power + turn;
            int right = power - turn;
            leftMotors.move(left);
            rightMotors.move(right);

            //pros::delay(2);
        }

        void Drivetrain::tank_control(int left_power, int right_power) {
            leftMotors.move(left_power);
            // leftMotors.move_voltage(left_power * 100);
            rightMotors.move(right_power);
            // rightMotors.move_voltage(right_power * 100);


            // pros::delay(2);
        }