#include <Arduino.h>
#include"sMQTTBroker.h"
#include <WiFi.h>

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";

IPAddress local_IP(192, 168, 15, 155);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 15, 1);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

sMQTTBroker broker;

void setup(){
    Serial.begin(115200);
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    WiFi.mode(WIFI_STA);
    if (!WiFi.config(local_IP, gateway, subnet/*, primaryDNS, secondaryDNS*/)){
      Serial.println("Configuration Failed!");
    }
    WiFi.begin(ssid, password);
    Serial.println("");
  
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    const unsigned short mqttPort=1883;
    broker.init(mqttPort);
    // all done
    digitalWrite(LED_BUILTIN, LOW);
}
long delayBlink;
void loop(){
    broker.update();
    
    if(millis() - delayBlink > 300){
      delayBlink = millis();
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}