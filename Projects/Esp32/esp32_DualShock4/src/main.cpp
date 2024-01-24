#include <Arduino.h>
#include <PS4Controller.h>
uint8_t broadcastAddress[] = {0x58, 0xBF, 0x25, 0x81, 0x3E, 0x98};

byte r = 255;
byte g = 0;
byte b = 0;

int initialLX = 0; 
int initialLY = 0; 
int initialRX = 0; 
int initialRY = 0; 

const char* PINS[][2] = {
  {"frente"    , "13"},
  {"tras"      , "12"},
  {"esquerda"  , "14"},
  {"direita"   , "27"},
  {"sobe"      , "4"},
  {"desce"     , "5"},
  {"farol"     , "22"},
  {"lanterna"  , "23"},
};

byte getPin(char* name){
  byte tam = sizeof (PINS) / sizeof (PINS[0]);
  for(byte i=0; i< tam; i++){
    if(String(PINS[i][0]).indexOf(name) != -1){
      return String(PINS[i][1]).toInt();
    }
  }
  return 0;
}

void nextRainbowColor() {
  if (r > 0 && b == 0) {
    r--;
    g++;
  }
  if (g > 0 && r == 0) {
    g--;
    b++;
  }
  if (b > 0 && g == 0) {
    r++;
    b--;
  }
}//end nextRainbowColor 

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  byte tam = sizeof (PINS) / sizeof (PINS[0]);
  for(byte i=0; i< tam; i++){
    pinMode(String(PINS[i][1]).toInt(), OUTPUT);
  }

  while(!PS4.isConnected()){
    // PS4.begin("1c:66:6d:76:84:1b");//
    PS4.begin("48:fd:a3:19:75:67");//
    Serial.print(".");
	delay(500);
  }
  Serial.println("Ready.");

  delay(200);
  if (PS4.isConnected()) {
    initialLX = PS4.LStickX();
    delay(1);
    initialLY = PS4.LStickY();
    delay(1);
    initialRX = PS4.RStickX();
    delay(1);
    initialRY = PS4.RStickY();
    delay(1);
  }
  delay(100);

  Serial.println(ESP_MAC_BT);


}//end setup
/* 
byte valPress = 0;
bool flag = true;
bool estadoBotao;
unsigned long tempoPressionado;
unsigned long tempoAtual;
unsigned long tempoPressionado;
unsigned long tempoAtual;
int val;
void longPress(bool btn){
    bool btn = digitalRead(BOT_PIN);
  static bool lastBtn;

  if(btn){
     if(lastBtn) {
      val++;
      Serial.println(val);
      lastBtn = false;
    }
    tempoAtual = millis();
  }else{

      if(millis() - tempoAtual > 3000){
        Serial.println("Long");
        tempoAtual = millis();
        lastBtn = true;
        btn = false;
      }
      else if(!lastBtn) {
        Serial.println("Down");
        lastBtn = true;
      }
        
  }

  if((millis()/500)%2){
    if(flag){
      flag = false;
      valPress++;
      //Serial.println(millis());
    }
    else{
      flag = true;
      Serial.println(valPress);
      valPress = 0;
      return;

    }
  }

}
 */
void loop() {

  if (PS4.isConnected()) {

    if (PS4.Right()) Serial.println("Right Button");
    if (PS4.Down()) Serial.println("Down Button");
    if (PS4.Up()) Serial.println("Up Button");
    if (PS4.Left()) Serial.println("Left Button");

    if (PS4.Square()) Serial.println("Square Button");
    if (PS4.Cross()) Serial.println("Cross Button");
    if (PS4.Circle()) Serial.println("Circle Button");

    if (PS4.Triangle()) Serial.println("Triangle Button");
    //longPress(PS4.Triangle());

    if (PS4.UpRight()) Serial.println("Up Right");
    if (PS4.DownRight()) Serial.println("Down Right");
    if (PS4.UpLeft()) Serial.println("Up Left");
    if (PS4.DownLeft()) Serial.println("Down Left");

    if (PS4.L1()) Serial.println("L1 Button");
    if (PS4.R1()) Serial.println("R1 Button");

    if (PS4.Share()) Serial.println("Share Button");
    if (PS4.Options()) Serial.println("Options Button");
    if (PS4.L3()) Serial.println("L3 Button");
    if (PS4.R3()) Serial.println("R3 Button");

    if (PS4.PSButton()) Serial.println("PS Button");

    if (PS4.Touchpad()) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);

/*     if (PS4.L2()) {
      Serial.printf("L2 button at %d\n", PS4.L2Value());
      if(PS4.L2Value() > 150) digitalWrite(getPin("tras"), HIGH);
    }
    else digitalWrite(getPin("tras"), LOW);

    if (PS4.R2()) {
      Serial.printf("R2 button at %d\n", PS4.R2Value());
      if(PS4.R2Value() > 150) digitalWrite(getPin("frente"), HIGH);
    }
    else digitalWrite(getPin("frente"), LOW); 
*/


    if ((PS4.LStickX() - (initialLX))*0.002 < -0.02 or (PS4.LStickX() - (initialLX))*0.002 > 0.02) {
      Serial.printf("Left Stick x at %d\n", PS4.LStickX());
    }
    if ((PS4.LStickY() - (initialLY))*0.002 < -0.02 or (PS4.LStickY() - (initialLY))*0.002 > 0.02) {
      Serial.printf("Left Stick y at %d\n", PS4.LStickY());
    }

    if ((PS4.RStickX() - (initialRX))*0.002 < -0.02 or (PS4.RStickX() - (initialRX))*0.002 > 0.02) {
      //Serial.printf("Right Stick x at %d\n", PS4.RStickX());

      if(PS4.RStickX() > 100){
        digitalWrite(getPin("direita"), HIGH);
        Serial.printf("Right Stick x at %d\n", PS4.RStickX());
      }
      if(PS4.RStickX() < 100){
        digitalWrite(getPin("esquerda"), HIGH);
        Serial.printf("Right Stick x at %d\n", PS4.RStickX());
      }
    }
    else{
      digitalWrite(getPin("direita"), LOW);
      digitalWrite(getPin("esquerda"), LOW);
    }   
/*
    if ((PS4.RStickY() - (initialRY))*0.002 < -0.02 or (PS4.RStickY() - (initialRY))*0.002 > 0.02) {
      Serial.printf("Right Stick y at %d\n", PS4.RStickY());
    }
*/
/*
    if (PS4.Charging()) Serial.println("The controller is charging");
    if (PS4.Audio()) Serial.println("The controller has headphones attached");
    if (PS4.Mic()) Serial.println("The controller has a mic attached");

    Serial.printf("Battery Level : %d\n", PS4.Battery());

*/
    // Serial.println()
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
    delay(100);
    PS4.setLed(r, g, b);
    nextRainbowColor();

    // Sets how fast the controller's front light flashes
    // Params: How long the light is on in ms, how long the light is off in ms
    // Range: 0->2550 ms, Set to 0, 0 for the light to remain on
    // PS4.setFlashRate(PS4.LStickY() * 10, PS4.RStickY() * 10);

    // Sets the rumble of the controllers
    // Params: Weak rumble intensity, Strong rumble intensity
    // Range: 0->255
    // PS4.setRumble(PS4.L2Value(), PS4.R2Value());

    // Sends data set in the above three instructions to the controller
    PS4.sendToController();
  } 

}//end loop