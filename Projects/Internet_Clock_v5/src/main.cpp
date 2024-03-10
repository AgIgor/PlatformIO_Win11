#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

#include <ArduinoJson.h>

#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;

#include <BH1750.h>
BH1750 lightMeter;

#include <MQTT.h>
WiFiClient WIFI;
MQTTClient MQTT;

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels (24, 1, NEO_GRB + NEO_KHZ800);

#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
const long utcOffsetInSeconds =  -10800;
NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds,60000);

//==========* Variaveis *==========//

#define BRILHO_MAX    255
#define BRILHO_MIN      2

#define LUX_MAX         3
#define LUX_MIN         2

#define DELAY_CLOCK    6
#define DELAY_TEMP     4
#define DELAY_HUMI     4

#define MQTT_USER ""
#define MQTT_PASS ""
#define MQTT_CLIENT "internet_clock#v.5"
#define MQTT_ADDRESS "mqtt.eclipseprojects.io"
#define MQTT_PUBLISH "/mqtt/internet_clock_v.5/SENSORS"
#define MQTT_SUBSCRIBE "/mqtt/internet_clock_v.5/CONFIG/#"

bool LIGHT;
byte* TIME;
byte* TEMP_HUMI;
JsonDocument JSON;
byte RGB[3]={255,0,0};

const byte displayConfig[12][7] = {{0,0,1,2,4,5,6},  //Digito 0
                                   {0,0,0,0,0,0,4},  //Digito 1
                                   {0,0,0,1,3,5,6},  //Digito 2
                                   {0,0,0,1,3,4,5},  //Digito 3
                                   {0,0,0,0,2,3,4},  //Digito 4
                                   {1,1,1,2,3,4,5},  //Digito 5
                                   {1,1,2,3,4,5,6},  //Digito 6
                                   {0,0,0,0,0,1,4},  //Digito 7
                                   {0,1,2,3,4,5,6},  //Digito 8
                                   {0,0,1,2,3,4,5},  //Digito 9
                                   {0,0,0,0,1,2,3},  //Grau
                                   {2,2,2,2,3,4,6}}; //Umidade;


//==========* Funções *==========//

void mqttSend(){

  /*
    char ct[5];
    char *char_temp = dtostrf(tempFloat,4,2,ct);
    client.publish("/mqtt/internet_clock_v.4/temperature", char_temp);
    
    char ch[5];
    char *char_humi = dtostrf(humiFloat,4,2,ch);
    client.publish("/mqtt/internet_clock_v.4/humidity",char_humi);

    char out[50];
    sprintf(out, "{\"temperature\":%.1f,\"humidity\":%.1f}", tempFloat, humiFloat);
  */

  String S_JSON = "";
  serializeJson(JSON, S_JSON);
  MQTT.publish( MQTT_PUBLISH, S_JSON , false, 0 );
  delay(10);

}
//end mqttSend

void nextRainbowColor() {
  if (RGB[0] > 0 && RGB[2] == 0) {
    RGB[0]--;
    RGB[1]++;
  }
  if (RGB[1] > 0 && RGB[0] == 0) {
    RGB[1]--;
    RGB[2]++;
  }
  if (RGB[2] > 0 && RGB[1] == 0) {
    RGB[0]++;
    RGB[2]--;
  }
}
//end nextRainbowColor

void limpaPixels(){

  static bool modeDirection;

  if(modeDirection){
    for (byte i=24; i>0; i--){
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(30);
    }
    modeDirection = !modeDirection;
  }else{
    for (byte i=0; i<24; i++){
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(30);
    }
    modeDirection = !modeDirection;
  }

  pixels.clear();
  delay(30);

}
//end limpa pixels

void piscaPonto( byte* RGB ){

  static long delayBlink;
  static bool BLK;

  if(millis() - delayBlink > 600){
    delayBlink = millis();
    BLK =!BLK;
  }

  if(BLK){

    pixels.setPixelColor(14, pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));
    pixels.show();

  }else{

    pixels.setPixelColor(14, pixels.Color(0, 0, 0));
    pixels.show();

  }

}
//end pisca pontos

bool luxRead(){

  bool lux_flag;
  int lux;

  for(byte i=0;i<5;i++){
    lux = lightMeter.readLightLevel();
    delay(5);
  }

  if(lux >= LUX_MAX){
    pixels.setBrightness(BRILHO_MAX);
    lux_flag = true;
  }//END IF LUX MAX

  if(lux <= LUX_MIN){
    pixels.setBrightness(BRILHO_MIN);
    lux_flag = false;
    RGB[0] = 255;
    RGB[2] = 0;
    RGB[1] = 0;
  }

  JSON["BH1750"]["lux"] = lux;
  return lux_flag;

}
//end lux read

byte* getAHT10(){

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  delay(1);

  float tempFloat = temp.temperature;
  float humiFloat = humidity.relative_humidity;
  JSON["AHT10"]["temp"] = String( tempFloat,1 );
  JSON["AHT10"]["humi"] = String( humiFloat,1 );
  
  static byte digitos[4];
  digitos[0] = (byte)tempFloat / 10;
  digitos[1] = (byte)tempFloat % 10;
  digitos[2] = (byte)humiFloat / 10;
  digitos[3] = (byte)humiFloat % 10;
  return digitos;
}
//end get AHT

