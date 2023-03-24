#include "BME280.h"

using namespace std;

BME280::BME280(int adress,int num)
{
    Initialize(adress,num);
}

int BME280::Connect()
{
    int status = bme.begin();
    return (status) ? 1 : 0;
}

void BME280::Print_values()
{
    SerialUSB.print("Temperature = ");
    SerialUSB.print(bme.readTemperature());
    SerialUSB.println(" °C");

    SerialUSB.print("Pressure = ");

    SerialUSB.print(bme.readPressure() / 100.0F);
    SerialUSB.println(" hPa");

    SerialUSB.print("Approx. Altitude = ");
    SerialUSB.print(bme.readAltitude(1013.25));
    SerialUSB.println(" m");

    SerialUSB.print("Humidity = ");
    SerialUSB.print(bme.readHumidity());
    SerialUSB.println(" %");

    SerialUSB.println();
}

void BME280::Upgrade_values()
    {
        this->Connect();

        temperature = values[0]= bme.readTemperature();
        pressure = values[1]= bme.readPressure();
        humidity = values[2]= bme.readHumidity();
        altitude = values[3]= bme.readAltitude(1013.25);
    }

int BME280::Sensor_configuration()
{
// no need to configure BME_280
}
int BME280::Sensor_testing()
{
    this->Upgrade_values();

    int wynik=0;
    if(temperature > -10.0 && temperature < 30.0 )wynik++;
    if(pressure > 900 && pressure < 1100 )wynik++;
    if(humidity >= 0.0 && humidity <= 100.0)wynik++;
    if(altitude >=0 && altitude <=500.0)wynik++;

    return (wynik == 4) ? 1 : 0;
}
