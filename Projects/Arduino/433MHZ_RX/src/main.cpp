#include <Arduino.h>

const byte pinRF = 2;  // Pin where RF Module is connected. If necessary, change this for your project

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

    //Serial.println(dur0);////////////
        
    //If time at "0" is between 9200 us (23 cycles of 400us) and 13800 us (23 cycles of 600 us).
    if((dur0 > 9200) && (dur0 < 13800) && !startbit)//9200 13800
    {    
      //calculate wave length - lambda
      lambda = dur0 / 23;

      // Serial.println(lambda);//////////

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

// unsigned long pulseDur = 0;
// unsigned long pulseHigh = 0;
// unsigned long pulseLow = 0;
// int val;

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

  // pulseDur = pulseIn(pinRF, HIGH, 11000);

  // if(pulseDur > 431 && pulseDur < 500){
  //   val++;
  //   if(val >= 84){
  //     Serial.println(val);
  //     val = 0;
  //   }
  // }


  // Serial.println(digitalPinToBitMask(pinRF));
  //delay(1);
}




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
  pinRF = 13;        //If necessary, change this for you project
  pinMode(pinRF, INPUT);
  pinMode(2, OUTPUT);
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

const int pinoSinal = 13; // Pino onde o sinal binário está conectado
long duration;
long ontime;
long offtime;
long period;
long inicio, final;





void setup() {
  pinMode(pinoSinal, INPUT); // Define o pino do sinal como entrada
  Serial.begin(115200); // Inicializa a comunicação serial para depuração
}

void loop() {
  ontime = pulseIn(pinoSinal, HIGH);
  offtime = pulseIn(pinoSinal,LOW);
  period = ontime+offtime;

  if(offtime < 30){
    Serial.print(offtime);
    Serial.print(" ");
    Serial.println(ontime);
  }

  // if( digitalRead(pinoSinal) == LOW){
    // inicio = millis();
  //}
  // else{
  //   final = millis();
    
  //   Serial.println(final - inicio);
  // }

  delay(50);
}
 */


/* 

#define pulse_ip 2

int ontime,offtime,duty;
float freq,period;
bool trigger;

long current, old, final;

// void down(){
//   current = micros();
//   //trigger = !trigger;
// }
// void up(){
//   final = old - current;
//   old = micros();
// }
void setup(){
  // pinMode(pulse_ip,INPUT);
  // pinMode(LED_BUILTIN,OUTPUT);
  // attachInterrupt(digitalPinToInterrupt(pulse_ip), down, FALLING);
  // attachInterrupt(digitalPinToInterrupt(pulse_ip), up, RISING);
  Serial.begin(115200);
}
void loop(){
  // ontime = pulseIn(pulse_ip,HIGH);
  // offtime = pulseIn(pulse_ip,LOW);
  // period = ontime - offtime;
  // freq = 1000000.0/period;
  // duty = (ontime/period)*100; 

  // if(period==0){ 
  // freq=0;
  // }
  
  //if(period < 700){
    // Serial.print("ontime: ");
    // Serial.print(ontime);
    // Serial.print(" offtime: ");
    Serial.print(final);
    Serial.println();

  //}

  //delay(10);
}
 */


