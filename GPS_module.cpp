#include "GPS_module.h"

int GPS_module::Connect()
{
    //possibly add a loop for a sure thing
    while(*gpsStream)
    {
        return(gps.encode(*gpsStream++));
    }
}

int GPS_module::getDate()
{
    if (gps.date.isValid())
  {
    year=gps.date.year();
    month=gps.date.month();
    day=gps.date.day();
    return 1;
  }
  return 0;
}

int GPS_module::getTime()
{
   if (gps.time.isValid())
   {
    hour=gps.time.hour();
    minute=gps.time.minute();
    second=gps.time.second();
    centisecond=gps.time.centisecond();
    return 1;
   }
   return 0;
}

int GPS_module::getPosition()
{
    if (gps.location.isValid())
  {
    latitude=gps.location.lat();
    longtitude=gps.location.lng();
  }
}

int GPS_module::Update_all()
{
    this->Connect();
    this->getDate();
    this->getTime();
    this->getPosition();
}

int GPS_module::Testing(int n)
{
    SerialUSB.println("Testing GPS ...");
    if(!(this->Connect()))
    {
        SerialUSB.println("Failed to find a GPS Module");
    }

    bool success=false;

    for(int i=0;i<n;i++)
    {

    bool success=false;

    while(!success)
    {
        this->Connect();

        if (!(this->getDate()))
        {
            SerialUSB.println("CANNOT find proper DATE values!");
            success==false;

        }

        if(this->year==2023 && this->month==3)
        {
            success=true;
        }

        if (!(this->getTime()))
        {
            SerialUSB.println("CANNOT find proper TIME values!");
            success=false;
        }

        if (!(this->getPosition()))
        {
            SerialUSB.println("CANNOT find proper POSITION values!");
            success=false;
        }

    }
    delay(1000);
    }
    if(success)
    {
        SerialUSB.println("GPS testing SUCCESS");
        return 1;
    }
    SerialUSB.println("GPS testing FAILED");
    return 0;

}

int GPS_module::Print_all()
{
    this->Update_all();

    SerialUSB.print(F("Location: "));
  if (gps.location.isValid())
  {

    SerialUSB.print(gps.location.lat(), 6);
    SerialUSB.print(F(","));
    SerialUSB.print(gps.location.lng(), 6);
  }
  else
  {
    SerialUSB.print(F("INVALID"));
  }

  SerialUSB.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    SerialUSB.print(gps.date.month());
    SerialUSB.print(F("/"));
    SerialUSB.print(gps.date.day());
    SerialUSB.print(F("/"));
    SerialUSB.print(gps.date.year());
  }
  else
  {
    SerialUSB.print(F("INVALID"));
  }

  SerialUSB.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) SerialUSB.print(F("0"));
    SerialUSB.print(gps.time.hour());
    SerialUSB.print(F(":"));
    if (gps.time.minute() < 10) SerialUSB.print(F("0"));
    SerialUSB.print(gps.time.minute());
    SerialUSB.print(F(":"));
    if (gps.time.second() < 10) SerialUSB.print(F("0"));
    SerialUSB.print(gps.time.second());
    SerialUSB.print(F("."));
    if (gps.time.centisecond() < 10) SerialUSB.print(F("0"));
    SerialUSB.print(gps.time.centisecond());
  }
  else
  {
    SerialUSB.print(F("INVALID"));
  }

  SerialUSB.println();
}
