#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

void setup() {
  LittleFS.begin();

  // Criando um objeto JSON e serializando
  JsonDocument doc;
  doc["nome"] = "João";
  doc["idade"] = 30;
  doc["cidade"] = "São Paulo";

  String jsonString;
  serializeJson(doc, jsonString);

  // Escrevendo o JSON em um arquivo
  File file = LittleFS.open("/config.json", "w");
  if (!file) {
    Serial.println("Erro ao abrir o arquivo");
    return;
  }
  file.print(jsonString);
  file.close();

  Serial.println("JSON salvo com sucesso!");
}

void loop() {
  // ... (seu código aqui)
}