#pragma once
#include "api.h"
#include "intake.hpp"

    Intake::Intake(int8_t motor1, int8_t motor2) :
    intakeMotors {{motor1, motor2}}
    {};

    
    //getters and setters
    void Intake::toggle_intake()
    {
        if (state)
        {
            intakeMotors.move_velocity(OFF);
            state = false;
        }
        else
        {
            intakeMotors.move_velocity(current_velocity);
            state = true;
        }
    }
    bool Intake::get_state_intake()
    {
        return state;
    }

    void Intake::set_direction(bool direction) //true is positive, false is negative
    {
        current_direction = direction;
    }
    bool Intake::get_direction()
    {
        return current_direction;
    }
    void Intake::toggle_direction()
    {
        if (current_direction)
        {
            
            current_direction = false;
            current_velocity = NEGATIVE_DIRECTION;
        }
        else
        {
            current_direction = true;
            current_velocity = POSITIVE_DIRECTION;
        }
    }

    int Intake::get_velocity()
    {
        return current_velocity;
    }