#include <Arduino.h>
#include <EEPROM.h>

class CONF
{
private:
    /* data */
public:
    void EEPROM_init(int size); 
    void Save();

    String string = "SSid :  1234, pass :  44445";

void EEPROM_init(int size){
    EEPROM.begin(size);
}

void Save(){
int index = 0;
while (string[index]&&)
{
    /* code */
}

}
};

