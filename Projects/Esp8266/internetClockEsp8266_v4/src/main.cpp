#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

const char *ssid     = "VIVOFIBRA-9501";
const char *password = "rgw7ucm3GT";

#define brilhoMax 230
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

                            bool Trigger, Lux;

int newMinuto;  
int modeDisplay;
int IntervaloC, IntervaloT, IntervaloH;


void getNTP();
void piscaPonto();
void getAHT10();
void wifiConn();
bool luxRead();
void piscaPonto();
void display();
void limpaPixels();
void displayTemp();
void nextRainbowColor();

byte r = 255;
byte g = 0;
byte b = 0;
void nextRainbowColor() {
  if (r > 0 && b == 0) {
    r--;
    g++;
  }
  if (g > 0 && r == 0) {
    g--;
    b++;
  }
  if (b > 0 && g == 0) {
    r++;
    b--;
  }
}
//end nextRainbowColor 

void displayTemp(){
    for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[10][ID]), pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS grau
    pixels.setPixelColor((displayConfig[unidadeT][ID]+7), pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[dezenaT][ID]+15), pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    pixels.show();
  }  
}
//end display temp

void display(){
  for (int ID = 0; ID < 7; ID++){
    pixels.setPixelColor((displayConfig[unidadeM][ID]), pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Minuto
    pixels.setPixelColor((displayConfig[dezenaM][ID]+7), pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
    pixels.setPixelColor((displayConfig[unidadeH][ID]+15), pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
    if(dezenaH > 0){
      pixels.setPixelColor((displayConfig[dezenaH][ID]+22), pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Hora
    }else{
      pixels.setPixelColor((displayConfig[dezenaH][ID]+22), pixels.Color(0, 0, 0)); //LEDS DEZENA DE Hora
    }
    pixels.show();
  }
}
//end display

void getNTP(){
  if((millis()/1000)%30){//atualiza hora por minuto

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

    }//if new minuto

  }//end millis 30seg
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
  IPAddress ip(192, 168, 15, 7);
  IPAddress gateway(192, 168, 15, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(8, 8, 8, 8);
  WiFi.config(ip, gateway, subnet, dns);
  WiFi.setHostname("InternetClock");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);//
  while (WiFi.status() != WL_CONNECTED) {
    pixels.clear();
    delay(20);

    byte loadingWifi[]={0,1,8,16,17,21,20,12,5,4,0};
    luxRead();

    for(byte i=sizeof(loadingWifi); i>0;i--){
      pixels.setPixelColor(loadingWifi[i], pixels.Color(255, 0, 255));
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

  for(byte i=0;i<5;i++){
    lux = lightMeter.readLightLevel();
    delay(5);
  }

  if(lux >= luxMax){
    pixels.setBrightness(brilhoMax);
    lux_flag = true;
  }//END IF LUX MAX

  if(lux <= luxMin){
    pixels.setBrightness(brilhoMin);
    lux_flag = false;
    r=255;
    g=0;
    b=0;
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
    pixels.setPixelColor(14, pixels.Color(r, g, b));//pixels.gamma32(pixels.ColorHSV(pixelHue)));
    pixels.show();
  }else{
    pixels.setPixelColor(14, pixels.Color(0, 0, 0));
    pixels.show();
  }
}
//end pisca pontos

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

void setup() {
  Wire.pins(0, 2);
  Wire.begin(0, 2);
  pixels.begin();
  pixels.setBrightness(200);
  pixels.clear();
  delay(100);

  if(! aht.begin()) {
    delay(100);
    setup();
  }

  if(! lightMeter.begin()) {
    delay(100);
    setup();
  }

  delay(100);
  wifiConn();//
  delay(50);
  timeClient.begin();
  getAHT10();
  getNTP();
}
//end setup

void loop() {

  while(modeDisplay == 0){//display clock
    // if((millis()/1000)%60){//wifi check
    //   if(WiFi.status() != WL_CONNECTED) wifiConn();
    // }
    if((millis()/1000)%2){//second check
      if(Trigger){
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
        // getNTP();
        getAHT10();
      }
    }else Trigger = true;

    getNTP();

    if(Lux) nextRainbowColor();//pixelHue = millis();
    // else pixelHue = 0;
    
    piscaPonto();//
    display();
    delay(100);

  }//mode display 0

  while(modeDisplay == 1){//display temp
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

    if(Lux) nextRainbowColor();//pixelHue = millis();
    // else pixelHue = 0;
    displayTemp();
    delay(100);

  }//mode display 1

  delay(100);
}
//end loop
