#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// uint8_t broadcastAddress[] = {0x58, 0xBF, 0x25, 0x81, 0x3E, 0x98}; //3C:61:05:E3:F2:0D 8266
//uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_message {
  bool bot1;
  bool bot2;
  bool bot3;
  bool bot4;
  int pot1;
  int pot2;
  int pot3;
  int pot4;
} struct_message;

struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer


/* void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
} */

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("b1: ");
  Serial.println(myData.bot1);
  Serial.print("b2: ");
  Serial.println(myData.bot2);
  Serial.print("b3: ");
  Serial.println(myData.bot3);
  Serial.print("b4: ");
  Serial.println(myData.bot4);

  Serial.print("pot1: ");
  Serial.println(myData.pot1);
  Serial.print("pot2: ");
  Serial.println(myData.pot2);
  Serial.print("pot3: ");
  Serial.println(myData.pot3);
  Serial.print("pot4: ");
  Serial.println(myData.pot4);
  Serial.println();
} 

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  // esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  
  // esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}
 
void loop() {
  /* if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    strcpy(myData.a, "THIS IS A Esp8266");
    myData.b = random(1,20);
    myData.c = 1.2;
    myData.d = "Hello";
    myData.e = !myData.e;

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
  } */
}