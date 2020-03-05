/***************************************************************
 * Name:      Motor.cpp
 * Purpose:
 * Author:     ()
 * Created:   2019-09-14
 * Copyright:  ()
 * License:
 **************************************************************/

#include "Motor.h"


float Motor::addingPwm(float regulator_X, float regulator_Y) {
    total_PWM = min_PWM;
    if((regulator_X < 0) && negative_axis_X == 1) total_PWM += regulator_X;
    if((regulator_X > 0) && negative_axis_X == 0) total_PWM += regulator_X;
    if((regulator_Y < 0) && negative_axis_Y == 1) total_PWM += regulator_Y;
    if((regulator_Y > 0) && negative_axis_Y == 0) total_PWM += regulator_Y;
    if(total_PWM > 100) total_PWM = 100;
    return total_PWM;
}



