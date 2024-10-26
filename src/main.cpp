#include <Arduino.h>

#include <ConfigSG.cpp>

#define SP_AP_NAME "ESP Config"
#define SP_AP_IP 192,168,1,1

#include <DNSServer.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <Adafruit_NeoPixel.h>

static DNSServer _SP_dnsServer;
#ifdef ESP8266
static ESP8266WebServer _SP_server(80);
#else
static WebServer _SP_server(80);
#endif

void StartConfPortal();



void setup(){
Serial.begin(115200);
for (int i = 0; i < 10; i++) Serial.println();
Serial.println("#######################################################################################");
Serial.println();

Config config(1024);

config.Add({0,1,245,152,12}, "SSid");
//config.Add("DDDD", "pasass");

config.Save();

}

void loop(){

}