#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_AHTX0.h>
#include <Wire.h>

const char *ssid     = "VIVOFIBRA-9501";
const char *password = "rgw7ucm3GT";

const long utcOffsetInSeconds =  -10800;
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds,60000);

Adafruit_AHTX0 aht;

void getNTP(){
  static uint8_t Minuto;

  timeClient.update();
  Minuto = (timeClient.getMinutes());
  Serial.println(timeClient.getFormattedTime());   
  delay(10);
}//end get NTP

void getAHT10(){
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  delay(1);
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
}//end get AHT

void setup() {
  Serial.begin(115200);
  Wire.pins(0, 2);
  Wire.begin(0, 2);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("Ok");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

}//end setup

void loop() {
  // getAHT10();

  static bool t;
  if((millis()/1000)%2){
    if(t){
      t = false;
      getNTP();
    }
  }else{
    t = true;
  }

  delay(10);
}//end loop
