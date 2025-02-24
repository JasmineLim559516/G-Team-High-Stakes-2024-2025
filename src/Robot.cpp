#pragma once
#include "api.h"
#include "Robot.hpp"
#include "lemlib/api.hpp"  //IWYU pragma: keep
#include "ports.hpp"


        pros::Controller m_controller {pros::E_CONTROLLER_MASTER}; 

        //robot constructor
        Robot::Robot(int8_t left1, int8_t left2, int8_t left3, int8_t right1, int8_t right2, int8_t right3, uint8_t a_pneu, int8_t intake1, int8_t intake2, uint8_t a_flag) :
            dt {left1,  left2,  left3,  right1,  right2,  right3},
            pneu {a_pneu},
            intake {intake1, intake2},
            flag {a_flag}
        {};



        //update robot components
        void Robot::update_intake(){
            //press
            // int voltageToBeSet = 0;
            // if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            //     voltageToBeSet = 600;
            // }
            // else if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            //     voltageToBeSet = -600;
            // }
            // intake.move(voltageToBeSet);

            //toggle
            if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
                if (intake.get_velocity() == 150) {
                    intake.set_velocity(0);
                }
                else {
                    intake.set_velocity(150);
                }
            }
            if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
                if (intake.get_velocity() == -50) {
                    intake.set_velocity(0);
                }
                else {
                    intake.set_velocity(-50);
                }
            }
            intake.move(intake.get_velocity());
        }

        void Robot::update_drivetrain() {
            pros::MotorGroup left_side_motors({ports::LEFT_FRONT_TOP_DT, ports::LEFT_FRONT_BOTTOM_DT, ports::LEFT_BACK_DT}, pros::MotorGearset::blue);
            pros::MotorGroup right_side_motors({ports::RIGHT_FRONT_TOP_DT, ports::RIGHT_FRONT_BOTTOM_DT, ports::RIGHT_BACK_DT}, pros::MotorGearset::blue);

            lemlib::Drivetrain drivetrain(
                &left_side_motors, //left motor group
                &right_side_motors, //right motor group
                14.9, //track width
                3.25, //wheel diameter
                450, //drivetrain rpm
                2 //horizontal drift
            );

            pros::Imu intertial_sensor(11); //add port

            lemlib::OdomSensors sensors(
	            nullptr,
	            nullptr,
	            nullptr,
	            nullptr,
	            &intertial_sensor
            );

            // forward/backward PID
            lemlib::ControllerSettings lateralController(
	            7, // proportional gain (kP)
                0, // integral gain (kI)
                3, // derivative gain (kD)
                3, // anti windup
                1, // small error range, in inches
                100, // small error range timeout, in milliseconds
                3, // large error range, in inches
                500, // large error range timeout, in milliseconds
                10 // maximum acceleration (slew)
            );

            // turning PID
            lemlib::ControllerSettings angularController(
	            2.15, // proportional gain (kP)
                0, // integral gain (kI)
    12, // derivative gain (kD)
    0, // anti windup
    0, // small error range, in inches
    0, // small error range timeout, in milliseconds
    0, // large error range, in inches
    0, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
	10, // minimum output where drivetrain will move out of 127
	1.019 // expo curve gain
);

            // input curve for steer input during driver control
            lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                10, // minimum output where drivetrain will move out of 127
                1.019 // expo curve gain
            );

            lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors, &throttle_curve, &steer_curve);


            int turn = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); //for arcade control
            int left_power = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            int right_power = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

            //dt.tank_control(left_power, right_power);  //beginner
            //dt.arcade_control(left_power, turn);  //arcade

            //chassis.arcade(left_power, turn);  //zoya/dristi
            chassis.tank(left_power, right_power); //sarah
        }

        void Robot::update_pneumatics() {
            if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
            {
                pneu.toggle_mogo();
            }
        }

        void Robot::update_flag() {
            if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) //change button for flag mech
            {
                flag.toggle_flag();
            }
        }
    
        //update function for whole robot
        void Robot::update(std::string info){
            update_drivetrain();
            update_intake();
            update_pneumatics();
        }