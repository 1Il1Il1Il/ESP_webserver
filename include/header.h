#define SP_AP_NAME "ESP Config"     // название точки
#define SP_AP_IP 192,168,1,1        // IP точки

#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>

#include <DNSServer.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

extern const String loginWebPage;

void StartWebSite();
void SP_handleConnect();

class WiFiconfig
{
public:
    void startWP();
    void tick();
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
extern char Pass[32];

#endif
