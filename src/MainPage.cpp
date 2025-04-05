#include <header.h>

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

void GetData() {
    String str = server.arg("str");
    Serial.printf("\nReceived: %s\n", str.c_str());

    // Разделение строки на части
    int firstSeparator = str.indexOf('|', 1);
    int secondSeparator = str.indexOf('|', firstSeparator + 1);

    if (firstSeparator != -1 && secondSeparator != -1) {
        String type = str.substring(1, firstSeparator);
        String id = str.substring(firstSeparator + 1, secondSeparator);
        String value = str.substring(secondSeparator + 1);

        Serial.printf("Type: %s, ID: %s, Value: %s\n", type.c_str(), id.c_str(), value.c_str());

        // Обработка различных типов запросов
        if (type == "input-text") {
            if (id == "ntpServer") {
                value.toCharArray((char*)(EEPROM.getDataPtr() + antpServer), antpServerSize); // Явное приведение типа
                EEPROM.commit();
            }
        } else if (type == "input-number") {
            long numberValue = value.toInt();
            if (id == "periodTime") {
                EEPROM.put(aperiodTime, numberValue);
                EEPROM.commit();
            } else if (id == "brightnessRange") {
                EEPROM.put(abrightnessRange, numberValue);
                EEPROM.commit();
            } else if (id == "spectrumSpeed") {
                EEPROM.put(aspectrumSpeed, numberValue);
                EEPROM.commit();
            } else if (id == "gradientShift") {
                EEPROM.put(agradientShift, numberValue);
                EEPROM.commit();
            } else if (id == "gradientSize") {
                EEPROM.put(agradientSize, numberValue);
                EEPROM.commit();
            } else if (id == "periodHour") {
                EEPROM.put(aperiodHour, numberValue);
                EEPROM.commit();
            } else if (id == "lavaIntensity") {
                EEPROM.put(alavaIntensity, numberValue);
                EEPROM.commit();
            }
        } else if (type == "input-color") {
            unsigned long colorValue = strtoul(value.c_str(), NULL, 16);
            if (id == "staticColor") {
                EEPROM.put(astaticColor, colorValue);
                EEPROM.commit();
            } else if (id == "celsiusColor") {
                EEPROM.put(acelsiusColor, colorValue);
                EEPROM.commit();
            } else if (id == "percentageColor") {
                EEPROM.put(apercentageColor, colorValue);
                EEPROM.commit();
            }
        } else if (type == "checkbox") {
            bool checked = (value == "1");
            byte byteValue = checked ? 1 : 0;
            if (id == "staticCheckbox") {
                EEPROM.put(astaticCheckbox, byteValue);
                EEPROM.commit();
            } else if (id == "spectrumCheckbox") {
                EEPROM.put(aspectrumCheckbox, byteValue);
                EEPROM.commit();
            } else if (id == "gradientCheckbox") {
                EEPROM.put(agradientCheckbox, byteValue);
                EEPROM.commit();
            } else if (id == "periodCheckbox") {
                EEPROM.put(aperiodCheckbox, byteValue);
                EEPROM.commit();
            } else if (id == "lavaMode") {
                EEPROM.put(alavaMode, byteValue);
                EEPROM.commit();
            } else if (id == "celsiusColorCheckbox") {
                EEPROM.put(acelsiusColorCheckbox, byteValue);
                EEPROM.commit();
            } else if (id == "percentageColorCheckbox") {
                Serial.println("63452798634578964539784539876453978634528967");
                EEPROM.put(apercentageColorCheckbox, byteValue);
                EEPROM.commit();
            } else if (id == "blinkPointCheckbox") {
                Serial.println("63452798634578964539784539876453978634528967");
                EEPROM.put(ablinkPointCheckbox, byteValue);
                EEPROM.commit();
            }
        }
    }
}

