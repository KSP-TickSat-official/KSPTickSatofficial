#ifndef T_AnalogSensor
#define T_AnalogSensor

#include <Adafruit_Sensor.h>

class AnalogSensor
{
public:

    int analogPin;
    double measure;

    AnalogSensor(int=A0);
    void Print_measure();
    int Testing();
    void Upgrade_measure();
};

#endif T_AnalogSensor
