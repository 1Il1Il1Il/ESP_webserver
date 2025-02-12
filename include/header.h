#define SP_AP_NAME "ESP Config"
#define SP_AP_IP 192,168,1,1

#ifndef HEADER_H
#define HEADER_H

#include <adresses.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <DNSServer.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

extern const String loginWebPage;

void handleConnect();
void getEEPROMdata();
void startMP();
IPAddress strtoip(String str);

class AccessPoint
{
public:
    void startCP();
    void tick();
    void stop();
    bool status();
};

class timer
{
private:
    long Time;
    long long StartTime;
    byte Mode;
    bool trigger;
public:
    timer(long time, byte mode);
    bool status();
    void start();
};

extern char SSid[32];
extern char pass[32];
extern IPAddress ip;
extern IPAddress subnet;
extern IPAddress gateway;

#endif
