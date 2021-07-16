#ifndef MBED_CONTROLLER_H
#define MBED_CONTROLLER_H

#include "mbed.h"


class PIDController
{
private:
    float kp;
    float ki;
    float kd;
    float max_windup;
    float alpha;
    float umin;
    float umax;

    float last_timestamp_ ;
    float set_point_;
    float start_time_ ;
    float error_sum_;
    float last_error_;
    float last_d_;

public:
    PIDController(float kp, float ki, float kd, float max_windup,
                             float start_time,float umin, float umax);
    //void reset();
    float update(float measured_value, float timestamp);
    void setTarget(float target);
    void setKp(float kp);
    void setKi(float ki);
    void setKd(float kd);
    void setMaxWindup(float max_windup);
    float getLastTimeStamp();
};

#endif
