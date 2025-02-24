#include "api.h"

namespace ports {

    constexpr int8_t LEFT_BACK_DT = -8;  //17 for mogo front.   8 for intake front(sarah)
    constexpr int8_t LEFT_FRONT_BOTTOM_DT = -16;  //13 for mogo front.   16 for intake front(sarah)
    constexpr int8_t LEFT_FRONT_TOP_DT = -20;  //19 for mogo front.  20 for intake front(sarah)


    constexpr int8_t RIGHT_BACK_DT = 17;   //8 for mogo front.  17 for intake front(sarah)
    constexpr int8_t RIGHT_FRONT_BOTTOM_DT = 13;  //16 for mogo front. 13 for intake front(sarah)
    constexpr int8_t RIGHT_FRONT_TOP_DT = 19;   //20 for mogo front.  19 for intake front(sarah)

    constexpr int8_t INTAKE_MOTOR_1 = -2; 
    constexpr int8_t INTAKE_MOTOR_2 = 15;
    
    constexpr uint8_t PNEUMATIC1 = 'H'; 
    constexpr uint8_t FLAG1 = 'G'; 

};