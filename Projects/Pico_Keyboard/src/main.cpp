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
    delay(400);
    Keyboard.key_code_raw(int_key);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Serial.println(int_key);
    
  }
}



// // ---------------------------------
// // Key definitions
// #define BUTTON_KEY1 KEY_F13
// #define BUTTON_KEY2 KEY_F14
// #define BUTTON_KEY3 KEY_F15
// #define BUTTON_KEY4 KEY_F16
// #define BUTTON_KEY5 KEY_F17
// #define BUTTON_KEY6 KEY_F18
// #define BUTTON_KEY7 KEY_F19
// #define BUTTON_KEY8 KEY_F20

// // Pin definitions
// #define BUTTON_PIN1 2
// #define BUTTON_PIN2 3
// #define BUTTON_PIN3 4
// #define BUTTON_PIN4 5
// #define BUTTON_PIN5 6
// #define BUTTON_PIN6 7
// #define BUTTON_PIN7 8
// #define BUTTON_PIN8 9
// // ---------------------------------

// #include "Keyboard.h"

// // Button helper class for handling press/release and debouncing
// class button {
//   public:
//   const char key;
//   const uint8_t pin;

//   button(uint8_t k, uint8_t p) : key(k), pin(p){}

//   void press(boolean state){
//     if(state == pressed || (millis() - lastPressed  <= debounceTime)){
//       return; // Nothing to see here, folks
//     }

//     lastPressed = millis();

//     state ? Keyboard.press(key) : Keyboard.release(key);    
//     pressed = state;
//   }

//   void update(){
//     press(!digitalRead(pin));
//   }

//   private:
//   const unsigned long debounceTime = 30;
//   unsigned long lastPressed = 0;
//   boolean pressed = 0;
// } ;

// // Button objects, organized in array
// button buttons[] = {
//   {BUTTON_KEY1, BUTTON_PIN1},
//   {BUTTON_KEY2, BUTTON_PIN2},
//   {BUTTON_KEY3, BUTTON_PIN3},
//   {BUTTON_KEY4, BUTTON_PIN4},
//   {BUTTON_KEY5, BUTTON_PIN5},
//   {BUTTON_KEY6, BUTTON_PIN6},
//   {BUTTON_KEY7, BUTTON_PIN7},
//   {BUTTON_KEY8, BUTTON_PIN8},
// };

// const uint8_t NumButtons = sizeof(buttons) / sizeof(button);
// const uint8_t ledPin = 17;

// void setup() { 
//   // Safety check. Ground pin #1 (RX) to cancel keyboard inputs.
//   pinMode(1, INPUT_PULLUP);
//   if(!digitalRead(1)){
//     failsafe();
//   }

//   // Set LEDs Off. Active low.
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, HIGH);
//   TXLED0;

//   for(int i = 0; i < NumButtons; i++){
//     pinMode(buttons[i].pin, INPUT_PULLUP);
//   }
// }

// void loop() {
//   for(int i = 0; i < NumButtons; i++){
//     buttons[i].update();
//   }
// }

// void failsafe(){
//   for(;;){} // Just going to hang out here for awhile :D
// }