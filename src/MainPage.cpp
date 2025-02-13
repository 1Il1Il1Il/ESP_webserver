#include <header.h>

#ifdef ESP8266
static ESP8266WebServer server(80);
#else
static WebServer server(80);
#endif

bool _Status = false;
bool _flag = false;

bool MainPade::start(int tries){
    bool flag = true;

    flag = WiFi.config(ip, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSid, pass);
     
    bool flag2 = false;
    Serial.print("Connecting to WiFi ..");
    for (byte i = 0; i < tries; i++)
    {
        if (WiFi.status() == WL_CONNECTED){
            Serial.println(" success");
            flag2 = true;
            break;
            }
        Serial.print('.');
        delay(1000);  
    }
    if (!flag2) {
        flag = false;
        Serial.println(" error");
    } 
    for (int i = 0; i < 4; i++)
        if (WiFi.localIP()[i] != ip[i]) flag = false;
   
    Serial.println(WiFi.localIP());

    server.onNotFound([]() {
        server.send(200, "text/html", WebPage);
      });
    server.on("/send", GetData);
    server.begin();

    _Status = true;

    return flag;
}

void MainPade::tick(){
    if (_Status)
    server.handleClient();
}

bool MainPade::status(){
     return _Status;
}

void GetData(){
    Serial.printf("\n"); 
    Serial.print(server.arg("str"));
    if (_flag)
    {
        digitalWrite(2, 1);
        _flag = false;
    }
    else
    {
        digitalWrite(2, 0);
        _flag = true;
    }
    
    
}