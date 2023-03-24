#ifndef T_LTR390
#define T_LTR390

#include "I2C_sensor.h"
#include <Adafruit_LTR390.h>

class LTR390 : public I2C_sensor
{
    public:
    Adafruit_LTR390 ltr;

    //BME280 constructor
    LTR390(int adress=0x53,int num=1);

    int Connect();
    void Print_values();
    int Sensor_configuration();
    int Sensor_testing();
    void Upgrade_values();

    //extra info - values measured;
    double UV_level;
};

#endif // T_LTR390
