#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

const char *ssid     = "VIVOFIBRA-9501";
const char *password = "rgw7ucm3GT";

#define brilhoMax 255
#define brilhoMin 5

#define luxMax 6
#define luxMin 5

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

void getNTP(){
  timeClient.update();
  int Hora = (timeClient.getHours());
  int Minuto = (timeClient.getMinutes());
  static int newMinuto;  
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
  }
}
//end get NTP

void getAHT10(){
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  delay(1);
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
}
//end get AHT

void wifiConn(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    pixels.clear();
    delay(300);

    for(byte i = millis()/1000; i>0;i--){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();
      delay(100);
    }
  }
  pixels.clear();
}
//end wifi

void luxRead(){
  bool lux_flag;
  int lux;
  lux = lightMeter.readLightLevel();
  if(lux >= luxMax){
    pixels.setBrightness(brilhoMax);
    //pixelHue = millis();
    lux_flag = true;
  }//END IF LUX MAX

  if(lux <= luxMin){
    pixels.setBrightness(brilhoMin);
    //pixelHue = 0;
    lux_flag = false;
  }//END IF LUX MIN
  if(lux_flag){
    pixelHue = millis();
  }else{
    pixelHue = 0;
  }//END ELSE LUX FLAG

}
//end lux read

void display(){
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

void setup() {
  Serial.begin(115200);
  Wire.pins(0, 2);
  Wire.begin(0, 2);
  pixels.begin();
  pixels.setBrightness(brilhoMax);
  pixels.clear();
  delay(100);

  wifiConn();//

  if (! aht.begin()) {
    delay(100);
    setup();
  }

  if (! lightMeter.begin()) {
    delay(100);
    setup();
  }
  timeClient.begin();

  

}
//end setup

void loop() {
  static bool t;
  if((millis()/1000)%2){
    if(t){
      t = false;
      getNTP();
      getAHT10();
      luxRead();
    }
  }else{
    t = true;
  }

  delay(10);
}
//end loop
