#include <Arduino.h>


void setup() {
  pinMode(13,OUTPUT);
}

void loop() {

  for(int i=0;i<4;i++){
    digitalWrite(13,!digitalRead(13));
    delay(50);
  }
  //delay(100);
  digitalWrite(13,LOW);
  delay(1000);
}