void displayTemp( byte* digitos, byte* RGB ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[10][ID]), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS grau
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+7), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[0]][ID]+15), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    pixels.show();
  }

}
//end display temp

void displayHumi( byte* digitos, byte* RGB ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[11][ID]), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS grau
    pixels.setPixelColor((displayConfig[digitos[3]][ID]+7), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+15), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    pixels.show();
  }

}
//end display humi

void display( byte* digitos, byte* RGB ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[digitos[3]][ID]), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Minuto
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+7), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+15), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    
    if(digitos[0] > 0){
      pixels.setPixelColor((displayConfig[digitos[0]][ID]+22), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Hora
    }else{
      pixels.setPixelColor((displayConfig[digitos[0]][ID]+22), pixels.Color(0, 0, 0)); //LEDS DEZENA DE Hora
    }
    pixels.show();
    delay(1);
  }
  
}
//end display

void mqttConnect(){

  MQTT.begin( MQTT_ADDRESS, WIFI );
  delay(5);
  while (!MQTT.connect(MQTT_CLIENT, MQTT_USER, MQTT_PASS)) {
    delay(500);
  }
  MQTT.publish( "/mqtt/internet_clock_v.5/STATUS", "OK" );
  // MQTT.subscribe( MQTT_SUBSCRIBE );

}
//end mqttConnect

byte* getNtp() {

  timeClient.update();
  delay(20);
  static byte digitos[4];
  byte H = timeClient.getHours() != 12 ? timeClient.getHours() % 12 : timeClient.getHours();
  byte M = timeClient.getMinutes();

  digitos[0] = H / 10;  // 2
  digitos[1] = H % 10;  // 3
  digitos[2] = M / 10;  // 0
  digitos[3] = M % 10;  // 2

  JSON["NTP"]["hour"] = timeClient.getHours();
  JSON["NTP"]["minute"] = timeClient.getMinutes();
  
  return digitos;

}
//end getNtp

void wifiConnect(){
  
  WiFi.mode(WIFI_STA);
  WiFi.begin("VIVOFIBRA-79D0", "58331BB245");

  while (WiFi.status() != WL_CONNECTED) {
    pixels.clear();
    delay(20);
    byte loadingWifi[]={0,1,2,3,4,5,6,3};
    for(byte i=0; i<8;i++){

      pixels.setPixelColor(loadingWifi[i], pixels.Color(255, 0, 255));
      pixels.setPixelColor(loadingWifi[i]-1, pixels.Color(0, 0, 0));
      pixels.show();
      delay(200);

    }
  }
  pixels.clear();

}
//end wifiConnect

byte COUNTER;
long int DELAY_COUNTER;
void delayInc(){
  if(millis() - DELAY_COUNTER > 1000){
    DELAY_COUNTER = millis();
    COUNTER++;
  }
}
//end delayInc

void setup(){

  Wire.begin(0, 2);
  aht.begin();
  lightMeter.begin();
  delay(100);
  pixels.begin();
  pixels.setBrightness(BRILHO_MAX);
  pixels.clear();
  delay(100);

  wifiConnect();
  mqttConnect();
  
  timeClient.begin();
  delay(1);

  LIGHT = luxRead();
  TIME = getNtp();
  TEMP_HUMI = getAHT10();

}
//end setup

void loop(){

  TIME = getNtp();
  TEMP_HUMI = getAHT10();
  delay(100);

//==========**==========//
  COUNTER = 0;
  limpaPixels();
  while(COUNTER < DELAY_CLOCK){

    delayInc();
    if( luxRead() ) nextRainbowColor();
    piscaPonto(RGB);
    display( TIME, RGB );
    delay(100);

  }
//==========**==========//
  COUNTER = 0;
  limpaPixels();
  while(COUNTER < DELAY_TEMP){

    delayInc();
    if( luxRead() ) nextRainbowColor();
    displayTemp( TEMP_HUMI, RGB );
    delay(100);

  }
//==========**==========//
  COUNTER = 0;
  limpaPixels();
  while(COUNTER < DELAY_HUMI){
    
    delayInc();
    if( luxRead() ) nextRainbowColor();
    displayHumi( TEMP_HUMI, RGB );
    delay(100);
    
  }
//==========**==========//

  if(WiFi.status() != WL_CONNECTED) wifiConnect();
  if(!MQTT.connected()) mqttConnect();

  JSON["status"]["wifi"]["ssid"] = WiFi.SSID();
  JSON["status"]["wifi"]["STATUS"] = WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected";

  JSON["status"]["mqtt"]["url"] = MQTT_ADDRESS;
  JSON["status"]["mqtt"]["status"] = MQTT.connected() ? "Connected" : "Disconnected";

  mqttSend();
  delay(1);

}
//end loop
