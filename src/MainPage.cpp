#include <header.h>

int color = 0;

timer timepoint(1000, 3);

static DNSServer dnsServer;
#ifdef ESP8266
static ESP8266WebServer server(80);
#else
static WebServer server(80)
#endif

bool _Status = false;
bool _flag = false;
byte connecting = 0;

IPAddress apIP(SP_AP_IP);
IPAddress Subnet(255, 255, 255, 0);

byte MainPage::start(int tries)
{
    static byte _try;

    if (connecting == 0)
    {
        //connecting = 1;

        // Serial.printf("Connecting to %s ..", SSid);

        // if (WiFi.config(ip, gateway, subnet, dns, dns2) == 0 || SSid[0] == '\0')
        // {
        //     connecting = 3;
        //     Serial.println(" error");
        // }



        WiFi.mode(WIFI_AP);
        WiFi.softAPConfig(apIP, apIP, Subnet);
        WiFi.softAP(SP_AP_NAME, "00000000");

        dnsServer.start(53, "*", apIP);

        Serial.println(WiFi.localIP());

        server.onNotFound([]()
                          { server.send(200, "text/html", WebPage); });
        server.on("/send", GetData);
        server.begin();

        _Status = true;
        // WiFi.mode(WIFI_STA);

        // WiFi.begin(SSid, pass);
        // WiFi.setPhyMode(WIFI_PHY_MODE_11G);

        // Wire.begin();

        //_try = 0;
    }

    if (connecting == 1)
    {
        // if (true)
        // {
        //     Serial.println(" success");
        //     connecting = 2;
        // }
        // if (timepoint.status())
        // {
        //     Serial.print('.');
        //     _try++;
        // }
        // if (_try >= tries)
        // {
        //     Serial.println(" error");
        //     connecting = 3;
        // }
    }

    if (connecting == 2)
    {
        // Serial.println(WiFi.localIP());

        // server.onNotFound([]()
        //                   { server.send(200, "text/html", WebPage); });
        // server.on("/send", GetData);
        // server.begin();

        connecting = 4;

        // for (int i = 0; i < 4; i++)
        //     if (WiFi.localIP()[i] != ip[i])
        //     {
        //         Serial.println(" error");
        //         connecting = 3;
        //     }
    }
    return connecting;
}

void MainPage::tick()
{
    if (_Status)
    {
        dnsServer.processNextRequest();
        server.handleClient();
    }
}

bool MainPage::status()
{
    // if (WiFi.status() != WL_CONNECTED)
    // {
    //     _Status = false;
    // }
    return _Status;
}

void MainPage::stop()
{
    _Status = 0;
    WiFi.disconnect();
    WiFi.softAPdisconnect();
    server.close();
    dnsServer.stop();
}

void MainPage::reset()
{
    stop();
    start(0);
}

void MainPage::send(String data)
{
    // server.send(200, "text/plane", data);
}

