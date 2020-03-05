/***************************************************************
 * Name:      BalancerMain.cpp
 * Purpose:
 * Author:     ()
 * Created:   2019-07-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "Regulator.h"



void RegulatorPid::calculate(float command_position, float actual_position) {

    deviation = command_position - actual_position;
    p = k_p * deviation;

    integral = integral + deviation;
    i = k_i * integral;

    derivative = actual_position - previous_position;
    d = k_d * derivative;

    regulator = p + i + d;
    previous_position = actual_position;

    if(regulator > 0) regulator = 0;
}

float RegulatorPid::sendPID(float value, char type) {
    if (type == 'P') k_p = value;
    if (type == 'I') k_i = value;
    if (type == 'D') k_d = value;
    return 0;
}

