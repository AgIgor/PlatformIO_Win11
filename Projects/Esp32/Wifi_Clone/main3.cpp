#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

#include <LittleFS.h>

// Defina o SSID e a senha do ponto de acesso
const char *ssid = "CaptivePortal";
const char *password = "12345678";

// Crie instâncias para o servidor web e o DNSServer
AsyncWebServer server(80);
DNSServer dnsServer;

const byte DNS_PORT = 53;

// Página HTML de login
const char* loginPage = R"(
<!DOCTYPE html>
<html>
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form action="/login" method="POST">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
)";

// Função para inicializar LittleFS
void initLittleFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  } else {
    Serial.println("LittleFS mounted successfully");
  }
}

// Função para armazenar os dados de login
void storeLoginData(const String& username, const String& password) {
  File file = LittleFS.open("/login.txt", "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  file.println("Username: " + username);
  file.println("Password: " + password);
  file.close();
}

// Função para configurar o ponto de acesso
void setupAP() {
  WiFi.softAP(ssid, password);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void setup() {
  Serial.begin(115200);
  initLittleFS();
  setupAP();

  // Redireciona todas as solicitações para a página de login
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(200, "text/html", loginPage);
  });

  // Lida com o envio do formulário de login
  server.on("/login", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("username", true) && request->hasParam("password", true)) {
      String inputUsername = request->getParam("username", true)->value();
      String inputPassword = request->getParam("password", true)->value();

      // Verifique o login (aqui você pode adicionar a verificação real do usuário)
      if (inputUsername == "admin" && inputPassword == "admin") {
        storeLoginData(inputUsername, inputPassword);
        request->send(200, "text/html", "Login Successful and Data Stored!");
      } else {
        request->send(200, "text/html", "Login Failed. Please try again.");
      }
    } else {
      request->send(400, "text/html", "Bad Request");
    }
  });

  // Inicia o servidor
  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
}
