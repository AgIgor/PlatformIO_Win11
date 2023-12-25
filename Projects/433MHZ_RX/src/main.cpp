#include <Arduino.h>
/* 
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
  Serial.println("ok");
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

  */

/* 
#include <RCSwitch.h>

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
  mySwitch.setProtocol(1); 
}

void loop() { 
  if (mySwitch.available()) {
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
}
 
 */


/* 

byte pinRF;      // Pin where RF Module is connected

boolean startbit;
boolean dataok;
boolean anticodeok;

int counter;  //received bits counter: 22 of Address + 2 of Data + 4 of EndCode (Anti-Code)
int lambda;  // on pulse clock width (if fosc = 2KHz than lambda = 500 us)
int dur0, dur1;  // pulses durations (auxiliary)

unsigned long buffer=0;  //buffer for received data storage

void setup(){ 
  pinRF = 2;        //If necessary, change this for you project
  pinMode(pinRF, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  digitalWrite(13, digitalRead(pinRF)); //blink de onboard LED when receive something
  
  if (!startbit)
  {// Check the PILOT CODE until START BIT;
    dur0 = pulseIn(pinRF, LOW);  //Check how long DOUT was "0" (ZERO) (refers to PILOT CODE)
        
    //If time at "0" is between 9200 us (23 cycles of 400us) and 13800 us (23 cycles of 600 us).
    if((dur0 > 9200) && (dur0 < 13800) && !startbit)
    {    
      lambda = dur0 / 23;  //calculate wave length - lambda
      
      dur0 = 0;
      buffer = 0;
      counter = 0;
      
      dataok = false;
      startbit = true;
    }
  }

  // If Start Bit is OK, then starts measure os how long the signal is level "1" and check is value is into acceptable range.
  if (startbit && !dataok && counter < 28)
  {
    ++counter;
    
    dur1 = pulseIn(pinRF, HIGH);
    
    if((dur1 > 0.5 * lambda) && (dur1 < (1.5 * lambda)))  //If pulse width at "1" is between "0.5 and 1.5 lambda", means that pulse is only one lambda, so the data é "1".
    {
      buffer = (buffer << 1) + 1;      // add "1" on data buffer
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
      anticodeok = true;
    }
    else
    {
      //Reset the loop
      startbit = false;
    }
    
  if (anticodeok)
    {
      dataok = true;
      
      counter = 0;
      startbit = false;
      anticodeok = false;
      
      Serial.print("Data: ");
      Serial.println(buffer, BIN);
      
      unsigned long addr = buffer >> 6;
      
      Serial.print("-Address: ");
      Serial.println(addr, HEX);
      
      Serial.println("-Button1: " + (String)bitRead(buffer, 4));
      Serial.println("-Button2: " + (String)bitRead(buffer, 5));
      Serial.println("-----------------------------------");
      
      delay(100);
    }
  }
}

 */


