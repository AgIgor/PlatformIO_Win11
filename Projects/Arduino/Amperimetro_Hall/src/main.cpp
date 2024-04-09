#include <Arduino.h>
#define hall_pin A1
#define leituras 100

float Vzero = 2.59;//56;
float K = 0.01;
float B = 0.10;
float Vbase = 4.96;
float Vin = 0;
float I = 0;

void setup() {
  Serial.begin(115200);
  pinMode(hall_pin, INPUT);
}

long delayPrint;
void loop() {
  float soma = 0;
  float media = 0;

  for(int x = 0; x < leituras; x ++){
    Vin = analogRead(hall_pin);
    Vin = (Vin * Vbase) / 1023;
    I = (Vin - Vzero)/(K*B);
    if(I<0)I=0;
    I = I * 0.01;
    soma = soma + I;
  }
  media = soma/leituras;
  delay(1);

  if(millis() - delayPrint > 200){
    delayPrint = millis();
    Serial.print("Vin = ");
    Serial.print(Vin);
    Serial.print(" I = ");
    Serial.print(media);
    Serial.print(" HALL = ");
    Serial.println(analogRead(hall_pin));
  }
}
