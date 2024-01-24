#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";
const char* mqtt_server = "mqtt.eclipseprojects.io";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const char* subscriberTopic = "@igor_db";
const char* publisherTopic = "@igor_esp32";
bool led = false;

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

void reconnect() {
  // Reconectar ao servidor MQTT
  while (!client.connected()) {
    Serial.println("Tentando reconectar ao servidor MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Reconectado ao servidor MQTT");

      // Inscrever-se novamente no tópico do subscriber após a reconexão
      client.subscribe(subscriberTopic);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void publishMessage() {
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
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(0, INPUT_PULLUP);

  // client.setCallback(callback);

  // Conecte-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Configurar o servidor MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Conectar ao servidor MQTT
  while (!client.connected()) {
    Serial.println("Conectando ao servidor MQTT...");
    if (client.connect("ESP32Client")) {
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
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}//end setup

void loop() {
  // Manter a conexão com o servidor MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  publishMessage();
}//end loop