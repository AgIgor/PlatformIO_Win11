#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

long Resistance;
double Temp;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int RawADC = analogRead(A1);
  Resistance=((10240000/RawADC) - 10000);
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;

  Serial.print(Temp);
  Serial.println("*C");
  delay(500);

}