/*

#define OOK_PIN 7
#define LED_PIN 13

#define MOD_PPM 1
#define MOD_PWM 0

char inChar;
String inputString        = "";         // a string to hold incoming data
unsigned int modulation   = 1;          // PWM = 0, PPM = 1
unsigned int repeats      = 5;          // signal repeats
unsigned int bits         = 36;         // amount of bits in a packet
unsigned int pd_len       = 2000;       // pulse/distance length (in us)
unsigned int zero_ca_len  = 250;        // length of 0 (in us)
unsigned int zero_ci_len  = 1250;       // length of 0 (in us)
unsigned int one_ca_len   = 1250;       // length of 1 (in us)
unsigned int one_ci_len   = 250;        // length of 0 (in us)
unsigned int pause_len    = 10000;      // pause length (in us), time between packets
unsigned int preamble     = 2500;       // preamble length (in us)
unsigned int invert       = 0;          // invert the bits before transmit
char packet_buf[256]      = {0};        // packet payload buffer
unsigned int pbuf_len     = 0;          // payload buffer length

unsigned int bit_pos      = 0;          // bit reader bit position
int carrier_mode          = 0;
void setup()
{
  // initialize digital pin 13 as an output.
  pinMode(OOK_PIN, OUTPUT);  // ook transmitter
  pinMode(LED_PIN, OUTPUT);  // led
  
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("OOK_gen 0.1");
  Serial.println("Copyright (C) 2015");  
  Serial.println("by Benjamin Larsson");
  Serial.print("> ");
}

char hextoInt(char hex_nibble) {
  switch (hex_nibble) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 0xA;
    case 'B': return 0xB;
    case 'C': return 0xC;
    case 'D': return 0xD;
    case 'E': return 0xE;
    case 'F': return 0xF;
    case 'a': return 0xA;
    case 'b': return 0xB;
    case 'c': return 0xC;
    case 'd': return 0xD;
    case 'e': return 0xE;
    case 'f': return 0xF;
    default: return 0;
  }
}

// sprintf bugs made me do this, the object code is smaller without sprintf also
char get_hex_char(char hchar){
  if (hchar>9)
    return hchar+'A'-10;
  else
    return hchar+'0';
}

void printhex(char hex_char){
  char tmp;
  tmp = get_hex_char(((hex_char>>4)&0x0F));
  Serial.print(tmp);
  tmp = get_hex_char(hex_char&0x0F);
  Serial.print(tmp);
  Serial.print(" ");
}

int get_bit() {
  int ret;
  int byte_pos     = bit_pos / 8;
  int byte_bit_pos = 7 - (bit_pos % 8);     // reverse indexing to send the bits msb
  bit_pos++;
  ret = (packet_buf[byte_pos] & (1<<byte_bit_pos)) ? 1 : 0;
  return ret^invert;
}

int transmit_signal() {
  int i,j;
  int bit;
  int pwm_bl;

  // send preamble - not implemented

  // support leds on Leonardo and Pro Micro
  if (LED_PIN == 13)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);

  // repeats
  for (j=0 ; j<repeats ; j++) {
    // reset bit reader
    bit_pos = 0;

    // send bits
    for (i=0 ; i<bits ; i++) {
      bit = get_bit();
      if ((modulation==MOD_PPM) || (modulation==MOD_PWM)) {
        digitalWrite(OOK_PIN, HIGH);
        if (bit) {
          delayMicroseconds(one_ca_len);
          digitalWrite(OOK_PIN, LOW);
          delayMicroseconds(one_ci_len);
        } else {
          delayMicroseconds(zero_ca_len);
          digitalWrite(OOK_PIN, LOW);
          delayMicroseconds(zero_ci_len);
        }
      } else {
        return -1; 
      }
    }
    
    // Send ending PPM pulse
    if (modulation == MOD_PPM) {
        digitalWrite(OOK_PIN, HIGH);
//        digitalWrite(LED_PIN, HIGH);
        delayMicroseconds(pd_len);
        digitalWrite(OOK_PIN, LOW);
//        digitalWrite(LED_PIN, LOW);    
    }
    // delay between packets
    delayMicroseconds(pause_len);
  }

  // support leds on Leonardo and Pro Micro
  if (LED_PIN == 13)
    digitalWrite(LED_PIN, LOW);
  else
    digitalWrite(LED_PIN, HIGH);

  return 0;
}

void loop()
{
  // read serial input
  if (Serial.available() > 0) {
    inChar = (char)Serial.read();
    inputString += inChar;

    // Serial echo
    Serial.print(inChar);


    // handle commands
    if (inChar=='\r') {

      Serial.print("\nCMD: ");
      Serial.println(inputString);

      switch((char)inputString[0]) {
        case 'm':
          if (inputString.length() == 2) {
            Serial.print("Modulation: ");
            if (modulation == MOD_PPM)
              Serial.println("PPM");
            else if (modulation == MOD_PWM)
              Serial.println("PWM");
            else
              Serial.println("Invalid state");            
          }
          if (inputString.length() > 3) {
            modulation = (char)inputString[2]-'0';   // the easy way
          }
          break;
        case 'i':
          if (inputString.length() == 2) {
            Serial.print("Invert: ");
            Serial.println(invert);
          }
          if (inputString.length() > 3) {
            invert = (char)inputString[2]-'0';   // the easy way
          }
          break;
        case 'r':
          if (inputString.length() == 2) {
            Serial.print("Repeats: ");
            Serial.println(repeats);
          }
          if (inputString.length() > 3) {
            repeats = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'b':
          if (inputString.length() == 2) {
            Serial.print("Bits: ");
            Serial.println(bits);
          }
          if (inputString.length() > 3) {
            bits = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'z':
          if (inputString.length() == 2) {
            Serial.print("Zero ca length: ");
            Serial.println(zero_ca_len);
          }
          if (inputString.length() > 3) {
            zero_ca_len = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'x':
          if (inputString.length() == 2) {
            Serial.print("Zero ci length: ");
            Serial.println(zero_ci_len);
          }
          if (inputString.length() > 3) {
            zero_ci_len = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'o':
          if (inputString.length() == 2) {
            Serial.print("One ca length: ");
            Serial.println(one_ca_len);
          }
          if (inputString.length() > 3) {
            one_ca_len = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'u':
          if (inputString.length() == 2) {
            Serial.print("One ci length: ");
            Serial.println(one_ci_len);
          }
          if (inputString.length() > 3) {
            one_ci_len = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;

        case 'd':
          if (inputString.length() == 2) {
            Serial.print("Pulse / Distance length(pd/z/o): ");
            Serial.println(pd_len);
          }
          if (inputString.length() > 3) {
            pd_len = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'e':
          if (inputString.length() == 2) {
            Serial.print("Pause length: ");
            Serial.println(pause_len);
          }
          if (inputString.length() > 3) {
            pause_len = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'a':
          if (inputString.length() == 2) {
            Serial.print("Preamble length: ");
            Serial.println(preamble);
          }
          if (inputString.length() > 3) {
            preamble = inputString.substring(2,inputString.length()).toInt();  // the hard way
          }
          break;
        case 'p':
          if (inputString.length() == 2) {
            Serial.print("Packet: ");
            Serial.println(pbuf_len);
            for (int i=0 ; i<pbuf_len ; i++){
              printhex(packet_buf[i]);
            }
            Serial.print("\n");
          }
          if (inputString.length() > 3) {
            for (int i=0 ; i<inputString.length()-3 ; i++){
              packet_buf[i]  = hextoInt((char)inputString[(i*2) + 2]) << 4;
              packet_buf[i] |= hextoInt((char)inputString[(i*2) + 3]);
            }
            // TODO clear the packet_buf buffer 
            pbuf_len = ((inputString.length()-3)+1)/2;  //round up
          }
          break;
        case 't':
            {
            int res = transmit_signal();
            if (!res)
              Serial.println("OK");
            else {
              Serial.print("FAIL: ");
              Serial.println(res);
            }
            }
          break;
        case 's':
          if (inputString.length() == 2) {
            Serial.print("Carrier mode: ");
            Serial.println(carrier_mode);
          }
          if (inputString.length() > 3) {
            carrier_mode = inputString[2]-'0';   // the easy way
            if (carrier_mode)
              digitalWrite(OOK_PIN, HIGH);
            else
              digitalWrite(OOK_PIN, LOW);
          }
          break;
        }
      // reset command line buffer
      inputString = "";
      Serial.print("> ");
    }
  }
}


*/
/* 

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  mySwitch.setProtocol(1);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );

    mySwitch.resetAvailable();
  }
}

 */

