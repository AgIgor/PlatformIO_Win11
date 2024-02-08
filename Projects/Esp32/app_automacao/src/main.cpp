#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>

#define MQQTT_VERSION = MQTT_VERSION_3_1_1
#define FORMAT_LITTLEFS_IF_FAILED true
JsonDocument w_list;
AsyncWebServer server(80);
//AsyncEventSource events("/events");
AsyncWebSocket ws("/ws");

void getFile();
void startServer();
void notifyClients(String sensorReadings);
void notFound(AsyncWebServerRequest *request);
void deleteFile(fs::FS &fs, const char * path);
void callback(char* topic, byte* payload, unsigned int length);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void reconnect(const char* username, const char* pass, const char* mqtt_server);
void salvarConfiguracao(String strSSID, String strPasswd, String mqtt_url, String mqtt_user, String mqtt_pass);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

// solace-cloud-client
// pre7c5hajo7k781dk7kvjbfnid
// mr-connection-its9016z64v.messaging.solace.cloud

// broker.hivemq.com
// mqtt.eclipseprojects.io

const char* subscriberTopic = "@igor_db";
const char* publisherTopic = "@igor_esp32";

JsonDocument  docLoad;
bool led = false;
WiFiClient espClient;
PubSubClient client(espClient);
// PubSubClient client(mqtt_server, mqtt_port, callback, espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println();
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String data = "";
  Serial.print("Conteúdo: ");
  for (int i = 0; i < length; i++) {
    data += (char)payload[i];
    //Serial.print(data);
  }
  
  Serial.println(data);
  Serial.println();

  JsonDocument jsonPayload;
  deserializeJson(jsonPayload, data);
  int sensor1 = jsonPayload["Sensor1"]["Temp"];
  int sensor2 = jsonPayload["Sensor2"]["Humidity"];
  bool sensor3 = jsonPayload["Sensor3"]["Light"];
  String by = jsonPayload["by"];

  Serial.println("Json");
  Serial.println(sensor1);
  Serial.println(sensor2);
  Serial.println(sensor3);
  Serial.println(by);
  Serial.println();

  if(sensor3 and by != "null"){
    led = true;
    client.publish(publisherTopic, "{\"Sensor3\": {\"Light\": true}}");
  }
  else{
    led = false;
    client.publish(publisherTopic, "{\"Sensor3\": {\"Light\": false}}");
  }
}

