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

#define DELAY_CLOCK    8
#define DELAY_TEMP     4
#define DELAY_HUMI     4

#define DELAY_LOOP_1 10
#define DELAY_LOOP_2 15
#define DELAY_LOOP_3 20

#define WIFI_SSID "VIVOFIBRA-79D0"
#define WIFI_PASS "58331BB245"

#define MQTT_USER ""
#define MQTT_PASS ""
#define MQTT_CLIENT "internet_clock#v.5"
#define MQTT_ADDRESS "mqtt.eclipseprojects.io"

byte* TIME;
byte* TEMP_HUMI;
JsonDocument JSON;
//byte RGB[3]={255,0,0};
unsigned long int PIXEL_HUE;

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
                                   {4,4,4,4,4,5,6}}; //Umidade;

//==========* Funções *==========//

void mqttSend(bool SYSTEM){

  String S_JSON = "";
  serializeJson(JSON, S_JSON);
  if(SYSTEM) MQTT.publish( "/mqtt/internet_clock_v.5/SENSORS", S_JSON , true, 0 );
  else MQTT.publish( "/mqtt/internet_clock_v.5/RESPONSE", S_JSON , true, 0 );

}
//end mqttSend

/* 
void nextRainbowColor() {
  static unsigned long nextRainbow;

  if( millis() - nextRainbow > 150 ){
    nextRainbow = millis();
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
}
//end nextRainbowColor
 */

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

}
//end limpa pixels

void piscaPonto( /* byte* RGB */ ){

  static long delayBlink;
  static bool BLK;

  if(millis() - delayBlink > 600){
    delayBlink = millis();
    BLK =!BLK;
  }

  if(BLK){

    pixels.setPixelColor(14, pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));;;
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

  for(byte i=0;i<15;i++){
    lux = lightMeter.readLightLevel();
  }

  if(lux >= LUX_MAX){
    pixels.setBrightness(BRILHO_MAX);
    lux_flag = true;
  }//END IF LUX MAX

  if(lux <= LUX_MIN){
    pixels.setBrightness(BRILHO_MIN);
    lux_flag = false;
    // RGB[0] = 255;
    // RGB[2] = 0;
    // RGB[1] = 0;
  }

  JSON["BH1750"]["lux"] = lux;
  return lux_flag;

}
//end lux read

byte* getAHT10(){

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  double tempFloat = temp.temperature;
  double humiFloat = humidity.relative_humidity;

  JSON["AHT10"]["temp"] = round(tempFloat * 10) / 10.0;
  JSON["AHT10"]["humi"] = round(humiFloat * 10) / 10.0;
  
  static byte digitos[4];
  digitos[0] = (byte)tempFloat / 10;
  digitos[1] = (byte)tempFloat % 10;
  digitos[2] = (byte)humiFloat / 10;
  digitos[3] = (byte)humiFloat % 10;
  return digitos;
}
//end get AHT

void displayTemp( byte* digitos/* , byte* RGB */ ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[10][ID]), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2])); //LEDS grau
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+7), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[0]][ID]+15), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS UNIDADE DE Hora
    pixels.show();
  }

}
//end display temp

void displayHumi( byte* digitos/* , byte* RGB */ ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[11][ID]), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2])); //LEDS grau
    pixels.setPixelColor((displayConfig[digitos[3]][ID]+7), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+15), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS UNIDADE DE Hora
    pixels.show();
  }

}
//end display humi

void display( byte* digitos/* , byte* RGB */ ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[digitos[3]][ID]), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS UNIDADE DE Minuto
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+7), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+15), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS UNIDADE DE Hora
    
    if(digitos[0] > 0){
      pixels.setPixelColor((displayConfig[digitos[0]][ID]+22), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));//pixels.Color(RGB[0], RGB[1], RGB[2]));//LEDS DEZENA DE Hora
    }else{
      pixels.setPixelColor((displayConfig[digitos[0]][ID]+22), pixels.Color(0, 0, 0)); //LEDS DEZENA DE Hora
    }
    pixels.show();
  }
  
}
//end display

