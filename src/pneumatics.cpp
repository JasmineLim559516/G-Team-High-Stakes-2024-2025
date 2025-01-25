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

        bool Pneumatics::get_state_mogo()
        {
            return state;
        }