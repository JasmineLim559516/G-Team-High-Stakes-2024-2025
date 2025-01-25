#pragma once
#include "api.h"

class Pneumatics {
    private:
        //initializes pneumatics motor
        pros::ADIDigitalOut mogo;

        bool state = false;

    public:
        //pneumatics constructor
        Pneumatics (uint8_t port);

        //extends or deextends pneumatics depending on state
        void toggle_mogo();

        //returns if pneumatic extended or not
        bool get_state_mogo();   
};