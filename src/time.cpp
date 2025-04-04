#include <header.h>

GyverDS3231Min rtc;

long long ltime = 0;

time1::time1()
{
    ltime = millis();
}

void time1::tick()
{
    if (millis() - ltime >= 1000)
    {
        curtime.Seconds += (byte)((millis() - ltime) / 1000);
        ltime = millis();
        if (curtime.Seconds >= 60)
        {
            curtime.Seconds -= 60;
            curtime.Minutes++;
            if (curtime.Minutes >= 60)
            {
                curtime.Minutes -= 60;
                curtime.Hour++;
                if (curtime.Hour >= 24)
                    curtime.Hour -= 24;
            }
        }
    }
}

void time1::update(String ntpserver)
{
    if (WiFi.status() != WL_CONNECTED)
        return;

    rtc.begin();
    NTP.setHost(ntpserver);
    NTP.begin(3);
    NTP.attachRTC(rtc);

    if (!NTP.tick())
        return;

    curtime.Hour = NTP.hour();
    curtime.Minutes = NTP.minute();
    curtime.Seconds = NTP.second();

    Serial.printf("\nTime has updated\th%i m%i s%i\t\n\n", curtime.Hour, curtime.Minutes, curtime.Seconds);
}