#include <Arduino.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h> 

// const char* ssid = "VIVOFIBRA-9501";
// const char* password = "rgw7ucm3GT";

// const char *ssid = "Esp";
// const char *password = "";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

#define pinF  13
#define pinT  12
#define pinE  14
#define pinD  27

#define pinSF  15
#define pinST  2
#define pinL1  4
#define pinL2  5
#define pinL3  18


void sendCarCommand(const char *command)
{
  String cmd = String(command);
  Serial.println(cmd);

  if (cmd == "E:true")
  {
    digitalWrite(pinF, LOW);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinD, LOW);
    digitalWrite(pinT, LOW);
  }
  if (cmd == "D:true")
  {
    digitalWrite(pinF, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinT, LOW);
  }
  if (cmd == "F:true")
  {
    digitalWrite(pinF, HIGH);
    digitalWrite(pinE, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinT, LOW);
  }
  if (cmd == "T:true")
  {
    digitalWrite(pinF, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinT, HIGH);
  }
  if (cmd == "FE:true")
  {
    digitalWrite(pinF, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinD, LOW);
    digitalWrite(pinT, LOW);
  }
  if (cmd == "FD:true")
  {
    digitalWrite(pinF, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, LOW);
    digitalWrite(pinT, LOW);
  }
  if (cmd == "TE:true")
  {
    digitalWrite(pinF, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinT, HIGH);
  }
  if (cmd == "TD:true")
  {
    digitalWrite(pinF, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinT, HIGH);
  }
  if (cmd == "C:false")
  {
    digitalWrite(pinF, LOW);
    digitalWrite(pinT, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinD, LOW);
  }
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
  {
    // Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    // client->printf("Hello Client %u :)", client->id());
    // client->ping();
  }

  case WS_EVT_DISCONNECT:
  {
    // Serial.printf("ws[%s][%u] disconnect\n", server->url(), client->id());
  }

  case WS_EVT_DATA:
  {
    //data packet
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len)
    {
      //the whole message is in a single frame and we got all of it's data
      if (info->opcode == WS_TEXT)
      {
        data[len] = 0;
        char *command = (char *)data;
        sendCarCommand(command);
      }
    }
  }

  case WS_EVT_PONG:
  {
    // Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
    // data[len] = 0;
    //     char *command = (char *)data;
        sendCarCommand((char *)data);
  }

  case WS_EVT_ERROR:
  {
    // Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
  }
  }
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}
String getRedes(){
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  String redes = "";
  // Serial.println("Scanning Wi-Fi networks...");
  
  int numNetworks = WiFi.scanNetworks();
  if (numNetworks == 0) {
    return "Wifi não encontrado!";
  } else {

    for (int i = 0; i < numNetworks; ++i) {
      // Serial.print("Network name: ");
      // Serial.println(WiFi.SSID(i));
      // Serial.print("Signal strength: ");
      // Serial.println(WiFi.RSSI(i));
      // Serial.println("-----------------------");
      redes += String(WiFi.SSID(i))+",";
    }
  }
  return redes;
}
void setup()
{
  pinMode(pinF, OUTPUT);
  pinMode(pinT, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinD, OUTPUT);
  
  pinMode(pinSF, OUTPUT);
  pinMode(pinST, OUTPUT);
  pinMode(pinL1, OUTPUT);
  pinMode(pinL2, OUTPUT);
  pinMode(pinL3, OUTPUT);

  digitalWrite(pinF, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinD, LOW);
  
  digitalWrite(pinSF, LOW);
  digitalWrite(pinST, LOW);
  digitalWrite(pinL1, LOW);
  digitalWrite(pinL2, LOW);
  digitalWrite(pinL3, LOW);


  Serial.begin(115200);
  if (!LittleFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  WiFi.softAP("Silverado", "");
  Serial.print("AP address: ");
  Serial.println(WiFi.softAPIP());

  /* WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
    WiFi.softAP("Esp", "");
    Serial.print("AP address: ");
    Serial.println(WiFi.softAPIP());


    //getRedes();
    bool flag = true;
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      Serial.println("Requesting index page...");
      request->send(LittleFS, "/wm.html", "text/html", false);
      // request->send(200, getRedes() , "text/plain");
    });
    server.on("/wm", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      Serial.println("Requesting index page...");
      request->send(200, getRedes() , "text/plain");
    });
    server.onNotFound(notFound);
    server.begin();
    while (flag)
    {
      delay(1);
    }

  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); */

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
  DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    Serial.println("Requesting index page...");
    request->send(LittleFS, "/index.html", "text/html", false);
  });

  server.on("/joy.js", HTTP_GET, [](AsyncWebServerRequest *request)
  { 
    request->send(LittleFS, "/joy.js", "text/javascript"); 
  });

  server.onNotFound(notFound);
  server.begin();
}
void loop() {
}
