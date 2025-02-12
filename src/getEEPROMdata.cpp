#include <header.h>

void getEEPROMdata(){   
    int i2 = 0;
    for (int i = aSSid; i < (int)sizeof(SSid) + aSSid; i++) {SSid[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = apass; i < (int)sizeof(pass) + apass; i++) {pass[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = aip; i < 4 + aip; i++) {ip[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = agateway; i < 4 + agateway; i++) {gateway[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = asubnet; i < 4 + asubnet; i++) {subnet[i2] = EEPROM.read(i); i2++;}

  
}