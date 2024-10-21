/*Arduino  code for ESP8266 AJAX Webserver
www.circuitdigest.com 
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>


#define LED D0
const char* ssid = "MATRIX_ZIP";
const char* password = "labmatrixzip";
ESP8266WebServer server(80);

#define PIN        4
#define NUMPIXELS 4

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style type="text/css">
</style>
<body style="background-color: #f9e79f ">                                                                                                       
<center>
<div>
  <input type="color" class="button" onChange  ="send(this.value.slice(1))"></input>
  <BR>
</div>
 <br>
<div><h2>
</h2>
</div>
<script>

function send(led_sts) 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
      
    }
  };
  xhttp.open("GET", "led_set?state="+led_sts, true);
  xhttp.send();
}
setInterval(function() 
{
  getData();
}, 2000); 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "adcread", true);
  xhttp.send();
}
</script>
</center>
</body>
</html>
)=====";

int charToInt(char num)
{
if(num > 57){
  num -= 96;
  num += 9;
} else {
  num -= 48;
}
return num;
}

void handleRoot() 
{
 String s = webpage;
 server.send(200, "text/html", s);
}
void sensor_data() 
{
 int a = analogRead(A0);
 int temp= a/4.35;
 String sensor_value = String(temp);
 server.send(200, "text/plane", String(millis()));
}
void led_control() 
{
 String act_state = server.arg("state");
 Serial.println(act_state);

int r = charToInt(act_state[0])*16+charToInt(act_state[1]);
int g = charToInt(act_state[2])*16+charToInt(act_state[3]);
int b = charToInt(act_state[4])*16+charToInt(act_state[5]);


 pixels.setPixelColor(0, r,g,b);
 pixels.setPixelColor(1, r,g,b);
 pixels.setPixelColor(2, r,g,b);

 pixels.show();
 
 
}
void setup(void)
{
  pixels.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(2,OUTPUT); 

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.on("/led_set", led_control);
  server.on("/adcread", sensor_data);
  server.begin();
}
void loop(void)
{
  server.handleClient();
}