#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define pinRST 2
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Olá do servidor ESP8266!");
}

void handleHello() {
  server.send(200, "text/plain", "Olá, mundo!");
}

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

  wifiManager.setHostname("RGB XBOX");
  
  if (!wifiManager.autoConnect()) {
    Serial.println("Falha ao conectar e o tempo limite atingido");
    delay(3000);
    ESP.restart();
  }
  Serial.println("Conectado ao WiFi!");
  //WiFi.setHostname("Esp01");
  Serial.println(WiFi.getHostname());
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/hello", HTTP_GET, handleHello);
  
  server.begin();
  Serial.println("Servidor iniciado");
  
}

void loop() {
  server.handleClient();
  delay(100);
}
