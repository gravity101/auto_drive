#include "mbed.h"
#include "LaneSensor.h"
#include "Servo.h"
#include "HallSensor.h"
#include "DistanceSensor.h"
#include "Motor.h"
#include "Controller.h"
#include "Plotting.h"

Serial pc(USBTX,USBRX);

Plotting plot;
HallSensor hall(p29);
Motor motor (p23, p24, p25, p26);
PIDController controller(0.1, 0.35, 0.0, 100.0, 0.0, -1.0, 100.0 );
DistanceSensor pir (p20);
//To plot with usb, set as below.
 // Tx, Rx Pin
Servo servo(p10);
//Set each gpio to see the output of the hall sensor as a led
LaneSensor laneSensor(p11,p12,p13,p14,p15,p16,p17);

bool middle = false;
bool left = false;
bool right = false;
bool left2 = false;
bool right2 = false;
bool no = false;

//Interrupt is generated every 1ms and count is increased by 1
unsigned int uiFlag_1ms = 0;
unsigned int uiFlag_50ms = 0;

void counter_1ms ()
{
    uiFlag_1ms++;
    uiFlag_50ms++;
}



int main()
{  
    wait(1);
    float degree= 0;
    float percent = 20;
    ////Set the 1ms thicker.
    Ticker ticker_1ms;
    ticker_1ms.attach(&counter_1ms, 0.001);
    
    Timer time;
    time.start();
   
    
    while(1) 
    { 

        if(uiFlag_1ms >= 1)
        {
            uiFlag_1ms = 0;
            
                    
            
            
           
            percent =20;
            
            
            
            if (pir.getDistance_cm() <= 60)
            {
               servo.update(degree);
               motor.setSpeed_percent(0,BACKWARD);
            }
            else
            {
                
                    
                
               
               
    if (laneSensor.getData() == 126)
    {
        percent = 15;
        degree = 55;
        left2 = false;
        
    } 
    else if (laneSensor.getData() == 125)
    {
        percent = 15;
            if(left2)
            {
                degree = 40;
            }
            else
            {
                degree = 35;
            }
            left = false;
            
    }
    else if (laneSensor.getData() == 123)
    {
            
            if(left)
            {
                degree = 25;
            }
            else
            {
                degree = 15;
            }
            
            left2 = true;
    } 
    else if ( laneSensor.getData() == 119 )
    {
            
                    degree = 0;    
            
            
            left = true;
            right = true;
            
    } 
    else if ( laneSensor.getData() == 111 )
    {
        
        if(right)
            {
                degree = -25;
            }
            else
            {
                degree = -15;
            }
            
            right2 = true;
    } 
    else if ( laneSensor.getData() == 95 )
    {
             percent = 15;
             if(right2)
            {
                degree = -40;
            }
            else
            {
                degree = -35;
            }
            right = false;
            
    } 
    else if ( laneSensor.getData() == 63 )
    {
            percent = 15;
            degree = -55;
            right2 = false;
    }
    else if ( laneSensor.getData() == 127 )
    {
            degree = servo.getDegree();
            percent=15;
    }
    else
    {
        percent=15;
    }

               
                servo.update(degree);
             
                motor.setSpeed_percent(percent,BACKWARD);
            }
           
            
        }
        // Every 50 ms,
        if(uiFlag_50ms >= 1000) {
            pc.printf("Degree: %d\n", laneSensor.getData());
            uiFlag_50ms=0;
            
        }
    }
}