/* 
uint8_t uartBit;      // received
uint8_t prevBit = 1;  // previously received
uint32_t lastTime;    // remember when state change was detected

const uint8_t somePin = 7;  // gpio pin

void setup()
{
  Serial.begin(115200);  // use the highest baudrate supported by 3rd party terminal program
}

void loop()
{
  uartBit = digitalRead(somePin);
  if(uartBit != prevBit)
  {
    Serial.print(millis() - lastTime);
    Serial.print(" ");
    Serial.println(uartBit);
    prevBit = uartBit;
    lastTime = millis();
  }
}

 */







/*
This example outputs values from all PPM channels to Serial
in a format compatible with Arduino IDE Serial Plotter
*/

/* 
#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
byte interruptPin = 3;
byte channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);

void setup() {
    Serial.begin(115200);
}

void loop() {
    // Print latest valid values from all channels
    for (byte channel = 1; channel <= channelAmount; ++channel) {
        unsigned value = ppm.latestValidChannelValue(channel, 0);
        Serial.print(value);
        if(channel < channelAmount) Serial.print('\t');
    }
    Serial.println();
    delay(10);
}

 */


unsigned long int a,b,c;
int x[15],ch1[15],ch[7],i;
//specifing arrays and variables to store values 

void read_me()  {
  //this code reads value from RC reciever from PPM pin (Pin 2 or 3)
  //this code gives channel values from 0-1000 values 
  //    -: ABHILASH :-    //
  a=micros(); //store time value a when pin value falling
  c=a-b;      //calculating time inbetween two peaks
  b=a;        // 
  x[i]=c;     //storing 15 value in array
  i=i+1;
  if(i==15){
    for(int j=0;j<15;j++){
      ch1[j]=x[j];
    }
    i=0;
  }
}//copy store all values from temporary array another array after 15 reading  
void read_rc(){
  int i,j,k=0;
  for(k=14;k>-1;k--){
    if(ch1[k]>10000){
      j=k;
    }
  }  //detecting separation space 10000us in that another array                     
  for(i=1;i<=6;i++){
    ch[i]=(ch1[i+j]-1000);
  }
}     //assign 6 channel values after separation space

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), read_me, FALLING);
  // enabling interrupt at pin 2
}

void loop() {
  read_rc();

  Serial.print(ch[1]);Serial.print("\t");
  Serial.print(ch[2]);Serial.print("\t");
  Serial.print(ch[3]);Serial.print("\t");
  Serial.print(ch[4]);Serial.print("\t");
  Serial.print(ch[5]);Serial.print("\t");
  Serial.print(ch[6]);Serial.print("\n");

  delay(100);
}


