#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

//58:BF:25:81:3E:98 esp32
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0xE3, 0xF2, 0x0D};


unsigned long lastTime = 0;  
unsigned long timerDelay = 1000;
bool led = false;

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

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

/* void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("\nBytes received: ");
  Serial.println(len);
  Serial.print("a: ");
  Serial.println(myData.a);
  Serial.print("b: ");
  Serial.println(myData.b);
  Serial.print("c: ");
  Serial.println(myData.c);
  Serial.print("d: ");
  Serial.println(myData.d);
  Serial.print("e: ");
  Serial.println(myData.e);
  Serial.println();
} */

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  // esp_now_register_recv_cb(OnDataRecv);
   
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  

  Serial.println();
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}
 
void loop() {

  if ((millis() - lastTime) > timerDelay) {
    led = !led;
    // strcpy(myData.a, "Esp32");
    myData.bot1 = !led;
    myData.bot2 = led;
    myData.bot3 = !led;
    myData.bot4 = led;

    myData.pot1 = esp_random();
    myData.pot2 = esp_random();
    myData.pot3 = esp_random();
    myData.pot4 = esp_random();

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    lastTime = millis();
  }
 
}