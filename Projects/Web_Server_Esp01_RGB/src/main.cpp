#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <FS.h>
// #include <LittleFS.h>

#define pwmOut 2

byte pwm;
WiFiManager wifiManager;
ESP8266WebServer server(80);

String getTemp(){
  long Resistance;
  double Temp;
  int RawADC = analogRead(A0);
  Resistance=((10240000/RawADC) - 10000);
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  return String(Temp);
}

void handleRead();
void handleRoot();
void handleMove();
void handleNotFound();
void getImg();
void handleAnalog();

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
  pinMode(A0, INPUT);
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
  server.on("/analog", HTTP_GET, handleAnalog);
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
    Serial.println(pwm);
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

void handleAnalog() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/plain", String(analogRead(A0)));
  Serial.println(getTemp());
}