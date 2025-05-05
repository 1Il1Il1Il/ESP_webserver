#include "header.h"

// bool Status = false;
// bool GotData = false;

char pass[32] = "";
char SSid[32] = "";
IPAddress ip(0, 0, 0, 0);
IPAddress subnet(0, 0, 0, 0);
IPAddress gateway(0, 0, 0, 0);
IPAddress dns(0, 0, 0, 0);
IPAddress dns2(0, 0, 0, 0);

// static DNSServer dnsServer;
// #ifdef ESP8266
// static ESP8266WebServer server(80);
// #else
// static WebServer server(80);
// #endif

void AccessPoint::startCP()
{
  // WiFi.softAPdisconnect();
  // WiFi.disconnect();

  // IPAddress apIP(SP_AP_IP);
  // IPAddress subnet(255, 255, 255, 0);

  // WiFi.mode(WIFI_AP);
  // WiFi.softAPConfig(apIP, apIP, subnet);
  // WiFi.softAP(SP_AP_NAME);

  // dnsServer.start(53, "*", apIP);

  // server.on("/", HTTP_GET, []()
  //           { server.send(200, "text/html", loginWebPage); });

  // server.onNotFound([]()
  //                   { server.send(200, "text/html", loginWebPage); });

  // server.on("/connect", HTTP_POST, handleConnect);
  // server.begin();

  // Status = true;
  // GotData = false;

  // Serial.printf("\nAP mode started. Access config at http://%s\n", apIP.toString().c_str());
}

void AccessPoint::stop()
{
  // WiFi.softAPdisconnect();
  // dnsServer.stop();
  // server.close();

  // GotData = false;
  // Status = false;
  // Serial.printf("\nAP mode stopped.\n");
}

void AccessPoint::tick()
{
  // if (Status)
  // {
  //   dnsServer.processNextRequest();
  //   server.handleClient();
  //   yield();
  // }
}

bool AccessPoint::gotStatus()
{
  return 0;
}

bool AccessPoint::status()
{
  return 0;
}

void handleConnect()
{
//   strncpy(SSid, server.arg("ssid").c_str(), sizeof(SSid) - 1);
//   SSid[sizeof(SSid) - 1] = '\0';
//   for (int i = 0; i < sizeof(SSid); i++)
//   {
//     EEPROM.write(aSSid + i, SSid[i]);
//   }

//   strncpy(pass, server.arg("pass").c_str(), sizeof(pass) - 1);
//   pass[sizeof(pass) - 1] = '\0';
//   for (int i = 0; i < sizeof(pass); i++)
//   {
//     EEPROM.write(apass + i, pass[i]);
//   }

//   static char buf[16] = "";

//   strncpy(buf, server.arg("ip").c_str(), sizeof(buf) - 1);
//   buf[(byte)sizeof(buf) - 1] = '\0';
//   ip = strtoip(buf);

//   for (int i = 0; i < 4; i++)
//   {
//     EEPROM.write(aip + i, ip[i]);
//   }

//   strncpy(buf, server.arg("gateway").c_str(), sizeof(buf) - 1);
//   buf[(byte)sizeof(buf) - 1] = '\0';
//   gateway = strtoip(buf);
//   for (int i = 0; i < 4; i++)
//   {
//     EEPROM.write(agateway + i, gateway[i]);
//   }

//   strncpy(buf, server.arg("subnet").c_str(), sizeof(buf) - 1);
//   buf[(byte)sizeof(buf) - 1] = '\0';
//   subnet = strtoip(buf);
//   for (int i = 0; i < 4; i++)
//   {
//     EEPROM.write(asubnet + i, subnet[i]);
//   }

//   strncpy(buf, server.arg("dns").c_str(), sizeof(buf) - 1);
//   buf[sizeof(buf) - 1] = '\0';
//   dns = strtoip(buf);

//   for (int i = 0; i < 4; i++)
//   {
//     EEPROM.write(adns + i, dns[i]);
//     Serial.printf("\nEEPROM write DNS byte %i at addr %i: %i\n", i, adns + i, dns[i]);
//   }

//   strncpy(buf, server.arg("dns2").c_str(), sizeof(buf) - 1);
//   buf[sizeof(buf) - 1] = '\0';
//   dns2 = strtoip(buf);
//   for (int i = 0; i < 4; i++)
//   {
//     EEPROM.write(adns2 + i, dns2[i]);
//     Serial.printf("\nEEPROM write DNS2 byte %i at addr %i: %i\n", i, adns2 + i, dns2[i]);
//   }

//   Serial.printf("\nSSid :\t%s\nPassword :\t%s\n", SSid, pass);
//   Serial.printf("Static IP:\t%s\n", ip.toString().c_str());
//   Serial.printf("Gateway:\t%s\n", gateway.toString().c_str());
//   Serial.printf("Subnet:\t\t%s\n", subnet.toString().c_str());
//   Serial.printf("DNS1:\t\t%s\n", dns.toString().c_str());
//   Serial.printf("DNS2:\t\t%s\n", dns2.toString().c_str());

//   if (EEPROM.commit())
//   {
//     Serial.printf("\nEEPROM write success!");
//   }
//   else
//   {
//     Serial.printf("\nEEPROM write error!");
//   }

//   GotData = true;

//   server.send(200, "text/plain", "Configuration received. Device will attempt to connect to WiFi.");
}

IPAddress strtoip(String str)
{
//   IPAddress result(0, 0, 0, 0);
//   byte octet[4] = {0, 0, 0, 0};
//   int octetIndex = 0;
//   int currentByteValue = 0;

//   for (int i = 0; i < str.length(); i++)
//   {
//     char c = str.charAt(i);
//     if (c == '.')
//     {
//       if (octetIndex < 3)
//       {
//         octet[octetIndex++] = currentByteValue;
//         currentByteValue = 0;
//       }
//       else
//       {
//         return IPAddress(0, 0, 0, 0);
//       }
//     }
//     else if (c >= '0' && c <= '9')
//     {
//       currentByteValue = currentByteValue * 10 + (c - '0');
//       if (currentByteValue > 255)
//       {
//         return IPAddress(0, 0, 0, 0);
//       }
//     }
//     else
//     {
//       return IPAddress(0, 0, 0, 0);
//     }
//   }

//   if (octetIndex == 3)
//   {
//     octet[octetIndex] = currentByteValue;
//     result = IPAddress(octet[0], octet[1], octet[2], octet[3]);
//   }
//   else
//   {
//     result = IPAddress(0, 0, 0, 0);
//   }

return 0;
}