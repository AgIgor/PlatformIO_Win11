#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
//#include <Servo.h>
#include "root.h"
#define pwmOut 2
//const char* ssid = "VIVOFIBRA-9501";
//const char* password = "rgw7ucm3GT";
byte pwm;

ESP8266WebServer server(80);
//Servo myservo;

void handleRead();
void handleRoot();
void handleMove();
void handleNotFound();

void setup() {
  WiFiManager wifiManager;
  //myservo.attach(2);  // Conecte o servo ao pino GPIO2 (D4
  pinMode(pwmOut, OUTPUT);
  analogWrite(pwmOut, 0);
  delay(10);
  if (!wifiManager.autoConnect("ESP8266-Config")) {
    delay(3000);
    ESP.restart();
  }

//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }

 IPAddress ip(192, 168, 15, 123);
 IPAddress gateway(192, 168, 15, 1);
 IPAddress subnet(255, 255, 255, 0);
 IPAddress dns(8, 8, 8, 8);
 WiFi.config(ip, gateway, subnet, dns);

  if (!MDNS.begin("esp8266")) {
    while (1) { delay(1000); }
  }

  server.on("/", HTTP_GET, handleRoot);
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

void handleRead() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/plain", String(pwm));//String(myservo.read()));
}

void handleRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/html", root);
}

void handleMove() {
  String angleValue = server.arg("angle");
  int angle = angleValue.toInt();
  if (angle >= 0 && angle <= 255) {
    //myservo.write(angle);
    pwm = angle;
    analogWrite(pwmOut, pwm);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.send(200, "text/html", root);
  } else {
    server.send(400, "text/plain", "Ângulo inválido");
  }
}

void handleNotFound() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(404, "text/plain", "Not Found");
}