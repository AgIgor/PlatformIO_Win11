#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include "FS.h"

#define pwmOut 2

byte pwm;
WiFiManager wifiManager;
ESP8266WebServer server(80);

void handleRead();
void handleRoot();
void handleMove();
void handleNotFound();
void getImg();
String readFile(fs::FS &fs, const char * path);

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
      return "";
  }
  String content = "";
  while (file.available()) {
    content += (char)file.read();
  }
  file.close();
  return content;
}

void setup() {
  Serial.begin(115200);
  
  pinMode(pwmOut, OUTPUT);
  analogWriteFreq(5000);
  analogWrite(pwmOut, pwm);
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

  if (!MDNS.begin("esp8266")) while (1) { delay(1000);}
  if(!SPIFFS.begin()) while (1) { delay(1000);}
  
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

void getImg(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "image/png", readFile(SPIFFS, "/fan.png"));
}

void handleRead() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/plain", String(pwm));
}

void handleRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/html", readFile(SPIFFS, "/ServoEsp01.html"));
}

void handleMove() {
  int range = server.arg("range").toInt();
  if (range >= 0 && range <= 255) {
    pwm = range;
    analogWrite(pwmOut, pwm);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.send(200, "text/html", readFile(SPIFFS, "/ServoEsp01.html"));
  } else {
    server.send(400, "text/plain", "Erro");
  }
}

void handleNotFound() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(404, "text/plain", "Not Found");
}

/*
void handleSSEdata(){
  WiFiClient client = server.client();
  
  if (client) {
    Serial.println("new client");
    serverSentEventHeader(client);
    if (client.connected()) {
      serverSentEvent(client);
      delay(1000); // round about 60 messages per second
    }
    else{

      // give the web browser time to receive the data
      delay(1);
      // close the connection:
      client.stop();
      Serial.println("client disconnected");
    }
  }
}

void serverSentEventHeader(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/event-stream;charset=UTF-8");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Access-Control-Allow-Origin: *");  // allow any connection. We don't want Arduino to host all of the website ;-)
  client.println("Cache-Control: no-cache");  // refresh the page automatically every 5 sec
  client.println();
  client.flush();
}

void serverSentEvent(WiFiClient client) {
  client.println("event: esp8266"); // this name could be anything, really.
  client.print("data: {");
  client.print("\"A0\": ");
  client.print(millis());
  client.print(", \"in5\": ");
  client.print(123);
  client.print(", \"in6\": ");
  client.print(456);
  client.print(", \"text\": ESP8266");    // added just to show how you can add your own parameters
  client.println("}");
  client.println();
  client.flush();
}
*/