#pragma once
#include "api.h"

class FlagMech {
    private:
        //initializes flagMech motor
        pros::ADIDigitalOut flag;

        bool state = false;

    public:
        //pneumatics constructor
        FlagMech (uint8_t port);

        //extends or deextends pneumatics depending on state
        void toggle_flag();

        //returns if pneumatic extended or not
        bool get_state_flag();  

        void set_flag(bool a_state); 
};