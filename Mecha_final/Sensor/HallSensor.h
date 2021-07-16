#ifndef MBED_HallSensor_H
#define MBED_HallSensor_H

#include "mbed.h"

#define PI 3.141592


class HallSensor
{
public:
    HallSensor(PinName a);
    
    int getPinState ();
    float getSpeed_rps();

protected:
    void risingCallback();
    
    InterruptIn m_hallSensor;
    Timer m_timer_sec;
    float m_period_sec;
};

#endif