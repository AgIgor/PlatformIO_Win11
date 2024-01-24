#include <Arduino.h>
#include <Wire.h>

struct Data
{
  int steering;
  int throttle;
  int motor;
  int servo;
};

Data myData;

/* 
String toHex(String data){

  String stringHexadecimal = "";

  for (int i = 0; i < data.length(); i++) {
    // Obtém o valor ASCII do caractere na posição 'i'
    int valorAscii = data.charAt(i);
    
    // Converte o valor ASCII para hexadecimal
    String valorHex = String(valorAscii, HEX);
    
    // Adiciona um 0 à esquerda se o valor hexadecimal tiver apenas um dígito
    if (valorHex.length() == 1) {
      valorHex = "0" + valorHex;
    }
    
    // Concatena o valor hexadecimal à string final
    stringHexadecimal += valorHex;
  }
  
  // Serial.println("String original: " + data);
  // Serial.println("String em hexadecimal: " + stringHexadecimal);
  return stringHexadecimal;

}

String toString(String data){
  String stringConvertida = "";
  // Garante que o comprimento da string hexadecimal é par
  if (data.length() % 2 != 0) {
    data = "0" + data; // Adiciona um zero à esquerda se for ímpar
  }
  
  // Converte pares de caracteres hexadecimais de volta para caracteres ASCII
  for (int i = 0; i < data.length(); i += 2) {
    String parHex = data.substring(i, i + 2); // Obtém um par de caracteres hexadecimais
    int valorAscii = strtol(parHex.c_str(), NULL, 16); // Converte o par para um valor ASCII
    
    // Adiciona o caractere correspondente à string convertida
    stringConvertida += (char)valorAscii;
  }
  
  // Serial.println("Valor hexadecimal: " + data);
  // Serial.println("String convertida: " + stringConvertida);
  return stringConvertida;

}
 */

// void receiveEvent(int howMany) {
//  while (Wire.available()) {
//     Wire.readBytes((byte*)&myData, sizeof(myData));
//     Serial.print( myData.steering);
//     Serial.print( " " );
//     Serial.print( myData.throttle);
//   }
//   Serial.println();
// }

// void requestEvent() {
//  Wire.write((byte *)&myData, sizeof myData);  /*send string on request */
// }

void sendWire(int data){
  Wire.beginTransmission(4);
  Wire.write(data);
  Wire.endTransmission();
}

void receiveEvent(size_t howMany) {

  (void)howMany;
  while (1 < Wire.available()) {  // loop through all but the last
    char c = Wire.read();         // receive byte as a character
    Serial.print(c);              // print the character
  }
  int x = Wire.read();  // receive byte as an integer
  Serial.println(x);    // print the integer
}

void setup() {
  Serial.begin(115200);
  Wire.begin(0,2);
  Wire.onReceive(receiveEvent);
  // Wire.onRequest(requestEvent);
}

long int dly;
int val = 0;
void loop() {
  if(millis() - dly >= 1000){
    dly = millis();
    Serial.println("ok");
    val++;
    sendWire(val);

    // Wire.beginTransmission(8); // transmit to device #8
    // Wire.write((byte *)&myData, sizeof myData);              // sends one byte
    // Wire.endTransmission();    // stop transmitting

    //  Wire.requestFrom(8, sizeof(myData));
    //  while (Wire.available()) {
    //     Wire.readBytes((byte*)&myData, sizeof(myData));
    //     Serial.print( myData.led1);
    //   }
    //   Serial.println();

  }
}

