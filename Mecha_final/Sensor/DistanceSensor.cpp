#include "DistanceSensor.h"

#define MAX_DISTANCE (75)

DistanceSensor::DistanceSensor(PinName a): m_analogIn(a)
{
    m_distance = MAX_DISTANCE;
}

float DistanceSensor::getDistance_cm()
{
    m_distance = 26.663 * pow((m_analogIn * 3.3), -1.25);
    
    return m_distance;
}