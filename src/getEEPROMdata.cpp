#include <header.h>

uint32_t storedDns;
uint32_t storedDns2;
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

void getEEPROMdata(){   
    int i2 = 0;
    for (int i = aSSid; i < (int)sizeof(SSid) + aSSid; i++) {SSid[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = apass; i < (int)sizeof(pass) + apass; i++) {pass[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = aip; i < 4 + aip; i++) {ip[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = agateway; i < 4 + agateway; i++) {gateway[i2] = EEPROM.read(i); i2++;}
    i2 = 0;
    for (int i = asubnet; i < 4 + asubnet; i++) {subnet[i2] = EEPROM.read(i); i2++;}

    EEPROM.get(adns, storedDns);
    EEPROM.get(adns2, storedDns2);
    EEPROM.get(antpServer, storedNtpServer);
    EEPROM.get(aperiodTime, storedPeriodTime);
    EEPROM.get(abrightnessRange, storedBrightnessRange);
    EEPROM.get(astaticColor, storedStaticColor);
    EEPROM.get(aspectrumSpeed, storedSpectrumSpeed);
    EEPROM.get(agradientShift, storedGradientShift);
    EEPROM.get(agradientSize, storedGradientSize);
    EEPROM.get(aperiodHour, storedPeriodHour);
    EEPROM.get(alavaIntensity, storedLavaIntensity);
    EEPROM.get(acelsiusColor, storedCelsiusColor);
    EEPROM.get(apercentageColor, storedPercentageColor);
    storedStaticCheckbox = EEPROM.read(astaticCheckbox);
    storedSpectrumCheckbox = EEPROM.read(aspectrumCheckbox);
    storedGradientCheckbox = EEPROM.read(agradientCheckbox);
    storedPeriodCheckbox = EEPROM.read(aperiodCheckbox);
    storedLavaMode = EEPROM.read(alavaMode);
    storedCelsiusColorCheckbox = EEPROM.read(acelsiusColorCheckbox);
    storedPercentageColorCheckbox = EEPROM.read(apercentageColorCheckbox);
    storedBlinkPointCheckbox = EEPROM.read(ablinkPointCheckbox);

  Serial.println("EEPROM Data Initialized:");
  Serial.print("DNS: ");         Serial.println(storedDns);
  Serial.print("DNS2: ");        Serial.println(storedDns2);
  Serial.print("NTP Server: ");  Serial.println(storedNtpServer);
  Serial.print("Period Time: ");  Serial.println(storedPeriodTime);
  Serial.print("Brightness: ");    Serial.println(storedBrightnessRange);
  Serial.print("Static Color: ");  Serial.println(storedStaticColor, HEX);
  Serial.print("Spectrum Speed: ");Serial.println(storedSpectrumSpeed);
  Serial.print("Gradient Shift: ");Serial.println(storedGradientShift);
  Serial.print("Gradient Size: "); Serial.println(storedGradientSize);
  Serial.print("Period Hour: ");   Serial.println(storedPeriodHour);
  Serial.print("Lava Intensity: ");  Serial.println(storedLavaIntensity);
  Serial.print("Celsius Color: "); Serial.println(storedCelsiusColor, HEX);
  Serial.print("Percentage Color: "); Serial.println(storedPercentageColor, HEX);
  Serial.print("Static Checkbox: ");    Serial.println(storedStaticCheckbox);
  Serial.print("Spectrum Checkbox: ");  Serial.println(storedSpectrumCheckbox);
  Serial.print("Gradient Checkbox: ");  Serial.println(storedGradientCheckbox);
  Serial.print("Period Checkbox: ");    Serial.println(storedPeriodCheckbox);
  Serial.print("Lava Mode: ");          Serial.println(storedLavaMode);
  Serial.print("Celsius Color Checkbox: "); Serial.println(storedCelsiusColorCheckbox);
  Serial.print("Percentage Color Checkbox: "); Serial.println(storedPercentageColorCheckbox);
  Serial.print("Blink Point Checkbox: ");   Serial.println(storedBlinkPointCheckbox);
}
