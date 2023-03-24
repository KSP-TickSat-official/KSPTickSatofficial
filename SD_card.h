

#ifndef T_SD
#define T_SD

#include <SD.h>
#include <SPI.h>

class SD_card
{
    public:
    void SD_card_configuration();

    void Write(char*);
    void Write(double);

    void Read();

    private:
    File Records;

    void Open_Records();
    void Close_Records();
};

#endif // T_SD

