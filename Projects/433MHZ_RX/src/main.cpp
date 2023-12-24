#include <Arduino.h>


const byte pinRF = 7;  // Pin where RF Module is connected. If necessary, change this for your project

int lambda;      // on pulse clock width (if fosc = 2KHz than lambda = 500 us)

struct rfControl        //Struct for RF Remote Controls
{
   unsigned long addr;  //ADDRESS CODE
   boolean btn1;        //BUTTON 1
   boolean btn2;        //BUTTON 2
   boolean btn3;        //BUTTON 3
   boolean btn4;        //BUTTON 4
};

boolean ACT_HT6P20B_RX(struct rfControl &_rfControl){ 
  
  static boolean startbit;      //checks if start bit was identified
  static int counter;           //received bits counter: 22 of Address + 2 of Data + 4 of EndCode (Anti-Code)
  static unsigned long buffer;  //buffer for received data storage
  
  int dur0, dur1;  // pulses durations (auxiliary)
  
  if (!startbit)
  {// Check the PILOT CODE until START BIT;
    dur0 = pulseIn(pinRF, LOW);  //Check how long DOUT was "0" (ZERO) (refers to PILOT CODE)
        
    //If time at "0" is between 9200 us (23 cycles of 400us) and 13800 us (23 cycles of 600 us).
    if((dur0 > 9200) && (dur0 < 13800) && !startbit)
    {    
      //calculate wave length - lambda
      lambda = dur0 / 23;
      
      //Reset variables
      dur0 = 0;
      buffer = 0;
      counter = 0;
      
      startbit = true;
    }
  }

  //If Start Bit is OK, then starts measure os how long the signal is level "1" and check is value is into acceptable range.
  if (startbit && counter < 28)
  {
    ++counter;
    
    dur1 = pulseIn(pinRF, HIGH);
    
    if((dur1 > 0.5 * lambda) && (dur1 < (1.5 * lambda)))  //If pulse width at "1" is between "0.5 and 1.5 lambda", means that pulse is only one lambda, so the data é "1".
    {
      buffer = (buffer << 1) + 1;   // add "1" on data buffer
    }
    else if((dur1 > 1.5 * lambda) && (dur1 < (2.5 * lambda)))  //If pulse width at "1" is between "1.5 and 2.5 lambda", means that pulse is two lambdas, so the data é "0".
    {
      buffer = (buffer << 1);       // add "0" on data buffer
    }
    else
    {
      //Reset the loop
      startbit = false;
    }
  }
  
  //Check if all 28 bits were received (22 of Address + 2 of Data + 4 of Anti-Code)
  if (counter==28) 
  { 
    // Check if Anti-Code is OK (last 4 bits of buffer equal "0101")
    if ((bitRead(buffer, 0) == 1) && (bitRead(buffer, 1) == 0) && (bitRead(buffer, 2) == 1) && (bitRead(buffer, 3) == 0))
    {     
      counter = 0;
      startbit = false;
      
      //Get ADDRESS CODE from Buffer
      _rfControl.addr = buffer >> 6;
      
      //Get Buttons from Buffer
       _rfControl.btn1 = bitRead(buffer,4);
       _rfControl.btn2 = bitRead(buffer,5);
       _rfControl.btn3 = bitRead(buffer,6);
       _rfControl.btn4 = bitRead(buffer,7);

       Serial.print("HEX: ");
       Serial.print(buffer, HEX);
       Serial.print(" DEC: ");
       Serial.print(buffer, DEC);
       Serial.print(" BIN: ");
       Serial.print(buffer, BIN);

       Serial.println();
 
      //Serial.print("Address: "); Serial.println(_rfControl.addr, HEX);
      //Serial.print("Button1: "); Serial.println(_rfControl.btn1, BIN);
      //Serial.print("Button2: "); Serial.println(_rfControl.btn2, BIN);
      //Serial.println();
      
      //If a valid data is received, return OK
      return true;
    }
    else
    {
      //Reset the loop
      startbit = false;
    }
  }
  
  //If none valid data is received, return NULL and FALSE values 
  _rfControl.addr = NULL;
  _rfControl.btn1 = NULL;
  _rfControl.btn2 = NULL; 
  _rfControl.btn3 = NULL;
  _rfControl.btn4 = NULL; 
  
  return false;
}

void setup(){    
  pinMode(pinRF, INPUT);
  pinMode(13, OUTPUT);
  
  Serial.begin(115200);
}

void loop(){

  digitalWrite(13, digitalRead(pinRF));  //blink de onboard LED when receive something
  
  struct rfControl rfControl_1;    //Set variable rfControl_1 as rfControl type
  
  if(ACT_HT6P20B_RX(rfControl_1))
  {
    //If a valid data is received, print ADDRESS CODE and Buttons values    
    // Serial.print("Address: "); Serial.println(rfControl_1.addr, HEX);
    // Serial.print("Button1: "); Serial.println(rfControl_1.btn1, BIN);
    // Serial.print("Button2: "); Serial.println(rfControl_1.btn2, BIN);
    // Serial.print("Button3: "); Serial.println(rfControl_1.btn3, BIN);
    // Serial.print("Button4: "); Serial.println(rfControl_1.btn4, BIN);
    // Serial.println();
  }
}




/* #include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

static const char* bin2tristate(const char* bin);
static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength);

void output(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {

  const char* b = dec2binWzerofill(decimal, length);
  Serial.print("Decimal: ");
  Serial.print(decimal);
  Serial.print(" (");
  Serial.print( length );
  Serial.print("Bit) Binary: ");
  Serial.print( b );
  Serial.print(" Tri-State: ");
  Serial.print( bin2tristate( b) );
  Serial.print(" PulseLength: ");
  Serial.print(delay);
  Serial.print(" microseconds");
  Serial.print(" Protocol: ");
  Serial.println(protocol);
  
  Serial.print("Raw data: ");
  for (unsigned int i=0; i<= length*2; i++) {
    Serial.print(raw[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.println();
}

static const char* bin2tristate(const char* bin) {
  static char returnValue[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos]!='\0' && bin[pos+1]!='\0') {
    if (bin[pos]=='0' && bin[pos+1]=='0') {
      returnValue[pos2] = '0';
    } else if (bin[pos]=='1' && bin[pos+1]=='1') {
      returnValue[pos2] = '1';
    } else if (bin[pos]=='0' && bin[pos+1]=='1') {
      returnValue[pos2] = 'F';
    } else {
      return "not applicable";
    }
    pos = pos+2;
    pos2++;
  }
  returnValue[pos2] = '\0';
  return returnValue;
}

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength) {
  static char bin[64]; 
  unsigned int i=0;

  while (Dec > 0) {
    bin[32+i++] = ((Dec & 1) > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j< bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    } else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';
  
  return bin;
}

void setup() {
  Serial.begin(115200);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() { 
  if (mySwitch.available()) {
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
}
*/