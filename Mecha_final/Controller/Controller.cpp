#include "Controller.h"


PIDController::PIDController(float kp, float ki, float kd, float max_windup,
                             float start_time, float umin, float umax)
{
//    The PID controller can be initalized with a specific kp value
//    ki value, and kd value
    this->kp=kp;
    this->ki=ki;
    this->kd=kd;

    this->max_windup=max_windup;

    this->umin=umin;
    this->umax=umax;

    //Store relevant data
    this->last_timestamp_ = 0.0;
    this->set_point_ = 0.0;
    this->start_time_ = start_time;
    this->error_sum_ = 0.0;
    this->last_error_ = 0.0;
}



float PIDController::update(float measured_value, float timestamp)
{
    float delta_time = timestamp - last_timestamp_;
    last_timestamp_=timestamp;
    if(delta_time < 0.0001) return 0.0;
    
    float error=set_point_-measured_value;    
    
    error_sum_ += error*delta_time;
    float delta_error=error-last_error_;

    if(delta_error>10.0) {
        delta_error=10.0;
    }   
    last_error_=error;

    if(error_sum_>max_windup) {
        error_sum_=max_windup;
    } else if(error_sum_<-1.0*max_windup) {
        error_sum_=max_windup*-1.0;
    }
    
    //TODO: Complete PID Controller
    float p=kp*error;
    float i=ki*error_sum_;
    float d=kd*delta_error/delta_time;
    float u=p+i+d;

    return u;
}

void PIDController::setTarget(float target)
{
    this->set_point_=target;
}

void PIDController::setKp(float kp)
{
    this->kp=kp;
}

void PIDController::setKi(float ki)
{
    this->ki=ki;
}

void PIDController::setKd(float kd)
{
    this->kd=kd;
}

void PIDController::setMaxWindup(float max_windup)
{
    this->max_windup=max_windup;
}

float PIDController::getLastTimeStamp()
{
    return this->last_timestamp_;
}
