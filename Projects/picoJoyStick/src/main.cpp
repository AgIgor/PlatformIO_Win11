/*
  PicoGamepad

  Turn a Raspberry Pico 2040 into an HID gamepad

  Supports:
  128 Buttons
  8 Analog axes
  4 Hat switches
  
  created 28 June 2021
  by Jake Wilkinson (RealRobots)

  This example code is in the public domain.

  https://www.gitlab.com/realrobots/PicoGamepad
*/

#include <PicoGamepad.h>

#define pin_bot1 2
// #define pin_bot2
// #define pin_bot3
// #define pin_bot4
// #define pin_bot5

#define pin_pot1 26
#define pin_pot2 27
// #define pin_pot3
// #define pin_pot4


PicoGamepad gamepad;

// 16 bit integer for holding input values
int val1, val2;

void setup() {  
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);

  // X Potentiometer on pin 26
  pinMode(pin_pot1, INPUT);
  // Y Potentiometer on pin 27
  pinMode(pin_pot2, INPUT);

  // Button on pin 
  pinMode(pin_bot1, INPUT_PULLUP);
}

void loop() {

  val1 = analogRead(pin_pot1);
  val1 = map(val1, 0, 1023, -32767, 32767);
  // gamepad.SetX(val1);

  val2 = analogRead(pin_pot2);
  val2 = map(val2, 0, 1023, -32767, 32767);
  // gamepad.SetY(val2);

  gamepad.SetZ(val1);
  // gamepad.SetRx(val);
  // gamepad.SetRy(val);
  // gamepad.SetRz(val);
  gamepad.SetThrottle(val2);
  // gamepad.SetS0(val);
  // gamepad.SetS1(val);

  // Set button 0 of 128 by reading button on digital pin 28
  gamepad.SetButton(0, !digitalRead(pin_bot1));
  
  // for (byte i = 0; i < 32; i++){
  //   gamepad.SetButton(i, !digitalRead(pin_bot1));
  // }


  // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER 
  // gamepad.SetHat(0, 8);
  gamepad.send_update();
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  delay(100);
}