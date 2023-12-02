#include <Arduino.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h> 
#include <ArduinoJson.h>

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";

// const char *ssid = "Esp";
// const char *password = "";

// AsyncWebserver runs on port 80 and the asyncwebsocket is initialize at this point also
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

int ledPin1 = 13; // Pino do LED
int ledPin2 = 12; // Pino do LED
int ledPin3 = 14; // Pino do LED
int ledPin4 = 27; // Pino do LED


void sendCarCommand(const char *command)
{
  // command could be either "left", "right", "forward" or "reverse" or "stop"
  // or speed settingg "slow-speed", "normal-speed", or "fast-speed"
  if (strcmp(command, "left") == 0)
  {
    digitalWrite(ledPin1, HIGH);
    //car.turnLeft();
    Serial.println("1");
  }
  else if (strcmp(command, "right") == 0)
  {
    digitalWrite(ledPin2, HIGH);
    //car.turnRight();
    Serial.println("2");
  }
  else if (strcmp(command, "up") == 0)
  {
    digitalWrite(ledPin3, HIGH);
    //car.moveForward();
    Serial.println("3");
  }
  else if (strcmp(command, "down") == 0)
  {
    digitalWrite(ledPin4, HIGH);
    //car.moveBackward();
    Serial.println("4");
  }
  else if (strcmp(command, "stop") == 0)
  {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    //car.stop();
  }
  else if (strcmp(command, "slow-speed") == 0)
  {
    //car.setCurrentSpeed(speedSettings::SLOW);
  }
  else if (strcmp(command, "normal-speed") == 0)
  {
    //car.setCurrentSpeed(speedSettings::NORMAL);
  }
  else if (strcmp(command, "fast-speed") == 0)
  {
    //car.setCurrentSpeed(speedSettings::FAST);
  }
}


// Callback function that receives messages from websocket client
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
  {
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    // client->printf("Hello Client %u :)", client->id());
    // client->ping();
  }

  case WS_EVT_DISCONNECT:
  {
    Serial.printf("ws[%s][%u] disconnect\n", server->url(), client->id());
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
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
  }

  case WS_EVT_ERROR:
  {
    // Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
  }
  }
}

// Function called when resource is not found on the server
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}


void setup()
{
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);


  Serial.begin(115200);

  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // WiFi.softAP(ssid, password);
  // Serial.print("IP address: ");
  // Serial.println(WiFi.softAPIP());

  // Initialize LittleFS
  if (!LittleFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Add callback function to websocket server
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              Serial.println("Requesting index page...");
              request->send(LittleFS, "/index.html", "text/html", false);
            });

  server.on("/joy.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/joy.js", "text/javascript"); });

  /* // Route to load custom.css file
  server.on("/css/custom.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/css/custom.css", "text/css"); });

  // Route to load custom.js file
  server.on("/js/custom.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/js/custom.js", "text/javascript"); }); */

  // On Not Found
  server.onNotFound(notFound);

  // Start server
  server.begin();
}
void loop() {}
