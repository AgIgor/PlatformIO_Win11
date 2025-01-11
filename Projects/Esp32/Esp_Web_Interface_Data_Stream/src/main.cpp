#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#define FORMAT_LITTLEFS_IF_FAILED true

// Credenciais da rede Wi-Fi
const char* ssid = "VIVOFIBRA-79D0";
const char* password = "58331BB245";

const byte listInput[] = {12,13,14,27};
const byte listOut[] = {2, 4, 5, 15};

bool estadoAtual[sizeof(listInput)]; // Estado atual dos botões
bool estadoAnterior[sizeof(listInput)]; // Estado anterior dos botões

// Criação do servidor e do WebSocket
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// void definePins(byte pin, byte mode){
//   if(mode == 0){
//     pinMode(pin, OUTPUT);
//   }
//   else if(mode == 1){
//     pinMode(pin, INPUT_PULLUP);
//   }
// }

JsonDocument cmnd;
JsonDocument states;
String payload;

void getPinStates(){
  for(byte i=0; i<sizeof(listInput);i++){
    states["inputs"][String(listInput[i])] = digitalRead(listInput[i]) ? 0 : 1;
  }
  for(byte i=0; i<sizeof(listOut);i++){
    states["outputs"][String(listOut[i])] = digitalRead(listOut[i]) ? 1 : 0;
  }

  serializeJson(states, payload);
  Serial.println( payload );
  
}

// Função para lidar com mensagens recebidas do WebSocket
void onWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, 
                        AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    // Converte os dados recebidos para string
    String message = "";
    for (size_t i = 0; i < len; i++) {
      message += (char) data[i];
    }
    Serial.println( message );
    deserializeJson(cmnd, message.c_str());

    if( cmnd["cmnd"].is<JsonVariant>() ){
      digitalWrite( byte(cmnd["cmnd"]["gpio"]) , bool(cmnd["cmnd"]["state"]) );
      // Serial.print( byte(cmnd["cmnd"]["gpio"]) );
      // Serial.print( " : " );
      // Serial.println( bool(cmnd["cmnd"]["state"]) );
    }
  
    // Envia uma resposta para o cliente
    // client->text("Mensagem recebida no ESP32: " + message);
    // Serial.printf("Mensagem recebida: %s\n", message.c_str());
    getPinStates();
    ws.textAll( payload );

  } else if (type == WS_EVT_CONNECT) {
    Serial.printf("Cliente conectado: %u\n", client->id());
    getPinStates();
    client->text( payload );

  } else if (type == WS_EVT_DISCONNECT) {
    Serial.printf("Cliente desconectado: %u\n", client->id());
  }
}

// Função de tarefa no núcleo secundário
void coreTask(void* parameter) {
  while (true) {
    // Incrementa contador como exemplo de processamento
    vTaskDelay(300 / portTICK_PERIOD_MS); // Atraso de 1 segundo

    for(byte i=0; i<sizeof(listInput);i++){
      estadoAtual[i] = digitalRead(listInput[i]);
      // Verificar se houve uma troca de estado de HIGH para LOW
      if (estadoAnterior[i] != estadoAtual[i]) {
        Serial.print("Pino: ");
        Serial.println(listInput[i]);
        getPinStates();
        ws.textAll( payload );
      }
      // Atualizar o estado anterior
      estadoAnterior[i] = estadoAtual[i];
    }
  }
}

void setup() {
  // Inicia a comunicação serial
  Serial.begin(115200);
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
    Serial.println("LittleFS Mount Failed");
    return;
  }

  for(byte i=0; i<sizeof(listOut);i++){
    pinMode(listOut[i], OUTPUT);
  }
  for(byte i=0; i<sizeof(listInput);i++){
    pinMode(listInput[i], INPUT_PULLUP);
    estadoAtual[i] = 1;
    estadoAnterior[i] = 1;
  }

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");
  Serial.println(WiFi.localIP());

  // Configura o WebSocket
  ws.onEvent(onWebSocketMessage);
  server.addHandler(&ws);

  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));
  
  // Configura uma página HTML simples para teste
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/index.html", "text/html");
  });
  server.on("/interruptor", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/interruptor.png", "image/png");
  });
  // Inicia o servidor
  server.begin();
  getPinStates();

  // Cria uma tarefa para rodar no núcleo 0 (separado do núcleo principal)
  xTaskCreatePinnedToCore(
    coreTask,        // Função da tarefa
    "CoreTask",      // Nome da tarefa
    10000,           // Tamanho da stack
    NULL,            // Parâmetro passado para a tarefa
    1,               // Prioridade da tarefa
    NULL,            // Handle da tarefa
    0                // Núcleo onde a tarefa será executada
  );
}

void loop() {
  // Atualiza o WebSocket
  ws.cleanupClients();
  delay(1);
}
