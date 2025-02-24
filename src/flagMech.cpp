#pragma once
#include "api.h"
#include "flagMech.hpp"

        FlagMech::FlagMech(uint8_t port) :
            flag {port}
        {};


        void FlagMech::toggle_flag()
        {
            if (state)
            {
                flag.set_value(false);
                state = false;
            }
            else
            {
                flag.set_value(true);
                state = true;
            }
        }

        void FlagMech::set_flag(bool a_state) //a_state false = off and vice versa
        {
            flag.set_value(a_state);
            state = a_state;
        }



        bool FlagMech::get_state_flag()
        {
            return state;
        }