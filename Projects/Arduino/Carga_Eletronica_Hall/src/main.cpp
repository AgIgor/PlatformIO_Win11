#include <Arduino.h>
// #include <PWM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <PID_v1.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define encoderA 2
#define encoderB 3
#define encoderButton 4

Encoder myEncoder(encoderA, encoderB);

byte encoderPassos = 4;
bool edit_mode = false;
float modes[] = {0.01,0.05, 0.10, 1.00};

float corrente = 0.00;
int value, oldValue;

// int32_t frequency = 10000; //frequency (in Hz)

float Vzero = 2.42;//2.56
float K = 0.01;//
float B = 0.12;//0.11
float Vbase = 4.80;//4.88
float Vin = 0;
float I = 0;

int sensorPin = A1;
int outputPin = 11;

int leituras = 50;

double Setpoint = 0;
double Kp = 4;
double Ki = 6.8;
double Kd = 0.001;

double Input, Output;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

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
Botao Ok(encoderButton);

void setValor() {
  Setpoint = corrente;
  edit_mode = false;
}

void rst(){
  Setpoint = -10;
}

void toggle_edit_mode(){
  edit_mode = !edit_mode;
}

/* 
void pid_controller(){

  float soma = 0;
  float media = 0;

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
  
  if (integral > output_max / ki) integral = output_max / ki;// Limitação da integral do erro
  else if (integral < output_min / ki) integral = output_min / ki;
  
  derivative = error - last_error;// Cálculo da derivada do erro
  output = kp * error + ki * integral + kd * derivative;// Cálculo da saída do controlador
  
  if (output > output_max) output = output_max;// Limitação da saída do controlador
  else if (output < output_min) output = output_min;

  pwmWrite(pinPWM, output);
  // analogWrite(pinPWM, output);
  // setDuty_pin11( output );
  last_error = error;

  if(edit_mode){

    Ok.press(setValor, rst);
    lcd.setCursor(15, 0);
    lcd.print("*");

    value = myEncoder.read();
    if(oldValue != value){
      oldValue = value;
      value < 0 ? value = 0 : NULL;
      corrente = ((value/encoderPassos) * modes[1] );
      delay(5);
    }

  }
  else{
   
    Ok.press(toggle_edit_mode, rst);
    lcd.setCursor(15, 0);
    lcd.print(" ");

  }

  if(millis() - delayMillis >= DELAYPRINT){
    delayMillis = millis(); 
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I ");lcd.print(media);lcd.print(" ");
    //lcd.setCursor(0, 0);
    lcd.print("S ");lcd.print(corrente);lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("PWM ");lcd.print(output,0);lcd.print(" ");
    lcd.print("E ");lcd.print(error);lcd.print(" ");
  }

}
*/

void getSerial(){
  if (Serial.available() > 0) { // Verifica se há dados disponíveis no monitor serial
    String input = Serial.readStringUntil('\n'); // Lê a string enviada pelo monitor serial
    input.trim(); // Remove espaços em branco do início e do fim da string
    int index = input.indexOf("=");
    if (input.startsWith("kp")) {
      Kp = input.substring(index + 1).toFloat();
    }
    else if (input.startsWith("ki")) {
      Ki = input.substring(index + 1).toFloat();
    }
    else if(input.startsWith("kd")){
      Kd = input.substring(index + 1).toFloat();
    }
    else if(input.startsWith("set")){
      Setpoint = input.substring(index + 1).toFloat();
    }
    else if(input.startsWith("out")){
      Output = input.substring(index + 1).toInt();
    }
    myPID.SetTunings(Kp,Ki,Kd);    
  }//end if serial available
}

void get_encoder(){
  if(edit_mode){

    Ok.press(setValor, rst);
    lcd.setCursor(15, 0);
    lcd.print("*");

    value = myEncoder.read();
    if(oldValue != value){
      oldValue = value;
      value < 0 ? value = 0 : NULL;
      corrente = ((value/encoderPassos) * modes[1] );
      //delay(5);
    }

  }
  else{
   
    Ok.press(toggle_edit_mode, rst);
    lcd.setCursor(15, 0);
    lcd.print(" ");

  }
}

void lcd_print(){
  lcd.setCursor(0, 0);
  lcd.print("I ");lcd.print( Input );lcd.print(" ");
  lcd.print("S ");lcd.print( corrente );lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("PWM ");lcd.print (Output,0 );lcd.print(" ");
  lcd.print("E ");lcd.print( Setpoint - Input, 0 );lcd.print(" ");
}

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  pinMode(encoderButton, INPUT_PULLUP);

  // InitTimersSafe();
  // bool success = SetPinFrequencySafe(pinPWM, frequency);
  // if(!success)while(1){}

  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(outputPin, OUTPUT);

  Vin = analogRead(sensorPin);
  lcd.clear();

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255);

}

void loop() {

  float soma = 0;
  for(int x = 0; x < leituras; x ++){
    Vin = analogRead(sensorPin);
    Vin = (Vin * Vbase) / 1023;
    I = (Vin - Vzero)/(K*B);
    if(I<0)I=0;
    I = I * 0.01;
    soma = soma + I;
  }

  Input = soma/leituras;
  if(Input < 0.1 and Setpoint > 0 and Output > 100) Setpoint = -10;
  myPID.Compute();
  analogWrite(outputPin, int(Output));  
  
  Serial.print("kP= ");
  Serial.print(Kp);
  Serial.print(" - Ki= ");
  Serial.print(Ki);
  Serial.print(" - Kd= ");
  Serial.print(Kd);
  Serial.print(" - set= ");
  Serial.print(Setpoint);
  Serial.print(" Input: ");
  Serial.print(Input);
  Serial.print(" Err: ");
  Serial.print( Setpoint - Input );
  Serial.print(" - Output: ");
  Serial.println(int(Output));

  

  // float Vin2 = (analogRead(A2) * Vbase) / 1023;
  // float I2 = (Vin2 - Vzero)/(K*B);
  // if(I<0) I2 = 0;
  // I2 = I2 * 0.01;
  // Serial.println(I2);

  delay(1);
  //getSerial();
  lcd_print();
  get_encoder();

}//end loop