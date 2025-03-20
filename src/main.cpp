#define TRYCONN 150

#include "header.h"

AccessPoint accessPoint;
MainPage mainPage;
timer restartAPtime(1000*60*15, 3);
timer checkWiFi(1000*10, 3);

byte _WiFimode = 0;
bool APflag = true;

void setup(){
    Serial.begin(9600);
    Serial.printf("\n\n\n\n\n################################## START ##################################\n\n");

    EEPROM.begin(512);

    getEEPROMdata();

    Serial.printf("\nSSid :\t%s\nPassword :\t%s", SSid, pass);
    Serial.printf("\n%i.%i.%i.%i", ip[0], ip[1], ip[2], ip[3]);
    Serial.printf("\n%i.%i.%i.%i", gateway[0], gateway[1], gateway[2], gateway[3]);
    Serial.printf("\n%i.%i.%i.%i\n", subnet[0], subnet[1], subnet[2], subnet[3]);

    accessPoint.stop();
    mainPage.stop();

    fetchCurrentTime();
}

void loop(){
    HandleConnect();
}

void HandleConnect(){
    mainPage.tick();
    accessPoint.tick();

    if (_WiFimode == 0) {
        _WiFimode = mainPage.start(TRYCONN);
        APflag = false;
    }

    if (_WiFimode == 1) {
        _WiFimode = mainPage.start(TRYCONN);
    }

    if (_WiFimode == 3 && !APflag) {
        mainPage.reset();
        accessPoint.startCP();
        restartAPtime.start();
        APflag = true;
    }

    if (accessPoint.gotStatus() || (restartAPtime.status() && _WiFimode == 3) || (checkWiFi.status() && _WiFimode == 4 && !mainPage.status())) {
        accessPoint.stop();
        mainPage.reset();
        _WiFimode = 0;
    }
}
