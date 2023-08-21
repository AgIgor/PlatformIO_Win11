#include <Arduino.h>
#include <PicoGamepad.h>

PicoGamepad gamepad;

#define Bot 2
#define PotX 26
#define PotY 27

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PotX, INPUT);
  pinMode(PotY, INPUT);
  pinMode(Bot, INPUT_PULLUP);
}

void loop() {
  int valX = map(analogRead(PotX), 0, 1023, -32767, 32767);
  //gamepad.SetX(valX);

  int valY = map(analogRead(PotY), 0, 1023, -32767, 32767);
  //gamepad.SetY(valY);
  
  // gamepad.SetZ(valX);
  //  gamepad.SetRx(val);
  //  gamepad.SetRy(val);
  //  gamepad.SetRz(val);
  // gamepad.SetThrottle(valX);
  // gamepad.SetS0(valY);
  //  gamepad.SetS1(val);


  gamepad.SetButton(0, !digitalRead(Bot));

  // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER 
  // gamepad.SetHat(0, 8);

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  delay(100);
}