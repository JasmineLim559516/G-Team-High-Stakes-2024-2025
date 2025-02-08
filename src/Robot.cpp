#pragma once
#include "api.h"
#include "Robot.hpp"


        pros::Controller m_controller {pros::E_CONTROLLER_MASTER}; 

        //robot constructor
        Robot::Robot(int8_t left1, int8_t left2, int8_t left3, int8_t right1, int8_t right2, int8_t right3, uint8_t port, int8_t intake1, int8_t intake2) :
            dt {left1,  left2,  left3,  right1,  right2,  right3},
            pneu {port},
            intake {intake1, intake2}
        {};



        //update robot components
        void Robot::update_intake(){
            int voltageToBeSet = 0;
            if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
                voltageToBeSet = 600;
            }
            else if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
                voltageToBeSet = -600;
            }
            intake.move(voltageToBeSet);
        }

        void Robot::update_drivetrain() {
            int turn = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); //for arcade control
            int left_power = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            int right_power = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

            //dt.tank_control(left_power, right_power);
            dt.arcade_control(left_power, turn);
        }

        void Robot::update_pneumatics() {
            if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
            {
                pneu.toggle_mogo();
            }
        }

    
        //update function for whole robot
        void Robot::update(std::string info){
            update_drivetrain();
            update_intake();
            update_pneumatics();
        }


        void Robot::auton(){
            dt.move_velocity(100, 100);
            pros::delay(2);
            dt.move_velocity(0, 0);
        }