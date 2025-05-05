#include "header.h"

AccessPoint accessPoint;
MainPage mainPage;
handleLED HandleLED;
time1 _time;
DFRobot_AHT20 aht20;
iarduino_DHT sensor(D5);

timer restartAPtime(1000 * 60 * 15, 3);
timer checkWiFi(1000 * 10, 3);
timer updateTime(UPDATERATE, 3);
timer timeofget(10 * 60 * 1000, 3);
timer SEND(1000, 3);
timer printtime(1000, 3);
timer updateSensorTimer(5000, 3);
timer rt(1000*60*10, 3);

bool firstconnect = 1;

byte _WiFimode = 0;
bool APflag = true;

void updateSensor();
void show();
// void HandleConnect();


void setup()
{
    aht20.begin();

    Wire.begin(4, 5);
    Wire.setClock(50000);

    Serial.begin(9600);
    Serial.printf("\n\n\n\n\n################################## START ##################################\n\n");

    EEPROM.begin(1024);

    getEEPROMdata();

    Serial.printf("\nSSid :\t%s\nPassword :\t%s", SSid, pass);
    Serial.printf("\n%i.%i.%i.%i", ip[0], ip[1], ip[2], ip[3]);
    Serial.printf("\n%i.%i.%i.%i", gateway[0], gateway[1], gateway[2], gateway[3]);
    Serial.printf("\n%i.%i.%i.%i", subnet[0], subnet[1], subnet[2], subnet[3]);
    Serial.printf("\n%i.%i.%i.%i", dns[0], dns[1], dns[2], dns[3]);
    Serial.printf("\n%i.%i.%i.%i\n", dns2[0], dns2[1], dns2[2], dns2[3]);

    accessPoint.stop();
    mainPage.stop();

    HandleLED.begin();

    updateSensor();

    _time.begin();

    mainPage.start(0);
}

void loop()
{
    show();

    if (printtime.status())
        Serial.printf("\n%i:%i:%i\t\n", _time.curtime.Hour, _time.curtime.Minutes, _time.curtime.Seconds);

    // HandleConnect();

    if (updateTime.status())
        HandleLED.tick();

    if (updateSensorTimer.status())
        updateSensor();

    if (rt.status()) 
        mainPage.reset();

    mainPage.tick();
}

// void HandleConnect()
// {

//     mainPage.tick();
//     accessPoint.tick();

//     if (_WiFimode == 0)
//     {
//         _WiFimode = mainPage.start(TRYCONN);
//         APflag = false;
//     }

//     if (_WiFimode == 1)
//     {
//         _WiFimode = mainPage.start(TRYCONN);
//     }

//     if (_WiFimode == 3 && !APflag)
//     {
//         mainPage.reset();
//         accessPoint.startCP();
//         restartAPtime.start();
//         APflag = true;
//     }

//     if ((rt.status())||(accessPoint.gotStatus() || (restartAPtime.status() && _WiFimode == 3) || (checkWiFi.status() && _WiFimode == 4 && !mainPage.status())))
//     {
//         accessPoint.stop();
//         mainPage.reset();
//         _WiFimode = 0;
//     }
// }

void show()
{
    _time.tick();

    HandleLED.Leddata.Minutes = _time.curtime.Minutes;
    HandleLED.Leddata.Hour = _time.curtime.Hour;
    HandleLED.Leddata.Day_Month = _time.curtime.Day_Month;
    HandleLED.Leddata.Month = _time.curtime.Month;
}

void updateSensor()
{
    sensor.read();
    if(!aht20.startMeasurementReady(true)) return;
    Serial.printf("\nT:%i\tH:%i\n", (byte)aht20.getTemperature_C(), (byte)sensor.hum);
    HandleLED.Leddata.Temp = (byte)aht20.getTemperature_C();
    HandleLED.Leddata.Humidity = (byte)sensor.hum;
}   