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

#define BRILHO_MAX    230
#define BRILHO_MIN      2

#define LUX_MAX         3
#define LUX_MIN         2

#define DELAY_CLOCK    10
#define DELAY_TEMP     15
#define DELAY_HUMI     20

bool LIGHT;
byte* TIME;
byte* TEMP_HUMI;
byte RGB[3]={255,0,0};

const byte displayConfig[12][7]= {{0,0,1,2,4,5,6},  //Digito 0
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
                                  {0,0,0,0,0,3,6}}; //Umidade;


//==========* Funções *==========//

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
  }

  return lux_flag;

}
//end lux read

byte* getAHT10(){

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  delay(1);

  static byte digitos[4];
  float tempFloat = temp.temperature;
  float humiFloat = humidity.relative_humidity;

  byte tempByte = tempFloat;
  byte humiByte = humiFloat;
  
  digitos[0] = tempByte / 10;
  digitos[1] = tempByte % 10;
  digitos[2] = humiByte / 10;
  digitos[3] = humiByte % 10;

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

  JsonDocument doc;
  doc["temperature"] = serialized(String(tempFloat,1));
  doc["humidity"] = serialized(String(humiFloat,1));

  char saida[sizeof(doc)];
  serializeJson(doc, saida);
  MQTT.publish("/mqtt/internet_clock_v.4/sensor",saida, true, 0);
  delay(1);

  return digitos;

}
//end get AHT

void displayTemp( byte* digitos, byte* RGB ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[10][ID]), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS grau
    pixels.setPixelColor((displayConfig[digitos[0]][ID]+7), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+15), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    pixels.show();
  }

}
//end display temp

void displayHumi( byte* digitos, byte* RGB ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[11][ID]), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS grau
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+7), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[3]][ID]+15), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    pixels.show();
  }

}
//end display humi

void display( byte* digitos, byte* RGB ){

  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[digitos[0]][ID]), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Minuto
    pixels.setPixelColor((displayConfig[digitos[1]][ID]+7), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[digitos[2]][ID]+15), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    
    if(digitos[3] > 0){
      pixels.setPixelColor((displayConfig[digitos[3]][ID]+22), pixels.Color(RGB[0], RGB[1], RGB[2]));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Hora
    }else{
      pixels.setPixelColor((displayConfig[digitos[3]][ID]+22), pixels.Color(0, 0, 0)); //LEDS DEZENA DE Hora
    }
    pixels.show();
    delay(1);
  }
  
}
//end display

void mqttConnect(){

  MQTT.begin("mqtt.eclipseprojects.io", WIFI);
  delay(5);
  while (!MQTT.connect("internet_clock#v.4", "", "")) {
    delay(500);
  }
  MQTT.publish("/mqtt/internet_clock_v.4/sensors", "OK");
  //client.subscribe("/mqtt/internet_clock_v.4/config/#");

}
//end mqttConnect

byte* getNtp() {

  timeClient.update();
  static byte digitos[4];
  byte H = timeClient.getHours() % 12;
  byte M = timeClient.getMinutes();

  digitos[0] = H / 10;
  digitos[1] = H % 10;
  digitos[2] = M / 10;
  digitos[3] = M % 10;

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

byte val;
void delayInc(){
  static long int dly;
  if(millis() - dly > 1000){
    dly = millis();
    val++;
  }
}
//end delayInc

void setup(){

  timeClient.begin();
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

  LIGHT = luxRead();
  TIME = getNtp();
  TEMP_HUMI = getAHT10();

}
//end setup

void loop(){  

  while(val < 5){

    delayInc();
    RGB[0] = 127; //rgb(127,11,229)
    RGB[1] = 11;
    RGB[2] = 229;
    piscaPonto(RGB);
    display( TIME, RGB );
    delay(100);

  }
  limpaPixels();
  while(val < 10){

    delayInc();
    RGB[0] = 184; //rgb(184,105,55)
    RGB[1] = 105;
    RGB[2] = 55;
    displayTemp( TEMP_HUMI, RGB);
    delay(100);

  }
  limpaPixels();
  while(val < 15){
    
    delayInc();
    RGB[0] = 44;  //rgb(44,209,208)
    RGB[1] = 209;
    RGB[2] = 208;
    displayHumi( TEMP_HUMI, RGB);
    delay(100);
    
  }
  limpaPixels();
  val = 0;

  LIGHT = luxRead();
  TIME = getNtp();
  TEMP_HUMI = getAHT10();


  // unsigned long currentTime = millis();
  // if (currentTime - startTime < 2000) {

  //   piscaPonto(RGB);
  //   nextRainbowColor();
  //   display( TIME, RGB );

  //   currentTime = millis();
  //   delay(10);

  // }
  // limpaPixels();

  // startTime = millis(); // Reinicia o tempo inicial
  // while (currentTime - startTime < 2000) {
  //   // Código para o segundo while aqui
    
  //   currentTime = millis();
  // }
  // limpaPixels();

  // startTime = millis(); // Reinicia o tempo inicial
  // while (currentTime - startTime < 2000) {
  //   // Código para o terceiro while aqui
    
  //   currentTime = millis();
  // }
  // limpaPixels();

  // startTime = millis();

  //MQTT.loop();
  //if ( !MQTT.connected() ) mqttConnect();

  // LIGHT = luxRead();
  // TIME = getNtp();
  // TEMP_HUMI = getAHT10();

  // piscaPonto(RGB);
  // nextRainbowColor();
  // display( TIME, RGB );
  
  delay(100);
  //if(WiFi.status() == WL_CONNECTED) wifiConnect();

}
//end loop
