#include <Arduino.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

#define LED_BUILTIN 25

USBKeyboard Keyboard;

byte Keys_pins[] = {2,3,4,5};

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  for(byte i = 0;i<sizeof(Keys_pins);i++){
    pinMode(Keys_pins[i], INPUT_PULLUP);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  };
  
  
  
}
int int_key=32;

void loop() {
  delay(100);
  // Keyboard.printf("Hello world\n\r");
  
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    int_key = input.toInt();
    Serial.println(int_key);
  }
  
  if(!digitalRead(Keys_pins[0])){
    // for (byte i = 48; i <= 57; i++)
    // {
    //   Keyboard.key_code(i);
    //   delay(200);
    //   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    // }
    //Keyboard.key_code('0');
    Keyboard.key_code(int_key);
    delay(200);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Serial.println(int_key);
    
  }
}