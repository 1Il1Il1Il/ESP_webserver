#include <header.h>

GyverDS3231Min rtc;

long long ltime = 0;

String ntpprov;

time1::time1()
{
    ltime = millis();
    rtc.begin();
    NTP.begin(3);
    NTP.attachRTC(rtc);
}

void time1::tick()
{
    if (ntpprov.c_str() !=  Data.storedNtpServer)
    {
        ntpprov =  Data.storedNtpServer;
        NTP.setHost(ntpprov);
    }

    if (!NTP.tick())
        return;
    curtime.Hour = NTP.hour();
    curtime.Minutes = NTP.minute();
    curtime.Seconds = NTP.second();
}

