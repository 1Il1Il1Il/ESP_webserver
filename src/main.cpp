#include "header.h"

WiFiconfig wiFiconfig;

timer Timer1(1000, 0);

void setup(){
    Serial.begin(9600);
    Serial.printf("\n\n\n\n\n################################## START ##################################\n\n");

    wiFiconfig.startWP();
    Timer1.start();
}

void loop(){
    wiFiconfig.tick();
    if (Timer1.status()){
        Serial.printf("\n1");
    }
}

