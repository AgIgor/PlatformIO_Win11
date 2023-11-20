#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";

AsyncWebServer server(80);
AsyncEventSource events("/events");

unsigned long lastTime = 0;  
unsigned long timerDelay = 5000;

float temperature;
float humidity;
float pressure;
float ms;

void getSensorReadings(){
  temperature < 100 ? temperature++ : temperature = 0;
  humidity < 100 ? humidity++ : humidity = 0;
  pressure < 100 ? pressure++ : pressure = 0;
  ms = millis();
}
void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

String processor(const String& var){
  getSensorReadings();

  if(var == "TEMPERATURE"){
    return String(temperature);
  }
  else if(var == "HUMIDITY"){
    return String(humidity);
  }
  else if(var == "PRESSURE"){
    return String(pressure);
  }
  else if(var == "MILLIS"){
    return String(ms);
  }
  return String();
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
    delayMicroseconds(1);
  }
  file.close();
  Serial.println(content);
  return content;
}

void setup() {
  Serial.begin(115200);  
  initWiFi();
  
  if (!LittleFS.begin()) {
    Serial.println("Falha ao inicializar o sistema de arquivos LittleFS.");
    while (1);
  }

  // Habilitando CORS
  // DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));
  // Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String payload = readFile("/index.html");
    request->send_P(200, "text/html", payload.c_str());
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    // client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  server.begin();
}
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    getSensorReadings();
    // Serial.printf("Temperature = %.2f ºC \n", temperature);
    // Serial.printf("Humidity = %.2f \n", humidity);
    // Serial.printf("Pressure = %.2f hPa \n", pressure);
    // Serial.printf("Millis = %.2f ms \n", ms);
    // Serial.println();

    // Send Events to the Web Client with the Sensor Readings
    //events.send(String(ms/1000).c_str(),NULL,millis());
    events.send(String(temperature).c_str(),"temperature",millis());
    events.send(String(humidity).c_str(),"humidity",millis());
    events.send(String(pressure).c_str(),"pressure",millis());
    events.send(String(ms).c_str(),"millis",millis());
    
    lastTime = millis();
  }
}

/*
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);
AsyncEventSource events("/events");

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());

  // Habilitando CORS
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      client->send("hello!", NULL, millis(), 1000);
    }
  });

  server.addHandler(&events);

  server.begin();
}

void loop() {
  // Nada no loop por enquanto, pois o servidor está em um loop interno.
}
*/