#ifndef T_BME280
#define T_BME280

#include "I2C_sensor.h"
#include <Adafruit_BME280.h>

class BME280 : public I2C_sensor
{
    public:
    Adafruit_BME280 bme;

    //BME280 constructor
    BME280(int adress=0x76,int num=4);

    int Connect();
    void Print_values();
    int Sensor_configuration();
    int Sensor_testing();
    void Upgrade_values();

    //extra info - values measured;
    double temperature;
    double pressure;
    double humidity;
    double altitude;
};

#endif // T_BME280
