#include <header.h>

void startMP(){
    WiFi.config(ip, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSid, pass);
    
    Serial.print("Connecting to WiFi ..");
    for (byte i = 0; i < 50; i++)
    {
        if (WiFi.status() == WL_CONNECTED) break;
        Serial.print('.');
        delay(1000);  
    }
    
    Serial.println(WiFi.localIP());
}