#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "NOME_REDE_WIFI";
const char* password = "SENHA_REDE_WIFI";
const char* mqtt_server = "mqtt.eclipseprojects.io";
const uint16_t mqtt_port = 1883;

const char* mqtt_topic_pub = "topico/publicar";
const char* mqtt_topic_sub = "topico/assinar";

WiFiClient espClient;



void setup() {
  Serial.begin(115200);
  Serial.println("Initializing WiFi...");
  WiFi.begin("Wokwi-GUEST", "", 6);
  Serial.println("Setup done!");
  espClient.connect(mqtt_server, mqtt_port);

}

void reconnect() {
    // Loop até estar conectado
    while (!espClient.connected()) {
        Serial.print("Conectando ao MQTT...");

        // Tenta conectar
        if (espClient.connect(mqtt_server, mqtt_port)) {
            Serial.println("conectado");
            // Assina
            espClient.print("SUBSCRIBE " + String(mqtt_topic_sub) + "\r\n");
            return;
        } else {
            Serial.print("falhou, rc=");
            //Serial.print(espClient.state());
            Serial.println(" tentando novamente em 5 segundos");
            // Espera 5 segundos antes de tentar novamente
            delay(5000);
        }
    }
}

void loop() {
    if (!espClient.connected()) {
        reconnect();
    }

    // Mantém a conexão com o servidor MQTT
    //espClient.loop();

    // Publica uma mensagem
    String message = "Olá MQTT";
    espClient.print("PUBLISH " + String(mqtt_topic_pub) + " " + message + "\r\n");

    // Aguarda por mensagens no tópico assinado
    while (espClient.available()) {
        String line = espClient.readStringUntil('\n');
        if (line.startsWith("MESSAGE")) {
            String topic = line.substring(line.indexOf(' '));
            String payload = espClient.readStringUntil('\n');
            Serial.print("Mensagem recebida no tópico ");
            Serial.print(topic);
            Serial.print(": ");
            Serial.println(payload);
        }
    }

    delay(1000); // Aguarda um segundo antes de repetir o loop
}