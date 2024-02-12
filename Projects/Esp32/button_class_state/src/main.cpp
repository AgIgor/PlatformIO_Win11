#include <Arduino.h>
int contadorCliques = 0;

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

  void press(void (*funcao)()) {
    bool estadoBotao = !digitalRead(pino);
    unsigned long tempoAtual = millis();

    if (estadoBotao && !estadoAnterior && (tempoAtual - tempoAnterior) > 25) {
      tempoAnterior = tempoAtual;
      //Serial.println("Down");
    }
    else if (!estadoBotao && estadoAnterior && (tempoAtual - tempoAnterior) > 25) {
      tempoAnterior = tempoAtual;
      //Serial.println("Up");
      funcao();
    }
    else if (estadoBotao ) {
      if(tempoAtual - tempoAnterior > 2000){
        tempoAnterior = tempoAtual;
        Serial.println("5sec");
      }
    }
    
    estadoAnterior = estadoBotao;
  }
};

void inc() {
  contadorCliques++;
  Serial.print("Contagem: ");
  Serial.println(contadorCliques);
}
void dec() {
  contadorCliques--;
  Serial.print("Contagem: ");
  Serial.println(contadorCliques);
}

Botao Up(32);
Botao Down(33);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

void loop() {

  Up.press(inc);
  Down.press(dec);
  delay(10);

}
