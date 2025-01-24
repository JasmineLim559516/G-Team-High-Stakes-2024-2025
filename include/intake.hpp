#pragma once
#include "api.h"

class Intake {
    private:
        //intake constructor
        pros::Motor intakeMotor;
        pros::Motor intakeMotor2;

        bool current_direction = true; //positive direction
        
    public:
        
        //constructor
        Intake (int port1, int port2);


        //getters and setters
        void set_voltage(int32_t voltage); //motor moves at this voltage
        int32_t get_avg_velocity();

        void set_direction(bool direction); //true is positive, false is negative
        bool get_direction();
        void switch_direction();
};