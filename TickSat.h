

//Library of project KSP TickSat
//Author: Lukasz Kasprzak
//gmail: kaspisnio320@gmail.com

#ifndef T_TickSat
#define T_TickSat

// Sensor libraries

//I2C sensors
#include "I2C_sensor.h"
#include "BME280.h"
#include "MPU6050.h"
#include "LTR390.h"
#include "AnalogSensor.h"

//SD_card library
#include "SD_card.h"

//GPS_module_library
#include "GPS_module.h"

//RTC library
#include <RTCZero.h>

//For Radio communication we use CanSatKit::Radio
#include <CanSatKit.h>

using namespace std;

#define NUMBER_OF_I2C_SENSORS 4
#define NUMBER_OF_ANALOG_SENSORS 1
#define NUMBER_OF_UART_SENSORS 1



// an abstract class using polymorphism technique

class Geiger_counter
{
    public:
    int strikes; //number of voltage strikes counted
    int Time_elapsed; //time elapsed since last update
};

class T_TickSat_satelite
{
    public:
    //Ticksat constructor
    T_TickSat_satelite();

    //satelite's sensors

    //I2C_sensors
    BME280 bme;
    MPU6050 mpu;
    LTR390 ltr;
    //ENS160 ens;
    //HMC5883 mag;

    //Analog_sensors

    AnalogSensor MiCS_gas(A2);
    AnalogSensor MQ135(A1);

    //sensors' configuration
    I2C_sensor* sensor_table[NUMBER_OF_I2C_SENSORS]{&bme,&mpu,&ltr};

    //SD
    SD_card mySD;

    //GPS
    GPS_module gps;

    //Real Time Clock
    RTCZero rtc;

    //Radio Frame
    Frame frame;

    // preshooting operations
    int TickSat_configuration();
    int TickSat_test();
    int Sensors_configuration();

    //mission operations
    int Upgrade_sensor_data();
    int Print_sensor_data();
    int Save_to_SD();
    int Send_to_ground_station();

    //after-landing operations
    int Standby_mode();
    int GPS_signaling();

    //private:
    // an enum class will be used to declare the satelite's current mode
    enum class status{ Prepare_for_mission=1,Prepare_for_shooting, Ascending, Drop ,Descending, Stand_by, Mission_success };
    status current_status;

};

#endif // T_TickSat
