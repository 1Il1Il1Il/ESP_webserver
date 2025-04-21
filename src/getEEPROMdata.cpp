#include <header.h>

data Data;

void getEEPROMdata()
{
    int i2 = 0;
    for (int i = aSSid; i < (int)sizeof(SSid) + aSSid; i++)
    {
        SSid[i2] = EEPROM.read(i);
        i2++;
    }
    i2 = 0;
    for (int i = apass; i < (int)sizeof(pass) + apass; i++)
    {
        pass[i2] = EEPROM.read(i);
        i2++;
    }
    i2 = 0;
    for (int i = aip; i < 4 + aip; i++)
    {
        ip[i2] = EEPROM.read(i);
        i2++;
    }
    i2 = 0;
    for (int i = agateway; i < 4 + agateway; i++)
    {
        gateway[i2] = EEPROM.read(i);
        i2++;
    }
    i2 = 0;
    for (int i = asubnet; i < 4 + asubnet; i++)
    {
        subnet[i2] = EEPROM.read(i);
        i2++;
    }
    i2 = 0;
    for (int i = adns; i < 4 + adns; i++)
    {
        dns[i2] = EEPROM.read(i);
        i2++;
    }
    i2 = 0;
    for (int i = adns2; i < 4 + adns2; i++)
    {
        dns2[i2] = EEPROM.read(i);
        i2++;
    }

    EEPROM.get(antpServer, Data.storedNtpServer);
    EEPROM.get(aperiodTime, Data.storedPeriodTime);
    EEPROM.get(abrightnessRange, Data.storedBrightnessRange);
    EEPROM.get(astaticColor, Data.storedStaticColor);
    EEPROM.get(aspectrumSpeed, Data.storedSpectrumSpeed);
    EEPROM.get(agradientShift, Data.storedGradientShift);
    EEPROM.get(agradientSize, Data.storedGradientSize);
    EEPROM.get(aperiodHour, Data.storedPeriodHour);
    EEPROM.get(alavaIntensity, Data.storedLavaIntensity);
    EEPROM.get(acelsiusColor, Data.storedCelsiusColor);
    EEPROM.get(apercentageColor, Data.storedPercentageColor);
    Data.storedStaticCheckbox = EEPROM.read(astaticCheckbox);
    Data.storedSpectrumCheckbox = EEPROM.read(aspectrumCheckbox);
    Data.storedGradientCheckbox = EEPROM.read(agradientCheckbox);
    Data.storedPeriodCheckbox = EEPROM.read(aperiodCheckbox);
    Data.storedLavaMode = EEPROM.read(alavaMode);
    Data.storedCelsiusColorCheckbox = EEPROM.read(acelsiusColorCheckbox);
    Data.storedPercentageColorCheckbox = EEPROM.read(apercentageColorCheckbox);
    Data.storedBlinkPointCheckbox = EEPROM.read(ablinkPointCheckbox);

    for (int i = 0; i < 12; i++) {
        Serial.printf("\nbool %i", EEPROM.read(aFlagTable + i));
    }
    Serial.println();

    Serial.println("EEPROM Data Initialized:");

    Serial.print("NTP Server: ");
    Serial.println(Data.storedNtpServer);
    Serial.print("Period Time: ");
    Serial.println(Data.storedPeriodTime);
    Serial.print("Brightness: ");
    Serial.println(Data.storedBrightnessRange);
    Serial.print("Static Color: ");
    Serial.println(Data.storedStaticColor, HEX);
    Serial.print("Spectrum Speed: ");
    Serial.println(Data.storedSpectrumSpeed);
    Serial.print("Gradient Shift: ");
    Serial.println(Data.storedGradientShift);
    Serial.print("Gradient Size: ");
    Serial.println(Data.storedGradientSize);
    Serial.print("Period Hour: ");
    Serial.println(Data.storedPeriodHour);
    Serial.print("Lava Intensity: ");
    Serial.println(Data.storedLavaIntensity);
    Serial.print("Celsius Color: ");
    Serial.println(Data.storedCelsiusColor, HEX);
    Serial.print("Percentage Color: ");
    Serial.println(Data.storedPercentageColor, HEX);
    Serial.print("Static Checkbox: ");
    Serial.println(Data.storedStaticCheckbox);
    Serial.print("Spectrum Checkbox: ");
    Serial.println(Data.storedSpectrumCheckbox);
    Serial.print("Gradient Checkbox: ");
    Serial.println(Data.storedGradientCheckbox);
    Serial.print("Period Checkbox: ");
    Serial.println(Data.storedPeriodCheckbox);
    Serial.print("Lava Mode: ");
    Serial.println(Data.storedLavaMode);
    Serial.print("Celsius Color Checkbox: ");
    Serial.println(Data.storedCelsiusColorCheckbox);
    Serial.print("Percentage Color Checkbox: ");
    Serial.println(Data.storedPercentageColorCheckbox);
    Serial.print("Blink Point Checkbox: ");
    Serial.println(Data.storedBlinkPointCheckbox);
}