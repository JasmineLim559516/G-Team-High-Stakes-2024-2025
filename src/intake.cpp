#pragma once
#include "api.h"
#include "intake.hpp"

    Intake::Intake(int motor1, int motor2) :
    intakeMotor {motor1},
    intakeMotor2 {motor2}
    {}; 

    
    //getters and setters
    void set_voltage(int32_t voltage) //motor moves at this voltage
    {

    }
    
    int32_t get_avg_velocity();

    void set_direction(bool direction); //true is positive, false is negative
    bool get_direction();
    void switch_direction();