void GetData()
{
    String str = server.arg("str");
    Serial.printf("\nReceived: %s\n", str.c_str());

    int firstSeparator = str.indexOf('|', 1);
    int secondSeparator = str.indexOf('|', firstSeparator + 1);

    if (firstSeparator != -1)
    {
        String type = str.substring(1, firstSeparator);
        String id = str.substring(firstSeparator + 1, secondSeparator);
        String value = str.substring(secondSeparator + 1);

        Serial.printf("Type: %s, ID: %s, Value: %s\n", type.c_str(), id.c_str(), value.c_str());

        if (id == "resetwifi")
        {
            for (int i = adns2; i < 512; i++)
                EEPROM.write(i, 0);
            EEPROM.commit();
        }

        if (id == "resetmemory")
        {
            for (int i = 0; i < 512; i++)
                EEPROM.write(i, 0);
            EEPROM.commit();
        }

        if (id == "reset")
        {
            ESP.reset();
        }

        if (type == "input-text")
        {
            if (id == "ntpServer")
            {
                value.toCharArray(Data.storedNtpServer, antpServerSize);
                EEPROM.put(antpServer, Data.storedNtpServer);
                EEPROM.commit();
            }
        }

        if (type == "settime")
        {
            SetTime(value);
        }

        else if (type == "input-number" || type == "input-range")
        {
            long numberValue = value.toInt();
            if (id == "periodTime")
            {
                Data.storedPeriodTime = numberValue;
                EEPROM.put(aperiodTime, Data.storedPeriodTime);
                EEPROM.commit();
            }
            else if (id == "brightnessRange")
            {
                Data.storedBrightnessRange = numberValue;
                EEPROM.put(abrightnessRange, Data.storedBrightnessRange);
                EEPROM.commit();
            }
            else if (id == "spectrumSpeed")
            {
                Data.storedSpectrumSpeed = numberValue;
                EEPROM.put(aspectrumSpeed, Data.storedSpectrumSpeed);
                EEPROM.commit();
            }
            else if (id == "gradientShift")
            {
                Data.storedGradientShift = numberValue;
                EEPROM.put(agradientShift, Data.storedGradientShift);
                EEPROM.commit();
            }
            else if (id == "gradientSize")
            {
                Data.storedGradientSize = numberValue;
                EEPROM.put(agradientSize, Data.storedGradientSize);
                EEPROM.commit();
            }
            else if (id == "periodHour")
            {
                Data.storedPeriodHour = numberValue;
                EEPROM.put(aperiodHour, Data.storedPeriodHour);
                EEPROM.commit();
            }
            else if (id == "lavaIntensity")
            {
                Data.storedLavaIntensity = numberValue;
                EEPROM.put(alavaIntensity, Data.storedLavaIntensity);
                EEPROM.commit();
            }
        }
        else if (type == "input-color")
        {
            unsigned long colorValue = strtoul(value.c_str(), NULL, 16);
            if (id == "staticColor")
            {
                Data.storedStaticColor = colorValue;
                EEPROM.put(astaticColor, Data.storedStaticColor);
                EEPROM.commit();
            }
            else if (id == "celsiusColor")
            {
                Data.storedCelsiusColor = colorValue;
                EEPROM.put(acelsiusColor, Data.storedCelsiusColor);
                EEPROM.commit();
            }
            else if (id == "percentageColor")
            {
                Data.storedPercentageColor = colorValue;
                EEPROM.put(apercentageColor, Data.storedPercentageColor);
                EEPROM.commit();
            }
        }
        else if (type == "checkbox")
        {
            bool checked = (value == "1");
            byte byteValue = checked ? 1 : 0;
            if (id == "staticCheckbox")
            {
                Data.storedStaticCheckbox = 1;
                EEPROM.put(astaticCheckbox, byteValue);
                EEPROM.commit();
                Data.storedGradientCheckbox = 0;
                EEPROM.put(agradientCheckbox, byteValue);
                EEPROM.commit();
            }
            else if (id == "gradientCheckbox")
            {
                Data.storedGradientCheckbox = 1;
                EEPROM.put(agradientCheckbox, byteValue);
                EEPROM.commit();
                Data.storedStaticCheckbox = 0;
                EEPROM.put(astaticCheckbox, byteValue);
                EEPROM.commit();
            }
            else if (id == "lavaMode")
            {
                Data.storedLavaMode = checked;
                EEPROM.put(alavaMode, byteValue);
                EEPROM.commit();
            }
            else if (id == "celsiusColorCheckbox")
            {
                Data.storedCelsiusColorCheckbox = checked;
                EEPROM.put(acelsiusColorCheckbox, byteValue);
                EEPROM.commit();
            }
            else if (id == "percentageColorCheckbox")
            {
                Data.storedPercentageColorCheckbox = checked;
                EEPROM.put(apercentageColorCheckbox, byteValue);
                EEPROM.commit();
            }
            else if (id == "blinkPointCheckbox")
            {
                Data.storedBlinkPointCheckbox = checked;
                EEPROM.put(ablinkPointCheckbox, byteValue);
                EEPROM.commit();
            }
            else if (id == "firstzero")
            {
                Data.firstZeroCheckbox = checked;
                EEPROM.put(afirstZeroCheckbox, byteValue);
                EEPROM.commit();
            }
            else if (id.indexOf("colorCell") != -1)
            {
                id.remove(0, 9);
                byte index = id.toInt() - 1;
                if (index >= 0 && index < 12)
                {
                    Data.storedFlagTable[index] = checked;
                    EEPROM.put(aFlagTable + index, byteValue);
                    EEPROM.commit();
                }
            }
        }
    }
}
