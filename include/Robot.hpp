#pragma once
#include "api.h"
#include "intake.hpp"
#include "drivetrain.hpp"
#include "pneumatics.hpp"

class Robot {
    private:
        pros::Controller m_controller {pros::E_CONTROLLER_MASTER}; 

        //robot constructor
        // Robot(Drivetrain drive, Intake intake);
        

        //robot components
        Drivetrain dt;
        Pneumatics pneu;
        Intake intake;

        //update robot components
        void update_intake();
        void update_drivetrain();
        void update_pneumatics();

    public:
        Robot(int8_t left1, int8_t left2, int8_t left3, int8_t right1, int8_t right2, int8_t right3, uint8_t port, int8_t intake1, int8_t intake2);

        //update function for whole robot
        void update(std::string info);

        void auton();
};