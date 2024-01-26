#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define MQQTT_VERSION = MQTT_VERSION_3_1_1

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";
const char* username = "solace-cloud-client";
const char* pass = "pre7c5hajo7k781dk7kvjbfnid";
const char* mqtt_server = "mr-connection-its9016z64v.messaging.solace.cloud";
// const char* mqtt_server = "mqtt.eclipseprojects.io";
// const char* mqtt_server = "192.168.15.155";
// const char* mqtt_server = "3352203942da47b298951cbcd567f978.s1.eu.hivemq.cloud";
// const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void publishMessage();

WiFiClient espClient;
PubSubClient client(espClient);
// PubSubClient client(mqtt_server, mqtt_port, callback, espClient);

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
  reconnect();
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}//end setup

long delayPost;
void loop() {
  // Manter a conexão com o servidor MQTT
  client.loop();
  publishMessage();

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

  if (!client.connected()) {
    reconnect(); 
  }
}//end loop
