#include "TickSat.h"

using namespace std;

int T_TickSat_satelite::TickSat_configuration()
{
    for(int i=0; i<NUMBER_OF_I2C_SENSORS; i++)
    {
        sensor_table[i]->Sensor_configuration();
    }

    mySD.SD_card_configuration();
    gps.Connect();

    {
    rtc.setHours(gps.hour);
    rtc.setMinutes(gps.minute);
    rtc.setSeconds(gps.second);


    rtc.setDay(gps.day);
    rtc.setMonth(gps.month);
    rtc.setYear(gps.year);
    }

    Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_9,
            CodingRate_4_8);
}

int T_TickSat_satelite::TickSat_test()
{
    for(int i=0; i<NUMBER_OF_I2C_SENSORS; i++)
    {
        sensor_table[i]->Sensor_testing();
    }
    //MiCS_gas.Testing();
    gps.Testing();
}

int T_TickSat_satelite::Upgrade_sensor_data()
{
for(int i=0; i<NUMBER_OF_I2C_SENSORS; i++)
    {
        sensor_table[i]->Upgrade_values();
    }

    //MiCS_gas.Upgrade_measure();

    gps.Update_all();
}

int T_TickSat_satelite::Print_sensor_data()
{
for(int i=0; i<NUMBER_OF_I2C_SENSORS; i++)
    {
        sensor_table[i]->Print_values();
    }
    MiCS_gas.Print_measure();

    gps.Print_all();
}

int T_TickSat_satelite::Save_to_SD()
{
    mySD.Write(rtc.hour);
    mySD.Write(rtc.minute);
    mySD.Write(rtc.second);

    for(int i=0; i<NUMBER_OF_I2C_SENSORS; i++)
    {
        for(int i=0;i<sensor_table[i]->number_of_values;i++)
        mySD.Write(sensor_table[i]->values[i]);
    }
    mySD.Write(MiCS_gas.measure);
    mySD.Write (MQ135.measure);
}

int T_TickSat_satelite::Send_to_ground_station()
{
    frame.print(rtc.hour);
    frame.print(rtc.minute);
    frame.print(rtc.second);

    for(int i=0; i<NUMBER_OF_I2C_SENSORS; i++)
    {
        for(int i=0;i<sensor_table[i]->number_of_values;i++)
        {
            frame.print(sensor_table[i]->values[i]);
            radio.transmit(frame);
            frame.clear();
        }
    }
    frame.print(MiCS_gas.measure);
    frame.print (MQ135.measure);

    frame.clear();
}

int T_TickSat_satelite::GPS_signaling()
{
    //upgrade time and position
    gps.Connect();
    gps.getTime();
    gps.getDate();
    gps.getPosition();

    //Save GPS_info to SD
    mySD.Write(hour);
    mySD.Write(minute);
    mySD.Write(second);
    mySD.Write(gps.latitude);
    mySD.Write(gps.longtitude);
    }

int T_TickSat_satelite::Standby_mode()
{
    this->GPS_signaling();

    frame.print(gps.latitude);
    frame.print(gps.longtitude);

    //try to send GPS_data to ground
    radio.transmit(frame);

    frame.clear();

    //do it once a second
    delay(1000);
}

