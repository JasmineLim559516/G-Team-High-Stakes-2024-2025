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

        //update robot components
        void update_intake();
        void update_drivetrain();
        void update_pneumatics();

    public:
        Robot(int8_t left1, int8_t left2, int8_t left3, int8_t right1, int8_t right2, int8_t right3, int8_t port);

        //update function for whole robot
        void update(std::string info);
};