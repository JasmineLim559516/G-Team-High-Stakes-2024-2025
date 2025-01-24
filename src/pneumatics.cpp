#pragma once
#include "api.h"
#include "pneumatics.hpp"

        Pneumatics::Pneumatics(int port) :
            mogo {port}
        {};


        void Pneumatics::toggle_mogo()
        {
            if (state)
            {
                mogo.set_value(false);
            }
            else
            {
                mogo.set_value(true);
            }
        }

        bool Pneumatics::get_state_mogo()
        {
            return state;
        }