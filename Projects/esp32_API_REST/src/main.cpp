#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";

AsyncWebServer server(80);

#define pinBot 4
bool ledState, flag;

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
  pinMode(pinBot, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  IPAddress ip(192, 168, 15, 123);
  IPAddress gateway(192, 168, 15, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(8, 8, 8, 8);
  WiFi.config(ip, gateway, subnet, dns);

  if(!MDNS.begin("esp32")) {
     Serial.println("Error starting mDNS");
     return;
  } 
  
  int chipId;
  for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}
	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: "); Serial.println(chipId);
  
  Serial.println(WiFi.getHostname());
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.getStatusBits());
  Serial.println(WiFi.getTxPower());
  delay(100);  

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  
    String m = "Hello, ESP32 API! \nTxPower: "; 
    m += String(WiFi.getTxPower()); 
    m += "\nStatusBits: ";
    m += String(WiFi.getStatusBits());
    
    request->send(200, "text/plain", m);
  });

  server.on("/api/sensor", HTTP_GET, [](AsyncWebServerRequest *request){
    // Lógica para retornar dados da API GET
    String response = "{\"sensor\":\"ESP32 Sensor\",\"value\":"+String(millis())+"42}";
    request->send(200, "application/json", response);
  });

  server.on("/api/post", HTTP_POST, [](AsyncWebServerRequest *request){ 
    int paramsNr = request->params();

    if(request->hasParam("led")){
      if(request->getParam("led")->value() == "1") ledState = true;
      else ledState = false;
    }

    for(int i=0;i<paramsNr;i++){
 
        // AsyncWebParameter* p = request->getParam(i);
        Serial.print("name: ");
        Serial.print(request->getParam(i)->name());
        Serial.print(" value: ");
        Serial.println(request->getParam(i)->value());
        Serial.println("------");
    }
 
    request->send(200, "text/plain", "message received");
  });

  server.on("/light", HTTP_GET, [] (AsyncWebServerRequest *request) {

      String message;
      if (request->hasParam("led")) {
          message = request->getParam("led")->value();
          message == "1" ? ledState = true : ledState = false;
      } else {
          message = "No message sent";
      }
      //Serial.println(message);
      request->send(200, "text/plain", "Led Status: " + message);
  });



  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  bool botFlag = !digitalRead(pinBot);

  if(botFlag){

    if(!flag){
      flag = true;
      ledState = !ledState;
    }

  }else flag = false;

  digitalWrite(LED_BUILTIN, ledState);
  delay(5);
}

