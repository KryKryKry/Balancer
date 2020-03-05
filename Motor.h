/***************************************************************
 * Name:      Motor.h
 * Purpose:   Defines Motor Class
 * Author:     ()
 * Created:   2019-09-14
 * Copyright:  ()
 * License:
 **************************************************************/


class Motor
{
    public:

    const float min_PWM = 0.25;
    float total_PWM;
    float command_PWM;
    bool negative_axis_X;
    bool negative_axis_Y;
    float regulator_X;

    float addingPwm(float, float);

};
