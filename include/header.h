#define SP_AP_IP 192, 168, 0, 1
#define SP_AP_NAME "CHASI local: http://192.168.0.1"

#define UPDATERATE 50

#define PIN D9
#define NUMPIXELS 308

#define TRYCONN 120

#ifndef HEADER_H
#define HEADER_H

#include <adresses.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <DNSServer.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#endif
#include <WiFiUdp.h>

#include <GyverNTP.h>
#include <GyverDS3231Min.h>

#include <Adafruit_NeoPixel.h>

#include <Wire.h>

#include <DFRobot_AHT20.h>
#include <iarduino_DHT.h>

#include <GyverDS3231.h>


extern WiFiClient wifiClient; 

extern const String loginWebPage;
extern String WebPage;

extern int color;

void handleConnect();

void getEEPROMdata();
void GetData();

void SetTime(String value);

IPAddress strtoip(String str);

float fract(float x);
float mix(float a, float b, float t);

struct CRGB {
    uint8_t r, g, b;
    
    CRGB(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
    
    uint32_t to_uint32() const {
        return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
    }
  };

struct data
{
    char storedNtpServer[antpServerSize];
    long storedPeriodTime;
    long storedBrightnessRange;
    uint32_t storedStaticColor;
    long storedSpectrumSpeed;
    long storedGradientShift;
    long storedGradientSize;
    long storedPeriodHour;
    long storedLavaIntensity;
    uint32_t storedCelsiusColor;
    uint32_t storedPercentageColor;
    bool storedStaticCheckbox;
    bool storedSpectrumCheckbox;
    bool storedGradientCheckbox;
    bool storedPeriodCheckbox;
    bool storedLavaMode;
    bool storedCelsiusColorCheckbox;
    bool storedPercentageColorCheckbox;
    bool storedBlinkPointCheckbox;
    bool storedFlagTable[12];
    bool firstZeroCheckbox;
};
extern data Data;

struct Curtime
{
    byte Seconds;
    byte Minutes;
    byte Hour;
    byte Day_Month;
    byte Month;
    int Year;
};

struct leddata
{
    byte Minutes;
    byte Hour;
    byte Day_Month;
    byte Month;
    byte Temp;
    byte Humidity;
};

class AccessPoint
{
public:
    void startCP();
    void tick();
    void stop();
    bool status();
    bool gotStatus();
};

class MainPage
{
public:
    byte start(int tries);
    void tick();
    void stop();
    void reset();
    bool status();
    void send(String data);
};

class timer
{
private:
    long long StartTime;
    byte Mode;
    bool trigger;
    bool act;

public:
    long Time;
    timer(long time, byte mode);
    bool status();
    void start();
};

class handleLED
{
private:
    void show(byte ind, byte num, bool zero);
public:
    handleLED();
    void tick();
    void begin();

    leddata Leddata;
};

class chngNum
{
private:
    long max;
    long num;
    long dl;
    long long ltime;

public:
    chngNum(long Max, long Dl);
    long value();
    void Max(long MAX);
};

class time1
{
public:
    time1();
    void begin();
    void tick();
    Curtime curtime;
};




extern char SSid[32];
extern char pass[32];
extern String NTPServer;
extern IPAddress ip;
extern IPAddress subnet;
extern IPAddress gateway;
extern IPAddress dns;
extern IPAddress dns2;

#endif
