#include <Arduino.h>

#define botOk     A0
#define botLeft   A1
#define botRight  A2

byte bots[] = {botOk, botLeft, botRight};


void setup() {
  Serial.begin(115200);

  for(byte i=0;i<sizeof(bots);i++){
    pinMode(bots[i], INPUT_PULLUP);
    Serial.println(bots[i]);
  }
}

// char buffer[40];
int val;

bool leftFlag, okFlag, rightFlag;

void loop() {

  for(byte i=0;i<sizeof(bots);i++){
    bool botFlag = !digitalRead(bots[i]);

    // sprintf(buffer, "Bot: %d Index: %d", botFlag, bots[i]);
    // Serial.println(buffer);
    
    if(botFlag and bots[i] == botOk){
     okFlag = true;

     if((millis()/1000)%10 == 3){
      Serial.println("5seg");
     }

    }
    else{
      if(!botFlag and bots[i] == botOk and okFlag){
        Serial.println("Ok");
        okFlag = false;
      }
    }

    


    if(botFlag and bots[i] == botLeft){
      Serial.println("Left");
      // if(i == 0){
      // }
    }
    if(botFlag and bots[i] == botRight){
      Serial.println("Right");
      // if(i == 0){
      // }
    }

    delay(20);
  }
  
}
