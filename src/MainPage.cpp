#include <header.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

int color = 0;

timer timepoint(1000, 3);

#ifdef ESP8266
static ESP8266WebServer server(80);
#else
static WebServer server(80)
#endif

bool _Status = false;
bool _flag = false;
byte connecting = 0;

byte MainPage::start(int tries)
{
    static byte _try;

    if (connecting == 0)
    {
        connecting = 1;

        Serial.printf("Connecting to %s ..", SSid);

        if (WiFi.config(ip, gateway, subnet, IPAddress(8, 8, 8, 8), IPAddress(8, 8, 8, 8)) == 0 || SSid[0] == '\0')
        {
            connecting = 3;
            Serial.println(" error");
        }

        WiFi.mode(WIFI_STA);
        WiFi.begin(SSid, pass);

        Wire.begin();


        _try = 0;
    }

    if (connecting == 1)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println(" success");
            connecting = 2;
        }
        if (timepoint.status())
        {
            Serial.print('.');
            _try++;
        }
        if (_try >= tries)
        {
            Serial.println(" error");
            connecting = 3;
        }
    }

    if (connecting == 2)
    {
        Serial.println(WiFi.localIP());

        server.onNotFound([]()
                          { server.send(200, "text/html", WebPage); });
        server.on("/send", GetData);
        server.begin();

        connecting = 4;

        for (int i = 0; i < 4; i++)
            if (WiFi.localIP()[i] != ip[i])
            {
                Serial.println(" error");
                connecting = 3;
            }

        _Status = true;
    }
    return connecting;
}

void MainPage::tick()
{
    if (_Status)
        server.handleClient();
}

bool MainPage::status()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        _Status = false;
    }
    return _Status;
}

void MainPage::stop()
{
    WiFi.disconnect();
    WiFi.softAPdisconnect();
    server.close();
}

void MainPage::reset()
{
    stop();
    connecting = 0;
}

void MainPage::send(String data)
{
    server.send(200, "text/plane", data);
}

void GetData()
{
    Serial.printf("\n");
    Serial.print(server.arg("str"));
    color = server.arg("str").toInt();
}