/* 
#include <SoftwareSerial.h>

SoftwareSerial ss( 6,-1 );

char* controle1[] = {
                      "1001101011011110011110100111",
                      "1101101010011111010110110100",
                      "1101101101001101011011110011",
                      "1101001111101101010011111010",
                      "1101101001101101101001101011",
                      "0111100111101001111101101010",
                      "0111110101101101001101101101",
                      "0011010110111100111101001111"
};
char* controle4[] = {
                      "1010111011001110010111011001",
                      "1011011011011001110110011100",
                      "1001110110011001011011001001",
                      "1100101111001001100101110010",
                      "1101101101110110011011011111",
                      "0111011001110010011101100110",
                      "0101101100100111001011110010",
                      "1001011011011011101100110110"
};


char* controle2[]={
                    "1001111001101110111100111110",
                    "1101101001111110111110110100",
                    "1101100111011101111001111001",
                    "1011010011111101111101101001",
                    "1011001111001101110111100111",
                    "1101101101001111110111110110",
                    "1001101001111001101110111100",
                    "1111101101101001111110111110"
};
char* controle3[]={
                    "1001101011011110011110100111",
                    "1010011010100111110101101101",
                    "0011011011010011010110111100",
                    "1111010011110100110101001111",
                    "1010110110100110110110100110",
                    "1011011110011110100111101001",
                    "1010100111110101101101001101",
                    "1001010011010110111100111101"
};

bool findElemento(char* data, char* matriz[]){
  char* elementoProcurado = data;
  bool encontrado = false;
  int linhaEncontrada = -1;
  char* teste = "";


  for (int i = 0; i < 8; i++) {
    teste = matriz[i];
    if (teste == elementoProcurado) {
      encontrado = true;
      linhaEncontrada = i;
      break; // Se o elemento for encontrado, interrompe o loop
    }
    if (encontrado) {
      break; // Se o elemento for encontrado, interrompe o loop externo
    }
  }
  // Verificando se o elemento foi encontrado e exibindo o resultado na Serial
  if (encontrado) {
    Serial.print("Elemento encontrado na linha ");
    Serial.print(linhaEncontrada);
    Serial.println();
    return true;
  } else {
    //Serial.println("Elemento não encontrado na matriz.");
    return false;
  }
}

String decToHEx(char* data){
  char* binaryString = data;
  int length = strlen(binaryString);
  String result;

  // Certifique-se de que o comprimento da string é um múltiplo de 4
  int remainder = length % 4;
  if (remainder != 0) {
    length += 4 - remainder;
  }

  // Loop para converter os dígitos binários para hexadecimal
  for (int i = 0; i < length; i += 4) {
    int decimal = 0;
    for (int j = 0; j < 4; j++) {
      if (i + j < strlen(binaryString)) {
        decimal = decimal * 2 + (binaryString[i + j] - '0');
      } else {
        decimal *= 2; // Adiciona um zero se a string for menor que 4
      }
    }

    // Convertendo o valor decimal para hexadecimal e exibindo na Serial
    if (decimal < 10) {
      //Serial.print(decimal);
      result += decimal;
    } else {
      char hexChar = 'A' + (decimal - 10);
      //Serial.print(hexChar);
      result += hexChar;
    }
  }
  return result;
}

void setup() {
  Serial.begin(115200);
  ss.begin(2400);
  while (!Serial) {}
  Serial.println("Ok");

  // bool result;
  
  // for(int i=0; i<8;i++){
  //   result = findElemento(controle1[i], controle1);
  //   if(result){
  //     Serial.println(decToHEx(controle1[i]));
  //   }
  // }
  // Serial.println(result);

  // while(true){};

}//end setup

// byte dados[100];
// bool flag;
bool result;
int val;


void loop() {

  ss.listen();
  if (ss.available()) {
    // byte index = 0;

    while (ss.available()) {
      String package;
      do{
        String byteLido = String(ss.read(),BIN);
        // Serial.print(byteLido);
        package += byteLido;
        val++;

      } while (val <30);
      // Serial.println(package);

      for(int i=0;i<8;i++){
        int t = String(package).indexOf(controle4[i]);
        if(t > 0){
          Serial.println("ok");
        }
      }

      // Serial.println(package);
      //Serial.println("---------------END-------------");
      val = 0;
      package = "";

      
      
      // dados[index] = byteLido;
      // index++;

      // if(byteLido){

      //   //result = findElemento(byteLido.c_str(), controle1);
      //   // Serial.println(byteLido.length());
      //   // Serial.print(byteLido);
      //   // Serial.print(" ");
      //   flag = true;
      // }
      // else{
      //   if(flag){
      //     flag = false;
      //     Serial.println();
      //   }
      // }
    } 
  }
}

 */
 





/* #include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
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
} */