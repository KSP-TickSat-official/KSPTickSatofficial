
#include "SD_card.h"


void SD_card::SD_card_configuration()
{

    //SerialUSB.println(" TickSat initialization. ");

    SerialUSB.println("Initializing SD card ...");
    while(!SD.begin(11))
        {
            SerialUSB.println("Failed to initizalize SD card.");
            SerialUSB.println("Put SD card into CanSat!");
            delay(100);
        }
    delay(1500);
    SerialUSB.println("SD card Initialized!");
}

void SD_card::Open_Records()
{
    Records = SD.open("Records.txt", FILE_WRITE);
}

void SD_card::Close_Records()
{
    Records.close();
}

void SD_card::Write(char* znaki)
{
    this->Open_Records();
    Records.print(znaki);
    this->Close_Records();
}

void SD_card::Write(double liczba)
{
    this->Open_Records();
    Records.print(liczba);
    this->Close_Records();
}

void SD_card::Read()
{
    this->Open_Records();
    if(Records)
    {
        while(Records.available())
        {
        SerialUSB.write(Records.read());
        }
    }
    this->Close_Records();
}
