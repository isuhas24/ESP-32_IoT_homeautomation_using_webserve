#include <WiFi.h>
#define relay_pin 26
const char* ssid="ESP-32";
const char* password="Wanderer@24";
WiFiServer server(80);
String html="<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>ESP-32 web server</title>\
    <style>\
        .button1{\
            background-color:black;\
            color:white;\
            padding:2%;\
            margin-left:45%;\
            width:10%;\
            display:block;\
            margin-bottom:5%;\
            cursor: pointer;\
        }\
        h1{\
            font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;\
            text-align: center;\
        }\
        h3{\
            text-align: center;\
        }\
    </style>\
</head>\
<body>\
    <h1>IoT using ESP-32</h1>\
    <form>\
        <h3>LED Bulb</h3>\
        <button name=\"button1\" class=\"button1\" value=\"ON\" type=\"submit\">ON</button>\
        <button name=\"button1\" class=\"button1\" value=\"OFF\" type=\"submit\">OFF</button>\
    </form>\
</body>\
</html>";
void connect_WiFi(){
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(100);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relay_pin,OUTPUT);
  digitalWrite(relay_pin,HIGH);
  Serial.println("setting soft access point mode");
  WiFi.softAP(ssid,password);
  IPAddress IP=WiFi.softAPIP();
  Serial.println("AP IP address is:");
  Serial.println(IP);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client=server.available();
  if(client){
    String request=client.readStringUntil('\r');
    if(request.indexOf("button1=ON")!=-1){
      digitalWrite(relay_pin,LOW);
    }
    if(request.indexOf("button1=OFF")!=-1){
      digitalWrite(relay_pin,HIGH);
    }
    client.print(html);
    request="";
  }
}
