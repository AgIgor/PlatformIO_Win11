#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";
const char* apiUrl = "https://sa-east-1.aws.data.mongodb-api.com/app/data-odkfx/endpoint/data/v1/action/find?secret=1234igor";
const char* apiKey = "ed4QaaObPZKC7UWnqu5tZxFm0fv1RJ7RghRtPy20hRZf9aCsOtjSJuthjG7wOSRL";



void fazerRequisicao() {

  HTTPClient http;
  // Iniciar conexão HTTP

  http.addHeader("Content-Type", "application/json");
  http.addHeader("api-key", apiKey);
  http.begin(apiUrl);

  // Enviar requisição GET e verificar o código de resposta
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["dataSource"] = "Cluster0";
  jsonDoc["database"] = "esp32";
  jsonDoc["collection"] = "CHIP_ID_0001";
  jsonDoc["sort"]["_id"] = -1;

  String output;
  //jsonDoc.shrinkToFit();  // optional
  serializeJson(jsonDoc, output);

  int httpCode = http.POST(output);
  if (httpCode > 0) {
    Serial.printf("[HTTP] Código de resposta: %d\n", httpCode);

    // Ler a resposta da API
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.printf("[HTTP] Falha na requisição. Código de erro: %d\n", httpCode);
  }

  // Fechar conexão
  http.end();
}//


void setup() {
  Serial.begin(115200);

  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Fazer requisição à API
  fazerRequisicao();
}

void loop() {
  // Nada a fazer aqui
}
