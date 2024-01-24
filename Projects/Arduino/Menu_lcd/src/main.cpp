#include <Arduino.h>

#define up_pin 2
#define down_pin 3
#define left_pin 4
#define right_pin 5

bool key_lock = false;

int val;

void setup() {
  for(int i=2;i<5;i++)pinMode(i, INPUT_PULLUP);
  Serial.begin(115200);
}

int key_code(int button, bool btn_std){
  switch (button)
  {
    case 1:
      val++;
    break;
    case 2:
      val--;
    break;

  }
  return val;
}

void loop() {
  bool up = !digitalRead(up_pin);
  bool down = !digitalRead(down_pin);

  if(!key_lock){
    if(up) {
      Serial.println(key_code(1, up));
    }
    
    if(down) {
      Serial.println(key_code(2, down));
    }
  }

  if(up || down) key_lock = true;
  else key_lock = false;


  delay(100);
}