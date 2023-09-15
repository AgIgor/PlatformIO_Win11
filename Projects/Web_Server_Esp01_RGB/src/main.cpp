#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <FS.h>
//#include "root.h"

#define pwmOut 2

byte pwm;
WiFiManager wifiManager;
ESP8266WebServer server(80);

void handleRead();
void handleRoot();
void handleMove();
void handleNotFound();
void getImg();

void setup() {
  pinMode(pwmOut, OUTPUT);
  analogWriteFreq(5000);
  analogWrite(pwmOut, 0);
  delay(10);
  if (!wifiManager.autoConnect("ESP8266-Config")) {
    delay(3000);
    ESP.restart();
  }

 IPAddress ip(192, 168, 15, 123);
 IPAddress gateway(192, 168, 15, 1);
 IPAddress subnet(255, 255, 255, 0);
 IPAddress dns(8, 8, 8, 8);
 WiFi.config(ip, gateway, subnet, dns);

  if (!MDNS.begin("esp8266")) {
    while (1) { delay(1000); }
  }
  
  if (!SPIFFS.begin()) {
    while (1) { delay(1000); }
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/fan", HTTP_GET, getImg);
  server.on("/move", HTTP_GET, handleMove);
  server.on("/read", HTTP_GET, handleRead);
  server.onNotFound(handleNotFound);
  server.begin();
  MDNS.addService("http", "tcp", 80);
}

void loop() {
  MDNS.update();
  server.handleClient();
  delay(5);
}

String readFile(const char *path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    return "";
  }

  String content = "";
  while (file.available()) {
    content += (char)file.read();
  }
  file.close();
  return content;
}

void getImg(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "image/png", readFile("/fan.png"));
}

void handleRead() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/plain", String(pwm));
}

void handleRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/html", readFile("/ServoEsp01.html"));
  // server.send(200, "text/html", root);
}

void handleMove() {
  int range = server.arg("range").toInt();
  if (range >= 0 && range <= 255) {
    pwm = range;
    analogWrite(pwmOut, pwm);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.send(200, "text/html", readFile("/ServoEsp01.html"));
    // server.send(200, "text/html", root);
  } else {
    server.send(400, "text/plain", "Erro");
  }
}

void handleNotFound() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(404, "text/plain", "Not Found");
}