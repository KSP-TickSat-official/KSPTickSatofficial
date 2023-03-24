#ifndef T_I2C_SENSOR //header file guard
#define T_I2C_SENSOR

// libraries for I2C communication
#include <Adafruit_Sensor.h>
#include <Wire.h>

class I2C_sensor
{

public:

    int I2C_adress; // sensor address
    int number_of_values; //number of records a sensor provides
    double* values; // sensor's records stored in an array

    void Initialize(int adress, int num); //initialize sensor

    virtual int Connect(); //I2C connection protocol
    virtual void Print_values(); //Prints sensor's records on the screen
    virtual int Sensor_configuration(); // speaks for itself :)
    virtual int Sensor_testing(); //Basic test of the sensor // done in the pre-shooting phase
    virtual void Upgrade_values(); //upgrade values function
};


#endif
