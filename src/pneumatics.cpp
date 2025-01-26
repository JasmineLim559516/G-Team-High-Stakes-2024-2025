#pragma once
#include "api.h"
#include "pneumatics.hpp"

        Pneumatics::Pneumatics(uint8_t port) :
            mogo {port}
        {};


        void Pneumatics::toggle_mogo()
        {
            if (state)
            {
                mogo.set_value(false);
                state = false;
            }
            else
            {
                mogo.set_value(true);
                state = true;
            }
        }

        void Pneumatics::set_mogo(bool a_state) //a_state false = off and vice versa
        {
            mogo.set_value(a_state);
            state = a_state;
        }



        bool Pneumatics::get_state_mogo()
        {
            return state;
        }