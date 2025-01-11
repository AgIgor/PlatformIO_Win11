#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

// Allocate the JSON document
JsonDocument doc;
String output;

const char* ssid = "ESP-01_AP";
const char* password = "12345678";

#define MAX_CLIENTS 4
#define WIFI_CHANNEL 6

const IPAddress localIP(4, 3, 2, 1);
const IPAddress gatewayIP(4, 3, 2, 1);
const IPAddress subnetMask(255, 255, 255, 0);

const String localIPURL = "http://4.3.2.1";
DNSServer dnsServer;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

int pwmValue = 55;

void listDir(const char *dirname) {
	Serial.printf("Listing directory: %s\n", dirname);

	Dir root = LittleFS.openDir(dirname);

	while (root.next()) {
    File file = root.openFile("r");
    Serial.print("  FILE: ");
    Serial.print(root.fileName());
    Serial.print("  SIZE: ");
    Serial.print(file.size());
    time_t cr = file.getCreationTime();
    time_t lw = file.getLastWrite();
    file.close();
    struct tm *tmstruct = localtime(&cr);
    Serial.printf("    CREATION: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
    tmstruct = localtime(&lw);
    Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
  }
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
	AwsFrameInfo *info = (AwsFrameInfo*)arg;
	if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
	data[len] = 0;  // Finaliza a string recebida
	pwmValue = atoi((char*)data); // Converte o valor para inteiro

	byte p = map(pwmValue, 0, 100, 0, 255);
	analogWrite(2, p);    // Atualiza o PWM no GPIO2

	Serial.print("Recebido: ");
	Serial.print(pwmValue);
	Serial.print(" PWM: ");
	Serial.println(p);
	}
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
	case WS_EVT_CONNECT:

		Serial.printf( "WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str() );
		// ws.text(client->id(), "{\"pwm\":" + String(pwmValue) + "}");

		doc["pwm"] = pwmValue;
		serializeJson( doc, output );
		ws.text( client->id(), output );

		break;
    case WS_EVT_DISCONNECT:

		Serial.printf( "WebSocket client #%u disconnected\n", client->id() );

		break;
    case WS_EVT_DATA:

		handleWebSocketMessage( arg, data, len );
		// ws.textAll( "{\"pwm\":" + String(pwmValue) + "}");

		doc["pwm"] = pwmValue;
		serializeJson( doc, output );
		ws.textAll( output );

      	break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      	break;
  }
}

void setUpDNSServer(DNSServer &dnsServer, const IPAddress &localIP){
	// Define the DNS interval in milliseconds between processing DNS requests
	#define DNS_INTERVAL 30

	// Set the TTL for DNS response and start the DNS server
	dnsServer.setTTL(3600);
	dnsServer.start(53, "*", localIP);
}

void startSoftAccessPoint(const char *ssid, const char *password, const IPAddress &localIP, const IPAddress &gatewayIP){
	// Define the maximum number of clients that can connect to the server
	#define MAX_CLIENTS 4
	#define WIFI_CHANNEL 6
	const IPAddress subnetMask(255, 255, 255, 0);
	WiFi.softAPConfig(localIP, gatewayIP, subnetMask);
	WiFi.softAP(ssid, password, WIFI_CHANNEL, 0, MAX_CLIENTS);
}