void reconnect(const char* username, const char* pass, const char* mqtt_server) {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  // Reconectar ao servidor MQTT
  while (!client.connected()) {
    Serial.println("Conectando ao servidor MQTT...");
    const char* chip_model = ESP.getChipModel();
    long chip_id = ESP.getEfuseMac();
    char client_id[50];
    sprintf(client_id, "%s%d",chip_model, chip_id);

    if (client.connect(client_id, username, pass)) {
      Serial.println("Conectado ao servidor MQTT");
      // Inscrever-se no tópico do subscriber
      client.subscribe(subscriberTopic);

    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

/* void publishMessage() {
  // Publicar uma mensagem no tópico do publisher
  if(!digitalRead(0)){
    delay(500);
    led = !led;
    if(led){
      client.publish(publisherTopic, "{\"Sensor3\": {\"Light\": true}}");
      Serial.println("Btn Light: true");  
    }
    else {
      client.publish(publisherTopic, "{\"Sensor3\": {\"Light\": false}}");
      Serial.println("Btn Light: false");  
    }
  }
  digitalWrite(LED_BUILTIN, led);
} */

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

void salvarConfiguracao(String strSSID, String strPasswd, String mqtt_server, String mqtt_user, String mqtt_pass) {
  JsonDocument  docSave;

  docSave["SSID"] = strSSID;
  docSave["Senha"] = strPasswd;
  docSave["mqtt_server"] = mqtt_server;
  docSave["mqtt_user"] = mqtt_user;
  docSave["mqtt_pass"] = mqtt_pass;

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Erro ao abrir o arquivo de configuração para escrita.");
    return;
  }

  serializeJson(docSave, configFile);
  configFile.close();
}

void notifyClients(String sensorReadings) {
  ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  // Lidar com mensagens recebidas do cliente
  JsonDocument doc;
  deserializeJson(doc, data, len);

  const char *message = doc["message"];
  Serial.print("Mensagem recebida do cliente: ");
  Serial.println(message);

  String mqtt_server    = doc["mqtt_server"];
  String mqtt_user      = doc["mqtt_user"];
  String mqtt_pass      = doc["mqtt_pass"];
  String wifi_ssid      = doc["wifi_ssid"];
  String wifi_password  = doc["wifi_password"];
  
  Serial.print("mqtt_server: ");
  Serial.println(mqtt_server);

  Serial.print("wifi_ssid: ");
  Serial.println(wifi_ssid); 

  Serial.print("wifi_password: ");
  Serial.println(wifi_password);

  Serial.print("mqtt_user: ");
  Serial.println(mqtt_user);

  Serial.print("mqtt_pass: ");
  Serial.println(mqtt_pass);

  salvarConfiguracao(wifi_ssid, wifi_password, mqtt_server, mqtt_user, mqtt_pass);
  Serial.println("\nReiniciando..");
  delay(1000);
  ESP.restart();
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:{
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());

      String response;
      serializeJson(w_list, response);
      notifyClients(response);

      break;
    }
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
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void getFile(){
  //get config
  File configFile = LittleFS.open("/config.json", "r");
  if(!configFile || configFile.isDirectory()){
      Serial.println("- failed to open configFile for reading");
      return;
  }

  DeserializationError error = deserializeJson(docLoad, configFile);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* fileSSID = docLoad["SSID"];
  const char* filePASSWD = docLoad["Senha"];

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

  // Configurar o servidor MQTT
  const char* file_mqtt_server  = docLoad["mqtt_server"];
  const char* file_mqtt_user    = docLoad["mqtt_user"];
  const char* file_mqtt_pass    = docLoad["mqtt_pass"];

  Serial.print("Mqtt server: ");
  Serial.print(file_mqtt_server);
  Serial.print(" Mqtt user: ");
  Serial.print(file_mqtt_user);
  Serial.print(" Mqtt pass: ");
  Serial.println(file_mqtt_pass);

  reconnect(file_mqtt_user, file_mqtt_pass, file_mqtt_server);
  delay(100);

}//end get File

void startServer(){
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

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });
/*     
  events.onConnect([](AsyncEventSourceClient *client){

    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    // client->send("hello!", NULL, millis(), 10000);

    delay(1000);
    String response;
    serializeJson(w_list, response);
    client->send(String(response).c_str(),"w_list",millis());

  }); */
/*     
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

  }); */

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
      //notifyClients(String(ms/1000).c_str());
      Serial.print("ms: ");
      Serial.println(ms);

    }
    digitalWrite(LED_BUILTIN, (millis()/90)%2);
    ws.cleanupClients();

  }//end while true
}//end setart server

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
    getFile();
  }
  else {
    startServer();
  }//not exists /config.json

  digitalWrite(LED_BUILTIN, LOW);
}//end setup

long delayPost;
void loop() {
  // Manter a conexão com o servidor MQTT
  client.loop();
  // publishMessage();

  if (client.connected()) {
    if(millis() - delayPost > 3000){

      delayPost = millis();
        char ms[50];
        char* payload;
        // itoa ( millis(), ms, 10 );
        sprintf(ms, "{\"Millis\": {\"Time\":%d}}", millis());
        payload = ms;
        Serial.println(payload);
        //Serial.println(sizeof(payload));
        client.publish(publisherTopic, payload);
    }
  }
  else {
    // Configurar o servidor MQTT
    const char* file_mqtt_server = docLoad["mqtt_server"];
    const char* file_mqtt_user = docLoad["mqtt_user"];
    const char* file_mqtt_pass = docLoad["mqtt_pass"];
    reconnect(file_mqtt_user, file_mqtt_pass, file_mqtt_server);

    Serial.print("Mqtt server: ");
    Serial.print(file_mqtt_server);
    Serial.print(" Mqtt user: ");
    Serial.print(file_mqtt_user);
    Serial.print(" Mqtt pass: ");
    Serial.println(file_mqtt_pass);
    delay(100); 
  }

}//end loop