void mqttConnect(){

  MQTT.begin( MQTT_ADDRESS, WIFI );
  if (!MQTT.connect(MQTT_CLIENT, MQTT_USER, MQTT_PASS)) {
    return;
  }
  MQTT.publish( "/mqtt/internet_clock_v.5/BOOT", ESP.getResetReason() , false, 0 );
  MQTT.subscribe( "/mqtt/internet_clock_v.5/CMD" );

  // ESP.getResetInfo();

}
//end mqttConnect

byte* getNtp() {

  timeClient.update();
  static byte digitos[4];
  byte H = timeClient.getHours() != 12 ? timeClient.getHours() % 12 : timeClient.getHours();
  byte M = timeClient.getMinutes();

  digitos[0] = H / 10;  // 2
  digitos[1] = H % 10;  // 3
  digitos[2] = M / 10;  // 0
  digitos[3] = M % 10;  // 2

  // JSON["NTP"]["hour"] = timeClient.getHours();
  // JSON["NTP"]["minute"] = timeClient.getMinutes();
  JSON["NTP"]["clock"] = timeClient.getFormattedTime();
  return digitos;

}
//end getNtp

void wifiConnect(){
  
  WiFi.mode(WIFI_STA);
  WiFi.begin( WIFI_SSID , WIFI_PASS );
  const byte loadingWifi[3][6]={{0,1,2,6,5,4},
                                {7,8,9,13,12,11},
                                {15,16,17,21,20,19}};

  while (WiFi.status() != WL_CONNECTED) {
    
    pixels.clear();
    //for(byte c=0; c<3;c++){
      for(byte l=0; l<6; l++){
        pixels.setPixelColor( loadingWifi[0][l], pixels.Color(255, 0, 0) );
        pixels.setPixelColor( loadingWifi[0][l-1], pixels.Color(0, 0, 0) );
        pixels.show();
        delay(100);
      }
    //}
    //delay(200);

  }
  pixels.clear();

}
//end wifiConnect

void messageReceived(String &topic, String &payload) {

  //Serial.println("incoming: " + topic + " - " + payload);
  MQTT.publish( "/mqtt/internet_clock_v.5/RECEBIDO", payload , false, 0 );

  if(payload == "GET"){
    mqttSend(false);
  }

}
//end message received

void setup(){

  Wire.begin(0, 2);
  if(!aht.begin()) while(true);
  if(!lightMeter.begin()) while(true);
  pixels.begin();
  pixels.setBrightness(BRILHO_MAX);
  pixels.clear();

  if( luxRead() ) PIXEL_HUE = millis();//nextRainbowColor();
  else PIXEL_HUE = 0;

  wifiConnect();
  mqttConnect();
  MQTT.onMessage(messageReceived);

  timeClient.begin();

  TIME = getNtp();
  TEMP_HUMI = getAHT10();


  ESP.wdtEnable(3000);

}
//end setup

void loop(){

  byte COUNTER = 0;
  limpaPixels();
  while(COUNTER++ <= 50){
    MQTT.loop();

    if( luxRead() ) PIXEL_HUE = millis();//nextRainbowColor();
    else PIXEL_HUE = 0;
    piscaPonto(/* RGB */);
    display( TIME/* , RGB */ );
    delay(100);

  }

  COUNTER = 0;
  limpaPixels();
  while(COUNTER++ <= 30){

    MQTT.loop();
    if( luxRead() ) PIXEL_HUE = millis();//nextRainbowColor();
    else PIXEL_HUE = 0;
    displayTemp( TEMP_HUMI/* , RGB */ );
    delay(100);

  }
  COUNTER = 0;
  limpaPixels();
  while(COUNTER++ <= 30){

    MQTT.loop();
    if( luxRead() ) PIXEL_HUE = millis();//nextRainbowColor();
    else PIXEL_HUE = 0;
    displayHumi( TEMP_HUMI/* , RGB */ );
    delay(100);

  }

  TIME = getNtp();
  TEMP_HUMI = getAHT10();

  //if(WiFi.status() != WL_CONNECTED) setup(); //wifiConnect();
  if(!MQTT.connected()) mqttConnect();
  else mqttSend(true);

  ESP.wdtFeed();

}
//end loop