#pragma once
#include "api.h"

class Intake {
    private:
        //intake constructor
        pros::MotorGroup intakeMotors;

        bool current_direction = true; //positive direction
        bool state = false; //not moving
        int current_velocity;
        int POSITIVE_DIRECTION = 600;
        int NEGATIVE_DIRECTION = -600;
        int OFF = 0;
        
    public:
        
        //constructor
        Intake (int8_t port1, int8_t port2);


        //getters and setters
        void toggle_intake();
        bool get_state_intake();

        void set_direction(bool direction); //true is positive, false is negative
        bool get_direction();
        void toggle_direction();

        int get_velocity();
};