#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS_PER_DIGIT 7 // 7 LEDs por dígito
#define NUM_DIGITS 29          // 4 dígitos no display
#define LED_PIN A1             // Pino de controle dos LEDs
#define BRIGHTNESS 100        // Brilho dos LEDs

// Definição dos segmentos dos dígitos de 0 a 9
const byte digitSegments[10] = {
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110   // 9
};

CRGB leds[NUM_LEDS_PER_DIGIT * NUM_DIGITS]; // Array para armazenar o estado dos LEDs

void displayNumber(int number) {
  for (int digit = 0; digit < NUM_DIGITS; digit++) {
    int digitNumber = number % 10; // Pega o último dígito do número
    number /= 10; // Remove o último dígito do número

    byte segments = digitSegments[digitNumber]; // Obtém os segmentos para o dígito atual
    for (int segment = 0; segment < 7; segment++) {
      int ledIndex = (digit * NUM_LEDS_PER_DIGIT) + segment; // Calcula o índice do LED atual
      bool lit = bitRead(segments, segment); // Verifica se o segmento deve estar aceso ou apagado
      leds[ledIndex] = lit ? CRGB::Red : CRGB::Black; // Define a cor do LED
    }
  }
  FastLED.show(); // Atualiza os LEDs com as novas cores
}

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS_PER_DIGIT * NUM_DIGITS); // Configuração dos LEDs
  FastLED.setBrightness(BRIGHTNESS); // Configuração do brilho
  Serial.begin(115200); // Inicialização da comunicação serial
  FastLED.clearData();
}

void loop() {
  int number = 0; // Número a ser exibido
  displayNumber(number); // Exibe o número
  delay(1000); // Espera 1 segundo antes de exibir o próximo número
}
