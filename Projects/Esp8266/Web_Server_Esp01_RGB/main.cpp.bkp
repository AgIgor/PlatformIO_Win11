#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
// #include <FS.h>
#include <LittleFS.h>

#define pwmOut 2

byte pwm = 127;
WiFiManager wifiManager;
ESP8266WebServer server(80);

void handleRead();
void handleRoot();
void handleMove();
void handleNotFound();
void getImg();
void handleAnalog();

void listDir(const char *dirname) {
  Serial.printf("Listing directory: %s\n", dirname);

  Dir root = LittleFS.openDir(dirname);

  while (root.next()) {
    File file = root.openFile("r");
    Serial.print("  FILE: ");
    Serial.print(root.fileName());
    Serial.print("  SIZE: ");
    Serial.print(file.size());
    time_t cr = file.getCreationTime();
    time_t lw = file.getLastWrite();
    file.close();
    struct tm *tmstruct = localtime(&cr);
    Serial.printf("    CREATION: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
    tmstruct = localtime(&lw);
    Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
  }
}
void appendFile(const char *path, String message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = LittleFS.open(path, "a");
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
void writeFile(const char *path, String message) {
  Serial.printf("Writing file: %s\n", path);

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  delay(2000);  // Make sure the CREATE and LASTWRITE times are different
  file.close();
}
void deleteFile(const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (LittleFS.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

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
String readFile(const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
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
  analogWrite(pwmOut, 127);
  delay(10);

  if (!MDNS.begin("esp8266")) while (1) { delay(1000);}
  IPAddress ip(192, 168, 15, 222);
  IPAddress gateway(192, 168, 15, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(8, 8, 8, 8);
  WiFi.config(ip, gateway, subnet, dns);
  
  if (!LittleFS.begin()) {
    Serial.println("Falha ao inicializar o sistema de arquivos LittleFS.");
    while (1);
  }
  
  //writeFile("/hello.txt", "Hello World!\n");
  //Serial.println(readFile("/hello.txt"));
  listDir("/");
//   deleteFile("/pwm.txt");
  
  if (!wifiManager.autoConnect("ESP8266-Config")) {
    delay(3000);
    ESP.restart();
  }
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/analog", HTTP_GET, handleAnalog);
  server.on("/fan", HTTP_GET, getImg);
  server.on("/move", HTTP_GET, handleMove);
  server.on("/read", HTTP_GET, handleRead);
  server.onNotFound(handleNotFound);
  server.begin();
  MDNS.addService("http", "tcp", 80);
  
  pwm = readFile("/pwm.txt").toInt();
  pwm == 0 ? pwm = 127 : pwm;
  Serial.print("pwm: ");
  Serial.println(pwm);
  
}

void loop() {
  MDNS.update();
  server.handleClient();
  delay(5);
}

void getImg(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "image/png", readFile("/fan.png"));
}

void handleRead() {
    
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.send(200, "text/plain", String(map(pwm, 0, 255, 0, 100)));
}

void handleRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(200, "text/html", readFile("/ServoEsp01.html"));
}

void handleMove() {
  int range = server.arg("range").toInt();
  if (range >= 0 && range <= 100) {
    pwm = map(range, 0, 100, 0, 255);
    analogWrite(pwmOut, pwm);
    writeFile("/pwm.txt", String(pwm));
    
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.send(200, "text/html", readFile("/ServoEsp01.html"));
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

    if(server.hasArg("analog")){
        Serial.println(server.arg("analog"));
    }
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.send(200, "text/plain", String(analogRead(A0)));
    // server.send(200, "text/plain", String(server.arg("analog")));
    Serial.println(getTemp());
}