#include <Arduino.h>
#include <PID_v1.h>

#define PIN_OUTPUT 3

// Definições
const int pinNTC = A1;  // Pino analógico onde o NTC está conectado
const float resistor = 10000.0;  // Resistor de 10k ohms
const float beta = 3950;  // Constante beta do NTC
const float temperaturaAmbiente = 298.15;  // Temperatura ambiente em Kelvin (25°C)
const float resistenciaNTC25 = 100000;  // Resistência do NTC a 25°C

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double consKp=90, consKi=30, consKd=80;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

void setup() {

  Serial.begin(115200);
  pinMode(Output, OUTPUT);
  Setpoint = 250;
  myPID.SetMode(AUTOMATIC);

}

unsigned long tprinnt;

void loop() {
  // Leitura do valor analógico
  int leituraADC = analogRead(pinNTC);

  // Convertendo a leitura para tensão
  float tensaoNTC = leituraADC * (5.0 / 1023.0);

  // Calculando a resistência do NTC
  float resistenciaNTC = (resistor * (5.0 / tensaoNTC)) - resistor;

  // Usando a equação de Steinhart-Hart simplificada
  float temperaturaKelvin = (beta * temperaturaAmbiente) / (beta + (temperaturaAmbiente * log(resistenciaNTC / resistenciaNTC25)));

  // Convertendo Kelvin para Celsius
  float temperaturaCelsius = temperaturaKelvin - 273.15;

  delay(1);  // Espera 1 segundo entre as leituras

  Input = temperaturaCelsius;
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);

  if(millis() - tprinnt > 150){
    tprinnt = millis();
    Serial.print(temperaturaCelsius);
    Serial.print(" ");
    Serial.print(Output);
    Serial.println();
  }
}
