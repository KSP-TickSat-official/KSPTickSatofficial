#ifndef T_MPU6050
#define T_MPU6050

#include "I2C_sensor.h"
#include <Adafruit_MPU6050.h>

class MPU6050 : public I2C_sensor
{
    public:
    Adafruit_MPU6050 mpu;


    //MPU6050 constructor
    MPU6050(int adress=0x68,int num=6);

    int Connect();
    void Print_values();
    int Sensor_configuration();
    int Sensor_testing();
    void Upgrade_values();

    //extra info - values measured;
    double a_x, a_y, a_z; // accelerations
    double a_sum;//vector sum of accelerations
    double r_x, r_y, r_z; // rotations
};


#endif // T_MPU6050
