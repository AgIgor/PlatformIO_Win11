#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";
String url = "https://teste-b1ceb-default-rtdb.firebaseio.com/";
String endUrl = "/.json?auth=lnB2E1gGijt9Ryb8fWTFnelL4f7VWCPImvWTUBEP";
String uri;
String chip_id = "/CHIP_ID_";

void makeRequest(String url) {
  HTTPClient http;

  // Iniciar a conexão
  http.begin(url);

  // Enviar a requisição GET e aguardar a resposta
  int httpCode = http.GET();

  if (httpCode > 0) {
    // Se a resposta for bem-sucedida, processar os dados JSON
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Resposta JSON: " + payload);

      // Parse do JSON
      DynamicJsonDocument doc(1024); // Tamanho do documento depende do seu JSON
      deserializeJson(doc, payload);

      // A partir daqui, você pode acessar os dados do JSON
      const char* valor = doc["chave"].as<const char*>();
      Serial.println("Valor da chave: " + String(valor));
    }
  } else {
    Serial.println("Falha na requisição HTTP");
  }

  // Fechar a conexão
  http.end();
}//

void postRequest(String url) {
  // Iniciar a conexão
  HTTPClient http;

  // json_id.add("chip_id", ESP.getEfuseMac());
  // json_id.add("chip_model", ESP.getChipModel());
  // json_id.add("chip_rev", ESP.getChipRevision());
  // json_id.add("chip_cores", ESP.getChipCores());

  String strBody;
  DynamicJsonDocument dataJson(1024);
  dataJson["chip_model"] = ESP.getChipModel();
  dataJson["chip_rev"] = ESP.getChipRevision();
  dataJson["chip_cores"] = ESP.getChipCores();
  dataJson["ts_db"][".sv"] = "timestamp";
  //dataJson["teste"]["ts"]["esp"] = millis();
  serializeJson(dataJson, strBody);

  http.begin(url);

  // Enviar a requisição GET e aguardar a resposta
  int httpCode = http.POST(strBody);

  if (httpCode > 0) {
    // Se a resposta for bem-sucedida, processar os dados JSON
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Resposta JSON: " + payload);

      // Parse do JSON
      DynamicJsonDocument doc(1024); // Tamanho do documento depende do seu JSON
      deserializeJson(doc, payload);

      // A partir daqui, você pode acessar os dados do JSON
      const char* valor = doc["chave"].as<const char*>();
      Serial.println("Valor da chave: " + String(valor));
    }
  } else {
    Serial.println("Falha na requisição HTTP");
  }

  // Fechar a conexão
  http.end();
}

void setup() {
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  // Conectar-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  delay(100);
  uri = url + ESP.getChipModel() + chip_id + ESP.getEfuseMac() + endUrl;
  //ESP32-D0WDQ6/CHIP_ID_167394222128984/.json

  //snprintf(uri, sizeof(uri), "%c%c%c", url, chip_id, endUrl); //esp32/CHIP_ID_0001/.json
  // Fazer a requisição HTTPS
  makeRequest(uri);
}

long delayMillis;
void loop() {
  // Seu código loop aqui
  if(!digitalRead(0)) makeRequest(uri);
  else delay(10);

  if(millis() - delayMillis > 10000){
    delayMillis = millis();
    postRequest(uri);
  }


}

