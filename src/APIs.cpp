#include <header.h>

const String endpoint0 = "http://tools.aimylogic.com/api/now?tz=Europe/Moscow&format=dd/MM/yyyy";

const String endpoint1 = "http://api.openweathermap.org/data/2.5/weather?q=Krasnodar,pt&APPID=ac7afd30127cfcc54360399c643f5aaa";
const String my_Api_Key = "ac7afd30127cfcc54360399c643f5aaa";
const String my_city = "Lahore";     // specify your city
const String my_country_code = "PK"; // specify your country code

bool first = 1;

String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp2.vniiftri.ru");

API::API()
{
}

String API::Time()
{
    if ((WiFi.status() == WL_CONNECTED))
    {
        if (first)
        {
            timeClient.begin();
            timeClient.setTimeOffset(10800);
            first = 0;
        }
        timeClient.update();
    }

    time_t epochTime = timeClient.getEpochTime();
    Serial.print("Epoch Time: ");
    Serial.println(epochTime);

    String formattedTime = timeClient.getFormattedTime();
    Serial.print("Formatted Time: ");
    Serial.println(formattedTime);

    int currentHour = timeClient.getHours();
    Serial.print("Hour: ");
    Serial.println(currentHour);

    int currentMinute = timeClient.getMinutes();
    Serial.print("Minutes: ");
    Serial.println(currentMinute);

    int currentSecond = timeClient.getSeconds();
    Serial.print("Seconds: ");
    Serial.println(currentSecond);

    String weekDay = weekDays[timeClient.getDay()];
    Serial.print("Week Day: ");
    Serial.println(weekDay);

    // Get a time structure
    struct tm *ptm = gmtime((time_t *)&epochTime);

    int monthDay = ptm->tm_mday;
    Serial.print("Month day: ");
    Serial.println(monthDay);

    int currentMonth = ptm->tm_mon + 1;
    Serial.print("Month: ");
    Serial.println(currentMonth);

    String currentMonthName = months[currentMonth - 1];
    Serial.print("Month name: ");
    Serial.println(currentMonthName);

    int currentYear = ptm->tm_year + 1900;
    Serial.print("Year: ");
    Serial.println(currentYear);

    // Print complete date:
    String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
    Serial.print("Current date: ");
    Serial.println(currentDate);

    Serial.println("");
    return "";
}

String API::GET(String url)
{
    if ((WiFi.status() == WL_CONNECTED))
    {

        WiFiClient client;
        HTTPClient http;

        if (http.begin(client, url.c_str()))
        {
            int httpCode = http.GET();

            if (httpCode > 0)
            {
                Serial.printf("[HTTP] GET... code: %d\n", httpCode);
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
                {
                    String payload = http.getString();
                    Serial.println(payload);
                }
            }
            else
            {
                Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        }
        else
        {
            Serial.println("[HTTP] Unable to connect");
        }
    }
    return "";
}
