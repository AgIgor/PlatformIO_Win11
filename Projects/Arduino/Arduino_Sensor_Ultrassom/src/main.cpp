#include <Arduino.h>
//Digital input pin for 5v pulses
int inputPin = 13; //Arduino Due digital input pin
unsigned int packet = 0;  //32bit data packet
byte sensorValue = 0;     //distance in cm for a single sensor
byte sensorAddress = 0;   //Address of a sensor that is currently being processed

unsigned long pulseDur = 0; //Measure pulse length

void setup() {
  // initialize digital input pin
  pinMode(inputPin, INPUT);

  //initialize serial port for debugging
  Serial.begin(9600);
}
long msDly;
void loop() {
  //read input pin for a start pulse

  pulseDur = pulseIn(inputPin, HIGH, 20000);

  if(pulseDur > 1000 && pulseDur < 1200)
  {
    //Debug output to serial
    //Serial.println("Packet Start Pulse");  

    sensorAddress = 0;
    sensorValue = 0;
    packet = 0;

    for(int i = 10; i >= 0; i-- ){
      //Start reading data bytes
      pulseDur = pulseIn(inputPin, HIGH, 3000); //read data bits, timeout @ 3000us

      if(pulseDur == 0) break;                   // Timeout occured
      else if(pulseDur > 200 && pulseDur < 300) bitSet(packet, i);  //set only 1s, not interested in zeroes
      else bitClear(packet, i);
    }

    sensorAddress = (byte)((packet >> 8) & B00001011);
    sensorValue = (byte)(packet);

    Serial.print("Address: ");
    Serial.print(sensorAddress);
    Serial.print(" value: ");
    Serial.println(sensorValue);


  }


  // if(millis() - msDly > 10){
  //   msDly = millis();

  //   Serial.print("Address: ");
  //   Serial.print(sensorAddress);
  //   Serial.print(" value: ");
  //   Serial.println(sensorValue);

  // }
}