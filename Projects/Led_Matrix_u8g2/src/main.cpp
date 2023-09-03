#include <Arduino.h>
#include <U8g2lib.h>

U8G2_MAX7219_32X8_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 11, /* data=*/ 12, /* cs=*/ 10, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);

char time_string[10]; // string to hold the current time to be displayed

void setup(void) {

  pinMode(4, OUTPUT); // we are using pin 4 to power the real time clock module, 
  digitalWrite(4, HIGH); // since the +5V pin is already used for the display
  
  u8g2.begin(); // begin function is required for u8g2 library
  u8g2.setContrast(150); // set display contrast 0-255

}

void loop(void) {

  if((millis()/1000)%2){
    sprintf(time_string, "%d:%02d", 17, millis()/1000);
  }
  else{
    sprintf(time_string, "%d %02d", 17, millis()/1000);
  }

  u8g2.setFont(u8g2_font_t0_11b_tn);
  // u8g2.setFont(u8g2_font_6x10_tn );
  // u8g2.setFont(u8g2_font_t0_12b_me);

  u8g2.clearBuffer(); // clear the internal u8g2 memory
  u8g2.drawStr(2, 8, time_string);  // draw the time string to the display
  u8g2.sendBuffer(); // transfer internal memory to the display
  delay(1000); // wait one second

}