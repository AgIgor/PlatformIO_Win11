#include <Arduino.h>
#include <ESP8266WiFi.h>

#define NTP_SERVER     "pool.ntp.br"
#define UTC_OFFSET     -10800
#define UTC_OFFSET_DST 0


void printLocalTime() {
  struct tm tm;
  // if (!getLocalTime(&tm)) {
  //   return;
  // }

  // Serial.print(&timeinfo, "%H:%M:%S");
  // Serial.print(" ");
  // Serial.println(&timeinfo, "%d/%m/%Y   %Z");

  int hora = tm.tm_hour;
  int minuto = tm.tm_min;
  int segundo = tm.tm_sec;

  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
  Serial.print("\n");

}

void setup() {
  Serial.begin(115200);

  WiFi.begin("VIVOFIBRA-79D0", "58331BB245");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
  }
    Serial.print("\n");

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void loop() {
  printLocalTime();
  delay(500);
}
