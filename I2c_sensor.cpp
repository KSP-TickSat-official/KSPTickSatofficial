#include "I2C_sensor.h"

void I2C_sensor::Initialize(int adress, int num)
{
    I2C_adress=adress;
    number_of_values = num;
    values = new double[number_of_values];
}
