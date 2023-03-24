#include "LTR390.h"

using namespace std;

LTR390::LTR390(int adress,int num)
{
  Initialize(adress,num);
  ltr=Adafruit_LTR390(I2C_adress);
}

int LTR390::Connect()
{
    int status = ltr.begin();
    return (status) ? 1 : 0;
}

void LTR390::Print_values()
{
    SerialUSB.print("UV data: ");
    SerialUSB.print(UV_level);

    SerialUSB.println();
}

void LTR390::Upgrade_values()
    {
        SerialUSB.println("IM HERE");
        ltr.begin();
        delay(1);
        this->Sensor_configuration();
        //while(!this->Connect());
        //if (ltr.newDataAvailable())
        for(int i=0;i<10;i++)
        {
        {
        delay(100);
        SerialUSB.println("UV data: ");
        SerialUSB.println(ltr.readUVS()); // check if it works!
        }
        delay(100);
        }
        UV_level=(ltr.readUVS());
        values[0]=UV_level;
    }

int LTR390::Sensor_configuration()
{
    this->Connect();
    ltr.setMode(LTR390_MODE_UVS);// UV light mode
    ltr.setGain(LTR390_GAIN_3);// set gain of the UV sensor
    ltr.setResolution(LTR390_RESOLUTION_16BIT);// set resolution; other options 13,16,17,18,19,20
    ltr.setThresholds(100, 1000);//set Tresholds
    ltr.configInterrupt(true, LTR390_MODE_UVS);// setting trigger to UV light
}

int LTR390::Sensor_testing()
{
    this->Connect();
    int wynik=0;
    if(UV_level >=0 && UV_level <=200)wynik++;
    return (wynik == 1) ? 1 : 0;
}
