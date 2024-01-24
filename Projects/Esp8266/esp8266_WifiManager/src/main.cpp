#include <Arduino.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

#define pinRST 2

void setup() {
  Serial.begin(115200);
  pinMode(pinRST, INPUT_PULLUP);
  
  WiFiManager wifiManager;

  // wifiManager.resetSettings();
  Serial.println("\n\nPress");
  delay(4000);
  while(!digitalRead(pinRST)){
    Serial.println("Apagando!!!");
    wifiManager.resetSettings(); 
    delay(4000);
  }

  if (!wifiManager.autoConnect("ESP8266-Config")) {
    Serial.println("Falha ao conectar e o tempo limite atingido");
    delay(3000);
    ESP.restart();
  }
  Serial.println("Conectado ao WiFi!");
   WiFi.setHostname("Esp01");
}

void loop() {
  // Seu código aqui
}