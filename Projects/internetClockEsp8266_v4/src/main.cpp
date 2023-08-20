#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

const char *ssid     = "VIVOFIBRA-9501";
const char *password = "rgw7ucm3GT";

#define brilhoMax 255
#define brilhoMin 5

#define luxMax 4
#define luxMin 2

#define delayClock 10//120
#define delayTemp 5//30
#define delayHumi 5//30

#include <NTPClient.h>
const long utcOffsetInSeconds =  -10800;
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds,60000);

#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels (24, 1, NEO_GRB + NEO_KHZ800);

#include <BH1750.h>
BH1750 lightMeter;

long pixelHue;
byte dezenaH ,unidadeH,dezenaM ,unidadeM;
byte dezenaT, unidadeT, dezenaHu, unidadeHu;
byte displayConfig[12][7]= {{0,0,1,2,4,5,6},  //Digito 0
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

void getNTP();
void piscaPonto();
void getAHT10();
void wifiConn();
bool luxRead();
void piscaPonto();
void display();
void limpaPixels();
void displayTemp();


void displayTemp(){
  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[10][ID]), pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS grau
    pixels.setPixelColor((displayConfig[unidadeT][ID]+7), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[dezenaT][ID]+15), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    pixels.show();
  }  
}
//end display temp

void display(){
  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[unidadeM][ID]), pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS UNIDADE DE Minuto
    pixels.setPixelColor((displayConfig[dezenaM][ID]+7), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[unidadeH][ID]+15), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    if(dezenaH > 0){
      pixels.setPixelColor((displayConfig[dezenaH][ID]+22), pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS DEZENA DE Hora
    }else{
      pixels.setPixelColor((displayConfig[dezenaH][ID]+22), pixels.Color(0, 0, 0)); //LEDS DEZENA DE Hora
    }
    pixels.show();
  }
}
//end display

int newMinuto;  
void getNTP(){
  timeClient.update();
  int Hora = (timeClient.getHours());
  int Minuto = (timeClient.getMinutes());
  delay(10);

  if(newMinuto != Minuto){
    newMinuto = Minuto;
    if(Hora >=13){Hora = Hora -=12;}
    dezenaH = Hora;
    unidadeH = dezenaH;
    dezenaH = dezenaH/10;
    unidadeH = unidadeH % 10;

    dezenaM = Minuto;
    unidadeM = dezenaM;
    dezenaM = dezenaM/10;
    unidadeM = unidadeM % 10;

    limpaPixels();
    delay(1);
    pixels.clear();
    //display(0);
  }//if new minuto
}
//end get NTP

void getAHT10(){
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  delay(1);

  byte Temp = temp.temperature;
  byte Humi = humidity.relative_humidity;
  if(Temp > 60) Temp = 60;
  if(Humi > 90) Humi = 90;

  dezenaT = Temp;
  unidadeT = dezenaT;
  dezenaT = dezenaT/10;
  unidadeT = unidadeT % 10;

  dezenaHu = Humi;
  unidadeHu = dezenaHu;
  dezenaHu = dezenaHu/10;
  unidadeHu = unidadeHu % 10;
}
//end get AHT

void wifiConn(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    pixels.clear();
    delay(300);

    for(byte i = 24; i>0;i--){
      pixels.setPixelColor(i, pixels.Color(255, 0, 255));
      pixels.show();
      delay(100);
    }
  }
  pixels.clear();
}
//end wifi

bool luxRead(){
  bool lux_flag;
  int lux;
  lux = lightMeter.readLightLevel();
  if(lux >= luxMax){
    pixels.setBrightness(brilhoMax);
    lux_flag = true;
  }//END IF LUX MAX

  if(lux <= luxMin){
    pixels.setBrightness(brilhoMin);
    lux_flag = false;
  }
  return lux_flag;

  // if(lux_flag){
  //   //pixelHue = millis();
  //   return true;
  // }else{
  //   //pixelHue = 0;
  //   return false;
  // }//END ELSE LUX FLAG

}
//end lux read

void piscaPonto(){
  if((millis()/1000)%2){
    pixels.setPixelColor(14, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    pixels.show();
  }else{
    pixels.setPixelColor(14, pixels.Color(0, 0, 0));
    pixels.show();
  }
}
//end pisca pontos

void limpaPixels(){
  for (byte i=24; i>0; i--){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    delay(30);
  }
}
//end limpa pixels

void setup() {
  Wire.pins(0, 2);
  Wire.begin(0, 2);
  pixels.begin();
  pixels.setBrightness(brilhoMax);
  pixels.clear();
  delay(100);

  wifiConn();//

  if(! aht.begin()) {
    delay(100);
    setup();
  }else{
    for(byte i=0; i<24;i++){
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels.show();
      delay(50);
    }
  }

  if(! lightMeter.begin()) {
    delay(100);
    setup();
  }else{
    for(byte i=0; i<24;i++){
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      pixels.show();
      delay(50);
    }
  }
  timeClient.begin();
  getAHT10();
  getNTP();
}
//end setup

bool Trigger, Lux;
int modeDisplay;
int IntervaloC, IntervaloT, IntervaloH;

void loop() {
  while(modeDisplay == 0){
    if((millis()/1000)%2){
      if(Trigger){
        if(WiFi.status() != WL_CONNECTED) wifiConn();
        Trigger = false;

        if(IntervaloC <= delayClock){
          IntervaloC++;
        }else{
          IntervaloC = 0;
          modeDisplay = 1;
          limpaPixels();
          delay(10);
          pixels.clear();
          break;
        }

        Lux = luxRead();
        getNTP();
        getAHT10();
      }
    }else Trigger = true;

    piscaPonto();//
    if(Lux) pixelHue = millis();
    else pixelHue = 0;
    display();
    delay(5);

  }//mode display 0

  while(modeDisplay == 1){
    if((millis()/1000)%2){
      if(Trigger){
        Trigger = false;

        if(IntervaloT <= delayTemp){
          IntervaloT++;
        }else{
          IntervaloT = 0;
          modeDisplay = 0;
          limpaPixels();
          delay(10);
          pixels.clear();
          break;
        }

        Lux = luxRead();
        //getNTP();
        getAHT10();
      }
    }else Trigger = true;

    if(Lux) pixelHue = millis();
    else pixelHue = 0;
    displayTemp();
    delay(5);

  }//mode display 1

  delay(5);
}
//end loop
