/***************************************************************
 * Name:      Regulator.h
 * Purpose:   Defines Regulator Class
 * Author:     ()
 * Created:   2019-07-24
 * Copyright:  ()
 * License:
 **************************************************************/

class RegulatorPid
{
    public:

    float deviation, p, i, d, derivative;
    float k_p, k_i, k_d;
    float regulator = 0;
    float previous_position = 0;
    float integral = 0;

    void calculate(float, float);
    float sendPID(float, char);
};

