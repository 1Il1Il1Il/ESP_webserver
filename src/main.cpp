#include <Arduino.h>

#define SP_AP_NAME "ESP Config"     // название точки
#define SP_AP_IP 192,168,1,1        // IP точки

#include <DNSServer.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <EEPROM.h>

#include <Adafruit_NeoPixel.h>

static DNSServer _SP_dnsServer;
#ifdef ESP8266
static ESP8266WebServer _SP_server(80);
#else
static WebServer _SP_server(80);
#endif


void StartPortal();


void setup(){
  Serial.begin(9600);

  
Serial.println();
Serial.println();
Serial.println();
Serial.println();
  Serial.println(sizeof(string));
}

void loop(){

}

void StartPortal(){

};
