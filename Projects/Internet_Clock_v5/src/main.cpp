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
#define NUM_LEDS 29
Adafruit_NeoPixel pixels (NUM_LEDS, 0, NEO_GRB + NEO_KHZ800);

#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
const long utcOffsetInSeconds =  -10800;
NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds,60000);

//==========* Variaveis *==========//

#define BRILHO_MAX    150
#define BRILHO_MIN      1

#define LUX_MAX         3
#define LUX_MIN         2

#define WIFI_SSID "VIVOFIBRA-79D0"
#define WIFI_PASS "58331BB245"

#define MQTT_USER ""
#define MQTT_PASS ""
#define MQTT_CLIENT "internet_clock#v.5"
#define MQTT_ADDRESS "mqtt.eclipseprojects.io"

bool LUX;
byte* TIME;
byte* TEMP_HUMI;
JsonDocument JSON;
unsigned long int PIXEL_HUE;

const byte displayConfig[13][7] = {{0,0,1,2,4,5,6},  //Digito 0
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
                                   {1,1,1,1,2,5,6},  //Celsius
                                   {1,1,1,1,2,11,12}}; 

//==========* Funções *==========//

void mqttSend(bool SYSTEM){

  String S_JSON = "";
  serializeJson(JSON, S_JSON);
  if(SYSTEM) MQTT.publish( "/mqtt/internet_clock_v.5/SENSORS", S_JSON , true, 0 );
  else MQTT.publish( "/mqtt/internet_clock_v.5/RESPONSE", S_JSON , true, 0 );

}
//end mqttSend

void limpaPixels(){

  static bool modeDirection;

  if(modeDirection){
    for (byte i=NUM_LEDS; i>0; i--){
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(30);
    }
    modeDirection = !modeDirection;
  }else{
    for (byte i=0; i<NUM_LEDS; i++){
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(30);
    }
    modeDirection = !modeDirection;
  }
  pixels.clear();

}
//end limpa pixels

void piscaPonto(){

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

  if(lux > LUX_MAX){

    pixels.setBrightness(BRILHO_MAX);
    lux_flag = true;
  }//END IF LUX MAX

  if(lux < LUX_MIN){

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

void displayTemp( byte* digitos ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[11][ID]), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[10][ID]+7), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+15), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[digitos[0]][ID]+22), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.show();
  }

}
//end display temp

void displayHumi( byte* digitos ){

  for (int ID = 0; ID < 7; ID++){

    pixels.setPixelColor((displayConfig[10][ID]+7), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[10][ID]+10-7), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[digitos[3]][ID]+15), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+22), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.show();
  }

}
//end display humi

void display( byte* digitos ){

  for (int ID = 0; ID < 7; ID++){

    pixels.setPixelColor((displayConfig[digitos[3]][ID]), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+7), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+15), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
    pixels.setPixelColor((displayConfig[digitos[0]][ID]+22), pixels.gamma32(pixels.ColorHSV(PIXEL_HUE)));
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

}
//end mqttConnect

byte* getNtp() {

  timeClient.update();
  static byte digitos[4];
  byte H = timeClient.getHours() ;//!= 12 ? timeClient.getHours() % 12 : timeClient.getHours();
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
  const byte loadingWifi[]={0,1,2,6,5,4};

  while (WiFi.status() != WL_CONNECTED) {

    
    if( luxRead() ) PIXEL_HUE = millis();//nextRainbowColor();
    else PIXEL_HUE = 0;
    
    pixels.clear();
      for(byte l=0; l<6; l++){
        pixels.setPixelColor( loadingWifi[l], pixels.Color(255, 0, 0) );
        pixels.setPixelColor( loadingWifi[l-1], pixels.Color(0, 0, 0) );
        pixels.show();
        delay(100);
      }

  }
  pixels.clear();
  timeClient.update();

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
  delay(500);
  Wire.begin(1, 2);
  if(!aht.begin()) while(true);
  if(!lightMeter.begin()) while(true);
  pixels.begin();
  pixels.setBrightness(BRILHO_MAX);
  pixels.clear();

  if( luxRead() ) PIXEL_HUE = millis();
  else PIXEL_HUE = 0;

  wifiConnect();
  mqttConnect();
  MQTT.onMessage(messageReceived);

  timeClient.begin();

  for(byte i=0; i<5; i++){
    TIME = getNtp();
    TEMP_HUMI = getAHT10();
    delay(100);
  }

  ESP.wdtEnable( 3000 );

}
//end setup

int TEMPO = 30;
int INTERVALO = 100;
void loop(){

  for(byte i=0; i< INTERVALO ;i++){
    
    MQTT.loop();
    if( luxRead() ) PIXEL_HUE = millis();
    else PIXEL_HUE = 0;
    piscaPonto();
    display( TIME );
    delay( TEMPO );

  }
  limpaPixels();

  for(byte i=0; i< INTERVALO ;i++){
    
    MQTT.loop();
    if( luxRead() ) PIXEL_HUE = millis();
    else PIXEL_HUE = 0;
    displayTemp( TEMP_HUMI );
    delay( TEMPO );

  }
  limpaPixels();

  for(byte i=0; i< INTERVALO ;i++){
    
    MQTT.loop();
    if( luxRead() ) PIXEL_HUE = millis();
    else PIXEL_HUE = 0;
    displayHumi( TEMP_HUMI );
    delay( TEMPO );

  }
  limpaPixels();

  if(!MQTT.connected()) mqttConnect();
  else mqttSend(true);

  ESP.wdtFeed();
  TIME = getNtp();
  TEMP_HUMI = getAHT10();

}
//end loop

// unsigned int long TEMPO;
// void loop(){
//   delay(10);

//   TEMPO = millis();
//   limpaPixels();
//   // if( luxRead() ) PIXEL_HUE = millis();
//   // else PIXEL_HUE = 0;

//   while(millis() - TEMPO <= 5000){

//     MQTT.loop();
//     if( LUX ) PIXEL_HUE = millis();
//     else PIXEL_HUE = 0;
//     piscaPonto();
//     display( TIME );
//     delay(100);

//   }

//   TEMPO = millis();
//   limpaPixels();
//   // if( luxRead() ) PIXEL_HUE = millis();
//   // else PIXEL_HUE = 0;

//   while(millis() - TEMPO <= 5000){
    
//     MQTT.loop();
//     if( LUX ) PIXEL_HUE = millis();
//     else PIXEL_HUE = 0;
//     displayTemp( TEMP_HUMI );
//     delay(100);

//   }

//   TEMPO = millis();
//   LUX = luxRead();
//   limpaPixels();
//   // if( luxRead() ) PIXEL_HUE = millis();
//   // else PIXEL_HUE = 0;

//   while(millis() - TEMPO <= 5000){
    
//     MQTT.loop();
//     if( LUX ) PIXEL_HUE = millis();
//     else PIXEL_HUE = 0;
//     displayHumi( TEMP_HUMI );
//     delay(100);

//   }

//   TIME = getNtp();
//   TEMP_HUMI = getAHT10();

//   //if(WiFi.status() != WL_CONNECTED) wifiConnect();
//   if(!MQTT.connected()) mqttConnect();
//   else mqttSend(true);

//   ESP.wdtFeed();

// }
// //end loop