void setUpWebserver(AsyncWebServer &server, const IPAddress &localIP){
	/* 

	//======================== Webserver ========================
	// WARNING IOS (and maybe macos) WILL NOT POP UP IF IT CONTAINS THE WORD "Success" https://www.esp8266.com/viewtopic.php?f=34&t=4398
	// SAFARI (IOS) IS STUPID, G-ZIPPED FILES CAN'T END IN .GZ https://github.com/homieiot/homie-esp8266/issues/476 this is fixed by the webserver serve static function.
	// SAFARI (IOS) there is a 128KB limit to the size of the HTML. The HTML can reference external resources/images that bring the total over 128KB
	// SAFARI (IOS) popup browser has some severe limitations (javascript disabled, cookies disabled)

	// Required
	server.on("/connecttest.txt", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
	}); // windows 11 captive portal workaround

	server.on("/wpad.dat", [](AsyncWebServerRequest *request){
		request->send(404);
	}); // Honestly don't understand what this is but a 404 stops win 10 keep calling this repeatedly and panicking the esp32 :)

	// Background responses: Probably not all are Required, but some are. Others might speed things up?
	// A Tier (commonly used by modern systems)
	server.on("/generate_204", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
	}); // android captive portal redirect

	server.on("/redirect", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);	
	}); // microsoft redirect

	server.on("/hotspot-detect.html", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);	
	}); // apple call home

	server.on("/canonical.html", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
	}); // firefox captive portal call home

	server.on("/success.txt", [](AsyncWebServerRequest *request){
		request->send(200);
	}); // firefox captive portal call home

	server.on("/ncsi.txt", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
	}); // windows call home

	// B Tier (uncommon)
	//  server.on("/chrome-variations/seed",[](AsyncWebServerRequest *request){request->send(200);}); //chrome captive portal call home
	//  server.on("/service/update2/json",[](AsyncWebServerRequest *request){request->send(200);}); //firefox?
	//  server.on("/chat",[](AsyncWebServerRequest *request){request->send(404);}); //No stop asking Whatsapp, there is no internet connection
	//  server.on("/startpage",[](AsyncWebServerRequest *request){request->redirect(localIPURL);});

	// return 404 to webpage icon
	server.on("/favicon.ico", [](AsyncWebServerRequest *request){ 
		request->send(404);
	}); // webpage icon
	*/

	server.on("/generate_204", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
	}); // android captive portal redirect
	server.on("/redirect", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);	
	}); // microsoft redirect
	server.on("/connecttest.txt", [](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
	}); // windows 11 captive portal workaround

	server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request){
	request->send(LittleFS, "/index.html", "text/html");
		// AsyncWebServerResponse *response = request->beginResponse(200, "text/html", mainPage);
		// response->addHeader("Cache-Control", "public,max-age=31536000");  // save this file to cache for 1 year (unless you refresh)
		// request->send(response);
		Serial.println("Served Basic HTML Page FS"); 
	});
	server.onNotFound([](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
		Serial.print("on not found ");
		Serial.print(request->host());	// This gives some insight into whatever was being requested on the serial monitor
		Serial.print(" ");
		Serial.print(request->url());
		Serial.print(" sent redirect to " + localIPURL + "\n"); 
	});
	// Rota para lidar com a submissão do formulário
	// server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request){
	// 	if (request->hasParam("password", true)) {
	// 	String password = request->getParam("password", true)->value();
	// 	File file = LittleFS.open("/password.txt", "a");
	// 	Serial.println("Senha: " + password);

	// 	if (file) {
	// 		file.println(password + "\n\r");
	// 		file.close();
	// 		request->send(200, "text/html", "Senha salva com sucesso. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
	// 	} else {
	// 		request->send(500, "text/html", "Erro ao salvar a senha. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
	// 	}
	// 	} else {
	// 	request->send(400, "text/html", "Senha não fornecida. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
	// 	}
	// });

	// Rota para a página de administração
	// server.on("/admin", HTTP_GET, [](AsyncWebServerRequest *request){
	// 	if (!request->authenticate(admin_username, admin_password)) {
	// 	return request->requestAuthentication();
	// 	}
	// 	if (LittleFS.exists("/password.txt")) {
	// 	File file = LittleFS.open("/password.txt", "r");
	// 	if (file) {
	// 		String passwordContent;
	// 		while (file.available()) {
	// 		passwordContent += (char)file.read();
	// 		}
	// 		file.close();
	// 		String html = "<html><head><meta charset='UTF-8'></head><body><h1>Conteúdo do Arquivo Salvo</h1><pre>" + passwordContent + "</pre></body></html>";
	// 		request->send(200, "text/html", html);
	// 	} else {
	// 		request->send(500, "text/html", "Erro ao abrir o arquivo.");
	// 	}
	// 	} else {
	// 	request->send(404, "text/html", "Arquivo não encontrado.");
	// 	}
	// });

	/* server.on("/salvar", HTTP_POST, [](AsyncWebServerRequest *request){
		if (!request->authenticate(admin_username, admin_password)) {
			return request->requestAuthentication();
		}
		if (request->hasParam("ssid", true)){
			String ssid = request->getParam("ssid", true)->value();

			File file = LittleFS.open("/config.txt", "w");
			Serial.println("SSID: " + ssid);

			if (file) {
				file.println(ssid);
				file.close();
				request->send(200, "text/html", "Salvo com sucesso. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
			} else {
				request->send(500, "text/html", "Erro ao salvar. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
			}
		} else {
			request->send(400, "text/html", "Senha não fornecida. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
		}
	});

	server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
		if (!request->authenticate(admin_username, admin_password)) {
			return request->requestAuthentication();
		}
		request->send(200, "text/html", configPage);
	}); */
}

void setup() {
	// Configuração da saída PWM
	pinMode(2, OUTPUT);
	analogWriteRange(255); // Define o valor máximo de PWM (0-255)
	analogWrite(2, 127);
	Serial.begin(115200);

	if (!LittleFS.begin()) {
		Serial.println("Falha ao inicializar o sistema de arquivos LittleFS.");
		while (1);
	}
	listDir("/");
  
  	startSoftAccessPoint(ssid, password, localIP, gatewayIP);
	setUpDNSServer(dnsServer, localIP);
	setUpWebserver(server, localIP);
  
	// Inicializa o WebSocket
	ws.onEvent(onEvent);
	server.addHandler(&ws);
	

	// Inicia o servidor
	server.begin();
}

unsigned long delaySendData;
void loop() {
	ws.cleanupClients();
	dnsServer.processNextRequest();
	delay( DNS_INTERVAL );

	if( millis() - delaySendData > 10000 ){
		delaySendData = millis();
		doc["millis"] = millis();
		serializeJson( doc, output );
		ws.textAll( output );

		// ws.textAll("{\"millis\":" + String(millis()) + "}");
	}
}
