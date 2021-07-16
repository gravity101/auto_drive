#include "LaneSensor.h"

LaneSensor::LaneSensor(PinName lll,PinName ll,PinName l,PinName m,PinName r,PinName rr,PinName rrr)
    : sensorsIn_(lll,ll,l,m,r,rr,rrr)
{
    error_ =0.0;
    prevError_=0.0;
    
    //sensorsIn_.mode(PullNode);
}
float LaneSensor::getError()
{
    
        int sensorIn=sensorsIn_ & sensorsIn_.mask();
    
    
        if( (sensorIn&0x1) == 0x0 ) 
        {
            error_ = -40;
        }
        if( (sensorIn&0x2) == 0x0 ) 
        {
            error_ = -25;
        }
        if( (sensorIn&0x4) == 0x0 ) 
        {
            error_ = -5;
        }
        if( (sensorIn&0x8) == 0x0 ) 
        {
            error_ = 0;
        }
        if( (sensorIn&0x10) == 0x0 )
        {
            error_ = 5;
        }
        if( (sensorIn&0x20) == 0x0 )
        {
            error_ = 25;
        }
        if((sensorIn&0x40) == 0x0 )
        {
            error_  = 40;
        }
    
    
    
   
    
    
    return error_;
}

int LaneSensor::getData()
{
    int sensorIn=sensorsIn_ & sensorsIn_.mask();
    
    /*
    if (  )
    {
        return -30;
    }
    else if ( ) 
    {
        return -10;
    }
    else if ( (sensorIn&0x1)==0x1 && (sensorIn&0x2) ==0x1 && (sensorIn&0x4) == 0x0 && (sensorIn&0x8) == 0x1 && (sensorIn&0x10) == 0x1 && (sensorIn&0x20) == 0x1 && (sensorIn&0x40) == 0x1) 
    {
        return -5;
    }
    else if ( (sensorIn&0x1)==0x1 && (sensorIn&0x2) ==0x1 && (sensorIn&0x4) == 0x1 && (sensorIn&0x8) == 0x0 && (sensorIn&0x10) == 0x1 && (sensorIn&0x20) == 0x1 && (sensorIn&0x40) == 0x1) 
    {
        return 0;
    }
    else if ( (sensorIn&0x1)==0x1 && (sensorIn&0x2) ==0x1 && (sensorIn&0x4) == 0x1 && (sensorIn&0x8) == 0x1 && (sensorIn&0x10) == 0x0 && (sensorIn&0x20) == 0x1 && (sensorIn&0x40) == 0x1) 
    {
        return 5;
    }
    else if ( (sensorIn&0x1)==0x1 && (sensorIn&0x2) ==0x1 && (sensorIn&0x4) == 0x1 && (sensorIn&0x8) == 0x1 && (sensorIn&0x10) == 0x1 && (sensorIn&0x20) == 0x0 && (sensorIn&0x40) == 0x1) 
    {
        return 10;
    }
    else if( (sensorIn&0x1)==0x1 && (sensorIn&0x2) ==0x1 && (sensorIn&0x4) == 0x1 && (sensorIn&0x8) == 0x1 && (sensorIn&0x10) == 0x1 && (sensorIn&0x20) == 0x1 && (sensorIn&0x40) == 0x0) 
    {
        return 30;
    }
    */
    
    return sensorsIn_ & sensorsIn_.mask();
}