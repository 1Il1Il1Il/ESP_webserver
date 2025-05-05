#include <header.h>

GyverDS3231 rtc;

long long ltime = 0;

String ntpprov;

time1::time1()
{
    ltime = millis();
    rtc.begin();
    NTP.begin(3);
    rtc.setTime(2025, 4, 26, 14, 44, 0);
    NTP.attachRTC(rtc);
}

void time1::tick()
{
    // if (ntpprov.c_str() !=  Data.storedNtpServer)
    // {
    //     ntpprov =  Data.storedNtpServer;
    //     NTP.setHost(ntpprov);
    // }
    if (rtc.tick() && !rtc.newSecond())
        return;

    Datime dt = rtc;

    curtime.Hour = dt.hour;
    curtime.Minutes = dt.minute;
    curtime.Seconds = dt.second;
}

void time1::begin()
{
    setStampZone(3);
    rtc.begin();
    if (rtc.isReset())
    {
        rtc.setBuildTime();
    }
}

void SetTime(String value)
{
    int yearEnd = value.indexOf('-');
    int monthEnd = value.indexOf('-', yearEnd + 1);
    int dayEnd = value.indexOf('T', monthEnd + 1);
    int hourEnd = value.indexOf(':', dayEnd + 1);
    int minuteEnd = value.indexOf(':', hourEnd + 1);

    String yearStr = value.substring(0, yearEnd);
    String monthStr = value.substring(yearEnd + 1, monthEnd);
    String dayStr = value.substring(monthEnd + 1, dayEnd);
    String hourStr = value.substring(dayEnd + 1, hourEnd);
    String minuteStr = value.substring(hourEnd + 1, minuteEnd);
    String secondStr = value.substring(minuteEnd + 1);

    Datime dt;
    dt.year = yearStr.toInt();
    dt.month = monthStr.toInt();
    dt.day = dayStr.toInt();
    dt.hour = hourStr.toInt();
    dt.minute = minuteStr.toInt();
    dt.second = secondStr.toInt();

    Serial.printf("\nSet:\t%i-%i%i-%i%iT%i:%i:%i", dt.year, dt.month / 10, dt.month % 10, dt.day / 10, dt.day % 10, dt.hour, dt.minute, dt.second);

    rtc.setTime(dt);
}