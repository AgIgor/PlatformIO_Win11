#include <Arduino.h>

#define PULSE_PIN 11
#define  READ_PIN 12

const uint32_t  ANALOG_TIMEOUT  = 500;  // = 20ms 20000

// Setup ----------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(PULSE_PIN,  OUTPUT);      // Envio do pulso
  pinMode(READ_PIN,   INPUT);       // Leitura
}

// Função de Leitura Analógica-------------------------------------------------
uint8_t analogDigitalRead(const uint8_t &pin) {
  // Envia pulso
  digitalWrite(PULSE_PIN, HIGH);
  uint32_t us = micros();

  // Aguarda carga do capacitor
  while ((micros() - us) < ANALOG_TIMEOUT && digitalRead(READ_PIN) == LOW);

  // Obtem tempo de carga
  us = micros() - us;

  // Coloca pino em nível baixo para descarga do capacitor
  digitalWrite(PULSE_PIN, LOW);

  // Aguarda descarga (= Tau x 5)
  delay(ANALOG_TIMEOUT / 1000 * 5); // Tempo em ms

  // Verifica valor lido
  if (us > ANALOG_TIMEOUT) {
    // Timeout
    us = ANALOG_TIMEOUT;
  }
  
  // Calcula leitura (0% a 100%)
  return uint8_t(us * 100 / ANALOG_TIMEOUT);
}

// Loop -----------------------------------------------------------------------
void loop() {
  // Chama função de leitura analógica
  Serial.print(analogDigitalRead(READ_PIN));
  Serial.println("");
}
