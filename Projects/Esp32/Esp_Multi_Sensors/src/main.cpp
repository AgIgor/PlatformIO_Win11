#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "FS.h"
#include <LITTLEFS.h>
#define FORMAT_LITTLEFS_IF_FAILED true


#define LDR_PIN 36      // Pino do sensor LDR


const char* default_ssid = "VIVOFIBRA-79D0";
const char* default_password = "58331BB245";
const char* default_mqtt_server = "mqtt.eclipseprojects.io";
const int default_mqtt_port = 1883;
const char* default_mqtt_topic = "agigor/esp32/sensors";

// Armazena as configurações da rede e MQTT
struct Config {
  String ssid;
  String password;
  String mqtt_server;
  int mqtt_port;
  String mqtt_topic;
} config;

WiFiClient espClient;
PubSubClient client(espClient);
AsyncWebServer server(80);

void loadConfig() {
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
    Serial.println("LittleFS Mount Failed");
    return;
  }

  File file = LittleFS.open("/config.json", "r");
  if (!file) {
    Serial.println("Arquivo de configuração não encontrado. Usando padrões.");
    config.ssid = default_ssid;
    config.password = default_password;
    config.mqtt_server = default_mqtt_server;
    config.mqtt_port = default_mqtt_port;
    config.mqtt_topic = default_mqtt_topic;
    return;
  }

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println("Erro ao carregar configuração");
  } else {
    config.ssid = doc["ssid"].as<String>();
    config.password = doc["password"].as<String>();
    config.mqtt_server = doc["mqtt_server"].as<String>();
    config.mqtt_port = doc["mqtt_port"];
    config.mqtt_topic = doc["mqtt_topic"].as<String>();
  }

  file.close();
}

void saveConfig() {
  File file = LittleFS.open("/config.json", "w");
  if (!file) {
    Serial.println("Erro ao abrir arquivo de configuração");
    return;
  }

  JsonDocument doc;
  doc["ssid"] = config.ssid;
  doc["password"] = config.password;
  doc["mqtt_server"] = config.mqtt_server;
  doc["mqtt_port"] = config.mqtt_port;
  doc["mqtt_topic"] = config.mqtt_topic;

  serializeJson(doc, file);
  file.close();
}

void connectWiFi() {
  WiFi.begin(config.ssid.c_str(), config.password.c_str());
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void connectMQTT() {
  client.setServer(config.mqtt_server.c_str(), config.mqtt_port);
  while (!client.connected()) {
    Serial.println("Conectando ao MQTT...");
    if (client.connect("ESP32_Client")) {
      Serial.println("Conectado ao MQTT!");
    } else {
      Serial.print("Falha na conexão MQTT, tentando novamente...");
      delay(5000);
    }
  }
}

void sendData() {
  float temperature = millis()/250;
  float humidity = millis()/350;
  int luminosity = analogRead(LDR_PIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Erro ao ler DHT22!");
    return;
  }

  JsonDocument json;
  json["temperature"] = temperature;
  json["humidity"] = humidity;
  json["luminosity"] = luminosity;

  char buffer[256];
  serializeJson(json, buffer);

  Serial.println(buffer);

  if (client.connected()) {
    client.publish(config.mqtt_topic.c_str(), buffer);
  }
}

void setupWebServer() {
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
    JsonDocument json;
    json["ssid"] = config.ssid;
    json["password"] = config.password;
    json["mqtt_server"] = config.mqtt_server;
    json["mqtt_port"] = config.mqtt_port;
    json["mqtt_topic"] = config.mqtt_topic;

    String response;
    serializeJson(json, response);
    request->send(200, "application/json", response);
  });

  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("ssid", true)) {
      config.ssid = request->getParam("ssid", true)->value();
    }
    if (request->hasParam("password", true)) {
      config.password = request->getParam("password", true)->value();
    }
    if (request->hasParam("mqtt_server", true)) {
      config.mqtt_server = request->getParam("mqtt_server", true)->value();
    }
    if (request->hasParam("mqtt_port", true)) {
      config.mqtt_port = request->getParam("mqtt_port", true)->value().toInt();
    }
    if (request->hasParam("mqtt_topic", true)) {
      config.mqtt_topic = request->getParam("mqtt_topic", true)->value();
    }

    saveConfig();
    request->send(200, "text/plain", "Configurações salvas! Reinicie o ESP32.");
  });

  server.begin();
}

void setup() {
  Serial.begin(115200);

  loadConfig();
  connectWiFi();
  connectMQTT();
  setupWebServer();
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();
  sendData();
  delay(5000);
}
