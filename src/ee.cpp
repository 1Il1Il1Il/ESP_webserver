#include "header.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void fetchCurrentTime() {
  timeClient.update();
  Serial.print("Current Time: ");
  Serial.println(timeClient.getFormattedTime());
}

void setup() {
  Serial.begin(115200);
  timeClient.begin();
}

void loop() {
  fetchCurrentTime();
  delay(1000);
}
