#include "MPU6050.h"

using namespace std;

MPU6050::MPU6050(int adress,int num)
{
  Initialize(adress,num);
}

int MPU6050::Connect()
{
    int status = mpu.begin();
    return (status) ? 1 : 0;
}

void MPU6050::Print_values()
{
  SerialUSB.print("Acceleration X: ");
  SerialUSB.print(a_x);
  SerialUSB.print(", Y: ");
  SerialUSB.print(a_y);
  SerialUSB.print(", Z: ");
  SerialUSB.print(a_z);
  SerialUSB.println(" m/s^2");

  SerialUSB.print("Vector sum of accelerations :");
  SerialUSB.print(sqrt(a_x*a_x   +   a_y*a_y  +   a_z*a_z));
  SerialUSB.println("");

  SerialUSB.print("Rotation X: ");
  SerialUSB.print(r_x);
  SerialUSB.print(", Y: ");
  SerialUSB.print(r_y);
  SerialUSB.print(", Z: ");
  SerialUSB.print(r_z);
  SerialUSB.println(" rad/s");


  SerialUSB.println();
}

void MPU6050::Upgrade_values()
    {
        this->Connect();

        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        a_x = values[0]= a.acceleration.x;
        a_y = values[1]= a.acceleration.y;
        a_z = values[2]= a.acceleration.z;

        a_sum = sqrt(a_x*a_x   +   a_y*a_y  +   a_z*a_z);

        r_x = values[3]= g.gyro.x;
        r_y = values[4]= g.gyro.y;
        r_z = values[5]= g.gyro.z;
    }

int MPU6050::Sensor_configuration()
{
    this->Connect();
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G); //setting accelerometer's precision;  options 2, 4, 8, 16.
    mpu.setGyroRange(MPU6050_RANGE_500_DEG); // setting gyroscope's precision;  options 250, 500, 1000, 2000.
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // setting Filter Bandwidth;  options 5, 10, 21, 44, 94, 184, 260.
}

int MPU6050::Sensor_testing()
{
    this->Connect();
    int wynik=0;
    if(sqrt(a_x*a_y*a_z) < 10.0 && sqrt(a_x*a_y*a_z) > 9.0)wynik++;
    if(r_x < 180 & r_y < 180 && r_z <180)wynik++;

    return (wynik == 2) ? 1 : 0;
}
