#include "header.h"

bool Status = false;

char pass[32] = "";
char SSid[32] = "";
IPAddress ip(0, 0, 0, 0);
IPAddress subnet(0, 0, 0, 0);
IPAddress gateway(0, 0, 0, 0);

static DNSServer dnsServer;
#ifdef ESP8266
static ESP8266WebServer server(80);
#else
static WebServer server(80);
#endif

void AccessPoint::startCP() {
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  IPAddress apIP(SP_AP_IP);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(SP_AP_NAME);
  dnsServer.start(53, "*", apIP);

  server.onNotFound([]() {
    server.send(200, "text/html", loginWebPage);
  });
  server.on("/connect", HTTP_POST, handleConnect);
  server.begin();

  Status = true;
}

void AccessPoint::stop() {
  WiFi.softAPdisconnect();
  dnsServer.stop();
  server.close();

  Status = false;
}

void AccessPoint::tick(){
  if (Status){
  dnsServer.processNextRequest();
  server.handleClient();
  yield();
  }
}

bool AccessPoint::status(){
  return Status;
}

void handleConnect() {
  strcpy(SSid, server.arg("ssid").c_str());
  int i2 = 0;
  for (int i = aSSid; i < (int)sizeof(SSid) + aSSid; i++) {EEPROM.write(i, SSid[i2]); i2++;}

  i2 = 0;
  strcpy(pass, server.arg("pass").c_str());
  for (int i = apass; i < (int)sizeof(pass) + apass; i++) {EEPROM.write(i, pass[i2]); i2++;}


  static char buf[15] = "";

  i2 = 0;
  strcpy(buf, server.arg("ip").c_str());
  ip = strtoip(buf);
  for (int i = aip; i < 4 + aip; i++) {EEPROM.write(i, ip[i2]); i2++;}

  i2 = 0;
  strcpy(buf, server.arg("gateway").c_str());
  gateway = strtoip(buf);
  for (int i = agateway; i < 4 + agateway; i++) {EEPROM.write(i, gateway[i2]); i2++;}

  i2 = 0;
  strcpy(buf, server.arg("subnet").c_str());
  subnet = strtoip(buf);
  for (byte i = asubnet; i < 4 + asubnet; i++) {EEPROM.write(i, subnet[i2]); i2++;}

  if (EEPROM.commit()) Serial.printf("\nEEPROM: success!");
  else Serial.printf("\nEEPROM: error!");
  
}

IPAddress strtoip(String str) {
  IPAddress result(0, 0, 0, 0);
  byte buf[str.length()+1];
  str.getBytes(buf, str.length()+1);
  byte i2 = 0;
  for (byte i = 0; i < str.length(); i++)
  {
    if (buf[i] == 46) {
      i2++;
      continue;
    }
    result[i2] = result[i2]*10 + buf[i] - 48;
  }
  return result;
}