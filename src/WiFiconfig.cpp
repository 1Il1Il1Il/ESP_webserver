#include "header.h"

char Pass[32] = "";
char SSid[32] = "";

static DNSServer _SP_dnsServer;
    #ifdef ESP8266
    static ESP8266WebServer _SP_server(80);
    #else
    static WebServer _SP_server(80);
    #endif

void WiFiconfig::startWP() {
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  IPAddress apIP(SP_AP_IP);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(SP_AP_NAME);
  _SP_dnsServer.start(53, "*", apIP);

  _SP_server.onNotFound([]() {
    _SP_server.send(200, "text/html", loginWebPage);
  });
  _SP_server.on("/connect", HTTP_POST, SP_handleConnect);
  _SP_server.begin();
}

void WiFiconfig::tick(){
  _SP_dnsServer.processNextRequest();
  _SP_server.handleClient();
  yield();
}

void SP_handleConnect() {
  strcpy(SSid, _SP_server.arg("ssid").c_str());
  strcpy(Pass, _SP_server.arg("pass").c_str());
}