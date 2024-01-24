#include <Arduino.h>

void findPrimes(int n) {
  bool isPrime[n+1];
  memset(isPrime, true, sizeof(isPrime));

  for (int p = 2; p * p <= n; p++) {
    if (isPrime[p]) {
      for (int i = p * p; i <= n; i += p) {
        isPrime[i] = false;
      }
    }
  }

  Serial.println("Prime Numbers:");
  for (int p = 2; p <= n; p++) {
    if (isPrime[p]) {
      Serial.print(p);
      Serial.print(" ");
    }
  }
  Serial.println();
}
void estimatePi(int iterations) {
  int insideCircle = 0;

  for (int i = 0; i < iterations; i++) {
    float x = random(-1.0, 1.0);
    float y = random(-1.0, 1.0);

    if (x*x + y*y <= 1) {
      insideCircle++;
    }
  }

  float pi = 4.0 * insideCircle / iterations;
  Serial.print("Estimated Pi: ");
  Serial.println(pi);
}
void calculateFibonacci(int n) {
  unsigned long long fib[n];
  fib[0] = 0;
  fib[1] = 1;

  for (int i = 2; i < n; i++) {
    fib[i] = fib[i-1] + fib[i-2];
  }

  Serial.println("Fibonacci Numbers:");
  for (int i = 0; i < n; i++) {
    Serial.print(fib[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
}
long int initMillis, endMillis, result;
void loop() {
  Serial.print("Sketch Size: ");Serial.print(ESP.getSketchSize());Serial.print(" bytes ");
  Serial.print("Free Heap Memory: ");Serial.print(ESP.getFreeHeap());Serial.println(" bytes");
  Serial.println("\n");

  initMillis = millis();
  findPrimes(5000);
  endMillis = millis();
  result = endMillis - initMillis;
  Serial.print(result);Serial.println(" ms");
  Serial.println("\n");

  initMillis = millis();
  estimatePi(10000);
  endMillis = millis();
  result = endMillis - initMillis;
  Serial.print(result);Serial.println(" ms");
  Serial.println("\n");

  initMillis = millis();
  calculateFibonacci(500);
  endMillis = millis();
  result = endMillis - initMillis;
  Serial.print(result);Serial.println(" ms");
  Serial.println("\n");

  Serial.println("\n\n");
  delay(5000);

}