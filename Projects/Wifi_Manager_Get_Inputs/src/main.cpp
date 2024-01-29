#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define FORMAT_LITTLEFS_IF_FAILED true
AsyncWebServer server(80);
//AsyncEventSource events("/events");
AsyncWebSocket ws("/ws");

void notifyClients(String sensorReadings) {
  ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  // Lidar com mensagens recebidas do cliente
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, data, len);

  const char *message = doc["message"];
  Serial.print("Mensagem recebida do cliente: ");
  Serial.println(message);
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }

  String response;
  serializeJson(w_list, response);
  notifyClients(response); // enviar lista para o cliente / receber inputs do cliente

}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void salvarConfiguracao(String strSSID, String strPasswd, String mqtt_url) {
  JsonDocument  docSave;

  docSave["SSID"] = strSSID;
  docSave["Senha"] = strPasswd;
  docSave["URL"] = mqtt_url;

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Erro ao abrir o arquivo de configuração para escrita.");
    return;
  }

  serializeJson(docSave, configFile);
  configFile.close();
}

JsonDocument w_list;
void setup(){
  Serial.begin(115200);
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
    Serial.println("LittleFS Mount Failed");
    return;
  }
  pinMode(0, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  bool flag;
  while(millis()/1000 <= 5){
    // digitalWrite(LED_BUILTIN, (millis()/90)%2);

    if( (millis()/500)%2 ){
      if( flag ){
        Serial.println(millis()/1000);
        flag = false;
      }
    }else{
      flag = true;
    }
    digitalWrite(LED_BUILTIN, flag);

    if(!digitalRead(0)){
      //LittleFS.format();
      deleteFile(LittleFS, "/config.json");
      Serial.println("Format and Reset...");
      delay(700);
      ESP.restart();
    }
  }//end reset btn

  // Verifique se o arquivo JSON de configuração existe
  if (LittleFS.exists("/config.json")){
    //get config
    File configFile = LittleFS.open("/config.json", "r");
    if(!configFile || configFile.isDirectory()){
        Serial.println("- failed to open configFile for reading");
        return;
    }

    JsonDocument  docLoad;
    DeserializationError error = deserializeJson(docLoad, configFile);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    const char* fileSSID = docLoad["SSID"];
    const char* filePASSWD = docLoad["Senha"];
    const char* fileURL = docLoad["URL"];
    configFile.close();
    Serial.println("\nCarregado!");
    delay(200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(fileSSID, filePASSWD);
    Serial.println("");
    byte tenativas;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");

      ++tenativas;
      if(tenativas == 10){
        //LittleFS.format();
        deleteFile(LittleFS, "/config.json");
        Serial.println("Format and reset.");
        delay(700);
        ESP.restart();
      }

    }

    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

  }
  else {
    Serial.println("Arquivo JSON de configuração não encontrado.\n\n");
    WiFi.mode(WIFI_AP);
    const char* name_ap = ESP.getChipModel();
    byte countWifi = WiFi.scanNetworks();
    if (countWifi > 0) {
      for (int i = 0; i < countWifi; ++i) {
        // listWifi[i] = WiFi.SSID(i);
        w_list[i]["SSID"] = WiFi.SSID(i);
        w_list[i]["RSSI"] = WiFi.RSSI(i);
      }
    }
    serializeJson(w_list, Serial);

    if (!WiFi.softAP(name_ap, "12345678")) {
      log_e("Soft AP creation failed.");
      while(1);
    }
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("\n\nAP IP address: ");
    Serial.println(myIP);
    server.begin();
    Serial.println("Server started\n\n");

    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));
    
    // events.onConnect([](AsyncEventSourceClient *client){

    //   if(client->lastId()){
    //     Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    //   }
    //   // send event with message "hello!", id current millis
    //   // and set reconnect delay to 1 second
    //   // client->send("hello!", NULL, millis(), 10000);

    //   delay(1000);
    //   String response;
    //   serializeJson(w_list, response);
    //   client->send(String(response).c_str(),"w_list",millis());

    // });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/index.html", "text/html");
    });
    server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request){

      String url;
      String wifi_ssid;
      String wifi_password;

      if (request->hasParam("wifi_ssid", true)) {
          url = request->getParam("url", true)->value();
          wifi_ssid = request->getParam("wifi_ssid", true)->value();
          wifi_password = request->getParam("wifi_password", true)->value();
      }
      request->send(200, "text/plain", "Salvo!");

      Serial.print("url: ");
      Serial.println(url);

      Serial.print("wifi_ssid: ");
      Serial.println(wifi_ssid); 

      Serial.print("wifi_password: ");
      Serial.println(wifi_password);

      salvarConfiguracao(wifi_ssid, wifi_password, url);
      Serial.println("\nReiniciando..");
      delay(1000);
      ESP.restart();

    });

    ws.onEvent(onEvent);
    server.addHandler(&ws);
    server.onNotFound(notFound);
    //server.addHandler(&events);
    server.begin();
    Serial.println("HTTP server started");
    long msDelay;

    while(true){
      
      // delay(1500);
      // String response;
      // serializeJson(w_list, response);
      // events.send(String(response).c_str(),"w_list",millis());

      long ms = millis();
      if(ms - msDelay > 1000){
        msDelay = ms;
        //events.send(String(ms/1000).c_str(),"millis",millis());
        notifyClients(String(ms/1000).c_str());
        Serial.print("ms: ");
        Serial.println(ms);
      }
      digitalWrite(LED_BUILTIN, (millis()/90)%2);
      ws.cleanupClients();

    }//end while true

  }//not exists /config.json

  digitalWrite(LED_BUILTIN, LOW);
}//end setup

void loop(){

}