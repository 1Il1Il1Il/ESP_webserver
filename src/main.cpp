#include "header.h"

API api;
AccessPoint accessPoint;
MainPage mainPage;
handleLED HandleLED;
timer restartAPtime(1000 * 60 * 15, 3);
timer checkWiFi(1000 * 10, 3);
timer updateTime(UPDATERATE, 3);
timer timeofget(10 * 1  * 1000, 3);
timer SEND(1000, 3);
timer S(1000, 3);

time1 _time;

bool firstconnect = 1;

String NTPServer = "1.pool.ntp.org";

byte _WiFimode = 0;
bool APflag = true;

void setup()
{
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
}

void loop()
{
    show();

    if (S.status())
        Serial.printf("\n%i:%i:%i\t\n", _time.curtime.Hour, _time.curtime.Minutes, _time.curtime.Seconds);

    if (timeofget.status() || (WiFi.status() == WL_CONNECTED && firstconnect))
    {
        firstconnect = 0;
        byte tryGET = 0;
        bool gt = gettime();
        Serial.printf("\n%i\n", gt);
        while (!gt)
        {
            if (tryGET == TRYGET)
            break;
            tryGET++;
            gt = gettime();
        }
    }

    HandleConnect();

    if (updateTime.status())
        HandleLED.tick();
}

void HandleConnect()
{

    mainPage.tick();
    accessPoint.tick();

    if (_WiFimode == 0)
    {
        _WiFimode = mainPage.start(TRYCONN);
        APflag = false;
    }

    if (_WiFimode == 1)
    {
        _WiFimode = mainPage.start(TRYCONN);
    }

    if (_WiFimode == 3 && !APflag)
    {
        mainPage.reset();
        accessPoint.startCP();
        restartAPtime.start();
        APflag = true;
    }

    if (accessPoint.gotStatus() || (restartAPtime.status() && _WiFimode == 3) || (checkWiFi.status() && _WiFimode == 4 && !mainPage.status()))
    {
        accessPoint.stop();
        mainPage.reset();
        _WiFimode = 0;
    }
}

bool gettime()
{
    if (WiFi.status() != WL_CONNECTED)
        return 0;

    byte oldSeconds = _time.curtime.Seconds;
    byte oldMinutes = _time.curtime.Minutes;
    byte oldHour = _time.curtime.Hour;
    byte oldDay_Month = _time.curtime.Day_Month;
    byte oldMonth = _time.curtime.Month;
    int oldYear = _time.curtime.Year;

    _time.update(NTPServer);

    byte CheckHour = _time.curtime.Hour;
    byte CheckMinutes = _time.curtime.Minutes;

    _time.update(NTPServer);

    if ((CheckHour != _time.curtime.Hour) || (CheckMinutes != _time.curtime.Minutes && _time.curtime.Minutes - CheckMinutes != (1 || -59)))
    {
        _time.curtime.Seconds = oldSeconds;
        _time.curtime.Minutes = oldMinutes; 
        _time.curtime.Hour = oldHour;
        _time.curtime.Day_Month = oldDay_Month;
        _time.curtime.Month = oldMonth;
        _time.curtime.Year = oldYear;
        Serial.printf("errorget336");
        return 0;
    }

    return 1;
}

void show()
{
    _time.tick();

    HandleLED.Leddata.Minutes = _time.curtime.Minutes;
    HandleLED.Leddata.Hour = _time.curtime.Hour;
    HandleLED.Leddata.Temp = 99;
    HandleLED.Leddata.Humidity = 50;
    HandleLED.Leddata.Day_Month = _time.curtime.Day_Month;
    HandleLED.Leddata.Month = _time.curtime.Month;
}