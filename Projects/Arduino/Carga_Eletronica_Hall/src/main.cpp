#include <Arduino.h>
#include <PWM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define encoderA 2
#define encoderB 3
#define encoderButton 4

Encoder myEncoder(encoderA, encoderB);

boolean buttonState = false;
boolean lastButtonState = false;
boolean fineAdjustMode = false;

byte encoderPassos = 4;
float modes[] = {0.01,0.05, 0.10, 1.00};

float corrente = 0.00;
int value, oldValue;
int contadorCliques = 1;

int32_t frequency = 10000; //frequency (in Hz)

#define hall_pin  A1
#define leituras  100
#define pinPWM    9

double newSetpoint;
bool err = false;

float Vzero = 2.42;//2.56
float K = 0.01;//
float B = 0.12;//0.11
float Vbase = 4.80;//4.88
float Vin = 0;
float I = 0;

float kp = 0.3; //5.5
float ki = 2.0; //5.2
float kd = 3.5; //5.1

double setpoint = 0.0;   // Valor de corrente desejado (em Ampères)
double maxSet = 2.5;

double output = 0.0;     // Valor de saída do controlador (em PWM)
double error = 0.0;      // Erro entre o setpoint e o input
double last_error = 0.0; // Último erro calculado
double integral = 0.0;   // Acumulador da integral do erro
double derivative = 0.0; // Derivada do erro

double output_min = 0.0;
double output_max = 255.0;

long delayMillis;
#define DELAYPRINT 250

class Botao {
  private:
    byte pino;
    bool estadoAnterior;
    unsigned long tempoAnterior;

  public:
    Botao(byte pino) {
      this->pino = pino;
      pinMode(pino, INPUT_PULLUP);
      estadoAnterior = false;
      tempoAnterior = 0;
    }

 void press( void (*press)(), void (*longPress)() ) {
    bool estadoBotao = !digitalRead(pino);
    unsigned long tempoAtual = millis();

    if (estadoBotao && !estadoAnterior && (tempoAtual - tempoAnterior) > 25) {
      tempoAnterior = tempoAtual;
      //Serial.println("Down");
      //press();
    }
    else if (!estadoBotao && estadoAnterior && (tempoAtual - tempoAnterior) > 25) {
      tempoAnterior = tempoAtual;
      //Serial.println("Up");
      press();
    }
    else if (estadoBotao ) {
      if(tempoAtual - tempoAnterior > 2000){
        tempoAnterior = tempoAtual;
        //Serial.println("5sec");
        longPress();
        return;
      }
    }
    estadoAnterior = estadoBotao;
  }
};

void setValor() {
  setpoint = corrente;
}
void rst(){
  setpoint = 0;
  corrente = 0;
  output = 0;
}

/* void getSerial(){
  if (Serial.available() > 0) { // Verifica se há dados disponíveis no monitor serial
    String input = Serial.readStringUntil('\n'); // Lê a string enviada pelo monitor serial
    input.trim(); // Remove espaços em branco do início e do fim da string
    int index = input.indexOf("=");
    if (input.startsWith("kp")) {
      kp = input.substring(index + 1).toFloat();
    }
    else if (input.startsWith("ki")) {
      ki = input.substring(index + 1).toFloat();
    }
    else if(input.startsWith("kd")){
      kd = input.substring(index + 1).toFloat();
    }
    else if(input.startsWith("set")){
      setpoint = input.substring(index + 1).toFloat();
    }    
  }//end if serial available
  delay(1);  
} */

void setup() {
  InitTimersSafe();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  pinMode(encoderButton, INPUT_PULLUP);

  bool success = SetPinFrequencySafe(pinPWM, frequency);
  if(!success)while(1){}

  Serial.begin(115200);
  pinMode(hall_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinPWM, OUTPUT);

  Vin = analogRead(hall_pin);
  lcd.clear();  
}

Botao Ok(encoderButton);
void loop() {
  float soma = 0;
  float media = 0;

  Ok.press(setValor, rst);

  value = myEncoder.read();
  if(oldValue != value){
    oldValue = value;
    value < 0 ? value = 0 : NULL;
    corrente = ((value/encoderPassos) * modes[contadorCliques] );
    delay(50);
  }
  
  for(int x = 0; x < leituras; x ++){
    Vin = analogRead(hall_pin);
    Vin = (Vin * Vbase) / 1023;
    I = (Vin - Vzero)/(K*B);
    if(I<0)I=0;
    I = I * 0.01;
    soma = soma + I;
  }

  media = soma/leituras;
  error = setpoint - media;
  integral = integral + error;
  
  if (integral > output_max / ki) {// Limitação da integral do erro
    integral = output_max / ki;
  }
  else if (integral < output_min / ki) {
    integral = output_min / ki;
  }
  
  derivative = error - last_error;// Cálculo da derivada do erro
  output = kp * error + ki * integral + kd * derivative;// Cálculo da saída do controlador
  
  if (output > output_max) {// Limitação da saída do controlador
    output = output_max;
  }
  else if (output < output_min) {
    output = output_min;
  }

  pwmWrite(pinPWM, output);
  last_error = error;

  // if(media < 0.03 && output > 10){
  //   newSetpoint = setpoint;
  //   setpoint = 0;
  //   err = true;
  // }  

  if(millis() - delayMillis >= DELAYPRINT){
    delayMillis = millis(); 
    lcd.setCursor(0, 0);
    lcd.print("I ");lcd.print(media);lcd.print(" ");
    //lcd.setCursor(0, 0);
    lcd.print("S ");lcd.print(corrente);lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("PWM ");lcd.print(output,0);lcd.print(" ");
    lcd.print("E ");lcd.print(error);lcd.print(" ");
  }
  //delay(1);
}