#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <map>
#include <analogWrite.h>
#include "page.h"

const char* ssid = "VIVOFIBRA-79D0";
const char* password = "58331BB245";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Estrutura para guardar as configurações dos pinos
struct PinConfig {
    String type;
    int mode; // 0: INPUT, 1: OUTPUT
};

// Mapa para guardar as configurações de cada pino
std::map<int, PinConfig> pinConfigs;

// Array com os pinos analógicos do ESP32
const int analogPins[] = {32, 33, 34, 35, 36, 39};
const int numAnalogPins = sizeof(analogPins) / sizeof(analogPins[0]);

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.println("Client conectado");
            break;
        case WS_EVT_DISCONNECT:
            Serial.println("Client desconectado");
            break;
        case WS_EVT_DATA: {
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, data);
            if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return;
            }

            const char* pin = doc["pin"];
            const char* mode = doc["mode"];

            if (strcmp(mode, "config") == 0) {
                const char* type = doc["type"];
                int pinNumber = atoi(pin + 4);
                pinConfigs[pinNumber].type = type;

                if (strcmp(type, "digital_out") == 0) {
                    pinMode(pinNumber, OUTPUT);
                    pinConfigs[pinNumber].mode = 1;
                } else if (strcmp(type, "digital_in") == 0) {
                    pinMode(pinNumber, INPUT);
                    pinConfigs[pinNumber].mode = 0;
                } else if (strcmp(type, "analog_out") == 0) {
                    pinMode(pinNumber, OUTPUT);
                    pinConfigs[pinNumber].mode = 1;
                } else if (strcmp(type, "analog_in") == 0) {
                    pinMode(pinNumber, INPUT);
                    pinConfigs[pinNumber].mode = 0;
                }
            } else if (strcmp(mode, "digitalWrite") == 0) {
                int pinNumber = atoi(pin + 4);
                int value = doc["value"];
                digitalWrite(pinNumber, value);
            } else if (strcmp(mode, "analogWrite") == 0) {
                int pinNumber = atoi(pin + 4);
                int value = doc["value"];
                analogWrite(pinNumber, value);
            }
            break; // Importante para sair do case AwsTextMessage
        }
        default:
            break;
    }
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Conectado à rede WiFi com IP: ");
    Serial.println(WiFi.localIP());

    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, index_html, "text/html");
    });

    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.onNotFound(notFound);
    server.begin();
}

void loop() {
    ws.cleanupClients();
    JsonDocument doc;
    JsonArray pinsJson = doc.createNestedArray("pins");

    for (int i = 0; i <= 39; i++) {
        // Ignora pinos que não podem ser usados como GPIOs
        if (i == 34 || i == 35) continue;

        JsonObject pinJson = pinsJson.createNestedObject();
        char pinName[10];
        sprintf(pinName, "GPIO%d", i);
        pinJson["name"] = pinName;

        // Configura o pino como INPUT caso não haja configuração prévia
        if (!pinConfigs.count(i)) {
            pinMode(i, INPUT);
        }

        if (pinConfigs.count(i)) {
            if (pinConfigs[i].mode == 0) { // INPUT
                pinJson["value"] = digitalRead(i);
                // Verifica se é um pino analógico E se está configurado como entrada analógica
                bool isAnalogPin = false;
                for (int j = 0; j < numAnalogPins; j++) {
                    if (i == analogPins[j]) {
                        isAnalogPin = true;
                        break;
                    }
                }
                if (isAnalogPin && pinConfigs[i].type == "analog_in") {
                    pinJson["analogValue"] = analogRead(i);
                }
            } else { // OUTPUT
                pinJson["value"] = digitalRead(i);
            }
        }
    }

    char json[1024];
    serializeJson(doc, json);
    ws.textAll(json);
    delay(500);
}