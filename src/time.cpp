#include <header.h>


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

    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, ntpserver.c_str(), 10800);

    timeClient.begin();
    timeClient.update();
    
    curtime.Hour = timeClient.getHours();
    curtime.Minutes = timeClient.getMinutes();
    curtime.Seconds = timeClient.getSeconds();

    
    int currentHour = timeClient.getHours();
    Serial.print("Hour: ");
    Serial.println(currentHour);

    int currentMinute = timeClient.getMinutes();
    Serial.print("Minutes: ");
    Serial.println(currentMinute);

    int currentSecond = timeClient.getSeconds();
    Serial.print("Seconds: ");
    Serial.println(currentSecond);

    Serial.printf("\nTime has updated\n");
}