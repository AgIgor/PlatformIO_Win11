#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID "VIVOFIBRA-9501"
#define WIFI_PASSWORD "rgw7ucm3GT"
#define BOT_TOKEN "6674979229:AAFFHWjMvaPFB7aISUbSb0R3p7zH2it6vNI"

const unsigned long BOT_MTBS = 1000;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;

const int ledPin = LED_BUILTIN;
int ledStatus = 0;

void handleNewMessages(int numNewMessages){
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/ledon"){
      ledStatus = 1;
      digitalWrite(ledPin, ledStatus);
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "/ledoff"){
      ledStatus = 0;
      digitalWrite(ledPin, ledStatus);
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/status"){
      if (ledStatus) bot.sendMessage(chat_id, "Led is ON", "");
      else bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/start"){
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

void setup(){
  Serial.begin(115200);
  Serial.println();

  pinMode(ledPin, OUTPUT);
  delay(10);
  digitalWrite(ledPin, LOW);

  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 24 * 3600){
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop(){
  if (millis() - bot_lasttime > BOT_MTBS){
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages){
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      Serial.println(bot.messages[0].text);
    }

    bot_lasttime = millis();
  }
  
  delay(100);
}