#include <Arduino.h>
#include "pins.h" 
#include <IRremote.hpp>
#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>

char ssid[] = "VIVOFIBRA-79D0";
char pass[] = "58331BB245";
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "mqtt.eclipseprojects.io";
int        port     = 1883;
const char topic[]  = "arduino/simple";


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  IrSender.begin();
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    //Serial.print(".");
    delay(1000);
  }
  if (!mqttClient.connect(broker, port)) {
    //Serial.print("MQTT connection failed! Error code = ");
    //Serial.println(mqttClient.connectError());

    while (1);
  }
  mqttClient.subscribe(topic);
}

const uint16_t rawDataON[] = {4380,4320, 730,470, 730,470, 730,1470, 680,520, 680,470, 780,1420, 730,470, 730,470, 730,470, 680,1470, 730,1470, 730,470, 730,470, 730,470, 730,1420, 780,1420, 730,470, 730,470, 730,470, 680,520, 730,420, 730,1470, 730,1470, 730,470, 680,520, 680,520, 680,470, 730,470, 730,470, 730,470, 730,470, 730,420, 780,420, 780,420, 730,470, 730,470, 730,470, 730,470, 730,470, 730,470, 680,1470, 730,470, 730,470, 730,470, 730,470, 680,520, 680,520, 680,470, 730,1470, 730,470, 730,470, 680,1470, 730,470, 730,1470, 730,470, 730,470, 730,39720, 8980,4420, 730,470, 730,470, 680,520, 680,1620, 680,1620, 730,1570, 680,520, 680,520, 680,520, 680,1620, 680,1620, 730,470, 730,470, 680,520, 680,520, 680,520, 680,520, 730,520, 680,520, 680,520, 680,470, 730,470, 730,1570, 730,520, 680,520, 680,520, 680,520, 680,520, 680,1620, 680,520, 680,1620, 680,520, 680,520, 680,1620, 680,520, 680,19870, 680,520, 680,470, 730,470, 730,520, 680,520, 680,520, 730,470, 680,520, 680,1620, 680,520, 680,520, 680,520, 680,520, 680,520, 730,470, 730,470, 730,470, 730,470, 680,520, 730,470, 730,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 730,470, 730,1570, 680}; // Using exact NEC timing

const uint16_t rawDataOFF[] = {4330,4320, 780,420, 730,470, 730,1420, 780,420, 730,470, 780,1420, 730,470, 730,470, 730,420, 780,1420, 780,1420, 730,470, 730,470, 730,470, 730,1470, 680,470, 730,470, 730,470, 730,470, 730,470, 730,420, 780,1420, 730,1470, 730,470, 730,470, 730,470, 730,470, 730,420, 730,470, 730,470, 730,470, 730,470, 730,470, 730,420, 780,420, 730,470, 730,470, 730,470, 730,470, 730,470, 680,1520, 680,470, 730,470, 730,470, 730,470, 730,470, 730,470, 730,470, 680,1520, 680,470, 730,470, 730,1470, 680,520, 680,1470, 730,470, 730,1470, 730,39720, 8980,4420, 730,470, 680,520, 680,520, 680,520, 730,1620, 680,1570, 730,470, 730,470, 730,470, 680,1620, 730,1570, 730,470, 730,470, 730,470, 730,470, 730,470, 730,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 730,470, 730,470, 730,1570, 680,520, 680,1620, 730,470, 730,520, 680,1570, 730,470, 680,19870, 680,520, 680,520, 680,520, 680,520, 680,520, 730,470, 680,520, 730,520, 680,1570, 730,470, 730,470, 730,470, 680,520, 730,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 680,520, 730,470, 730,470, 730,470, 680,520, 680,520, 680,520, 730,520, 680,520, 680,520, 680}; // Using exact NEC timing

void loop() {


  // IrSender.sendRaw(rawDataON, sizeof(rawDataON) / sizeof(rawDataON[0]), NEC_KHZ); // Note the approach used to automatically calculate the size of the array.
  // delay(3000);
  // IrSender.sendRaw(rawDataOFF, sizeof(rawDataOFF) / sizeof(rawDataOFF[0]), NEC_KHZ); // Note the approach used to automatically calculate the size of the array.
  // delay(3000);
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // we received a message, print out the topic and contents
    // Serial.print("Received a message with topic '");
    // Serial.print(mqttClient.messageTopic());
    // Serial.print("', length ");
    // Serial.print(messageSize);
    // Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient.available()) {
      //Serial.print((char)mqttClient.read());
    }

  }

}
