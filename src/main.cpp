#include "header.h"

AccessPoint accessPoint;
MainPade mainPage;
timer restartAPtime(1000*60*15, 3);

timer Timer1(1000, 0);

void setup(){
    Serial.begin(9600);
    Serial.printf("\n\n\n\n\n################################## START ##################################\n\n");

    EEPROM.begin(512);
    pinMode(2, 1);

    getEEPROMdata();

    Serial.printf("\nSSid :\t%s\nPassword :\t%s", SSid, pass);
    Serial.printf("\n%i.%i.%i.%i", ip[0], ip[1], ip[2], ip[3]);
    Serial.printf("\n%i.%i.%i.%i", gateway[0], gateway[1], gateway[2], gateway[3]);
    Serial.printf("\n%i.%i.%i.%i", subnet[0], subnet[1], subnet[2], subnet[3]);

    mainPage.start(100);
    Timer1.start();
}

void loop(){
    mainPage.tick();
    // delay(10000);
    
    // accessPoint.tick();
    // if (restartAPtime.status()){
    //     accessPoint.stop();
    //     accessPoint.startCP();
    //     Serial.printf("\nAP has restarted");
    // }
}
