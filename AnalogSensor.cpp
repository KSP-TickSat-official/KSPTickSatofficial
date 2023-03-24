#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(int pin)
{
    analogPin=pin;
}

void AnalogSensor::Print_measure()
{
    SerialUSB.println(measure);
}

void AnalogSensor::Upgrade_measure()
{
    measure = analogRead(analogPin);
}

int AnalogSensor::Testing()
{
    int wynik=0;
    if(measure >=0 && measure <= 10000)wynik++;
    return (wynik==1) ? 1 : 0;
}
