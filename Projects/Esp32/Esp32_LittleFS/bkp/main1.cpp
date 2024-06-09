#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>
#include <time.h>
#include <DNSServer.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
const char* ssid = "ESP32-AP";
const char* password = "";
const char* http_username = "admin";
const char* http_password = "admin";

DNSServer dnsServer;
const byte DNS_PORT = 53;

AsyncWebServer server(80);
String indexPage = {R"(
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

void handleRoot(AsyncWebServerRequest *request) {
    request->send(200, "text/html", "html");
};

void handleADMRoot(AsyncWebServerRequest *request) {
  if (!request->authenticate(http_username, http_password)) {
    return request->requestAuthentication();
  }
  
  String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>";
  html += "<title>Arquivos ESP32</title></head><body>";
  html += "<h1>Arquivos Disponíveis</h1>";
  html += "<ul>";
  
  File root = LittleFS.open("/");
  File file = root.openNextFile();
  while (file) {
    String fileName = file.name();
    String payload="";
    while(file.available()){
        payload += (char)file.read();
    }

    html += "<li>";
    html += "<button onclick=\"confirmDelete('" + fileName + "')\">";
    html += fileName;
    html += "</button>";
    html += "<p>";
    html += payload;
    html += "</p>";
    html += "</li>";
    file = root.openNextFile();
  }
  
  html += "</ul>";
  html += "<script>";
  html += "function confirmDelete(filename) {";
  html += "  if (confirm('Você tem certeza que deseja apagar ' + filename + '?')) {";
  html += "    window.location.href = '/delete?filename=' + filename;";
  html += "  }";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  
  request->send(200, "text/html", html);
}

void handleFileDelete(AsyncWebServerRequest *request) {
  if (!request->authenticate(http_username, http_password)) {
    return request->requestAuthentication();
  }
  String filename = "/" + request->arg("filename");
  if (LittleFS.exists(filename)) {
    LittleFS.remove(filename);
    request->send(200, "text/html", "File Deleted Successfully. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
  } else {
    request->send(404, "text/html", "File Not Found. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
  }
}

void handleNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/html", "Not Found. Redirecionando em 3 segundos...<script>setTimeout(function(){ window.location = '/'; }, 3000);</script>");
}


#define FORMAT_LITTLEFS_IF_FAILED false

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

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char * path){
    Serial.printf("Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
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

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("- file renamed");
    } else {
        Serial.println("- rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

void writeFile2(fs::FS &fs, const char * path, const char * message){
    if(!fs.exists(path)){
		if (strchr(path, '/')) {
            Serial.printf("Create missing folders of: %s\r\n", path);
			char *pathStr = strdup(path);
			if (pathStr) {
				char *ptr = strchr(pathStr, '/');
				while (ptr) {
					*ptr = 0;
					fs.mkdir(pathStr);
					*ptr = '/';
					ptr = strchr(ptr+1, '/');
				}
			}
			free(pathStr);
		}
    }

    Serial.printf("Writing file to: %s\r\n", path);
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void deleteFile2(fs::FS &fs, const char * path){
    Serial.printf("Deleting file and empty folders on path: %s\r\n", path);

    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }

    char *pathStr = strdup(path);
    if (pathStr) {
        char *ptr = strrchr(pathStr, '/');
        if (ptr) {
            Serial.printf("Removing all empty folders on path: %s\r\n", path);
        }
        while (ptr) {
            *ptr = 0;
            fs.rmdir(pathStr);
            ptr = strrchr(pathStr, '/');
        }
        free(pathStr);
    }
}

void testFileIO(fs::FS &fs, const char * path){
    Serial.printf("Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }

    size_t i;
    Serial.print("- writing" );
    uint32_t start = millis();
    for(i=0; i<2048; i++){
        if ((i & 0x001F) == 0x001F){
          Serial.print(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    Serial.printf(" - %u bytes written in %u ms\r\n", 2048 * 512, end);
    file.close();

    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.print("- reading" );
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F){
              Serial.print(".");
            }
            len -= toRead;
        }
        Serial.println("");
        end = millis() - start;
        Serial.printf("- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    } else {
        Serial.println("- failed to open file for reading");
    }
}

void setup(){
    Serial.begin(115200);
    if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
        Serial.println("LittleFS Mount Failed");
        return;
    }

    listDir(LittleFS, "/", 0);
    // createDir(LittleFS, "/mydir");
    // 	writeFile(LittleFS, "/mydir/hello2.txt", "Hello2");
    //   //writeFile(LittleFS, "/mydir/newdir2/newdir3/hello3.txt", "Hello3");
    //     writeFile2(LittleFS, "/mydir/newdir2/newdir3/hello3.txt", "Hello3");
    // 	listDir(LittleFS, "/", 3);
    // 	deleteFile(LittleFS, "/mydir/hello2.txt");
    //   //deleteFile(LittleFS, "/mydir/newdir2/newdir3/hello3.txt");
    //     deleteFile2(LittleFS, "/mydir/newdir2/newdir3/hello3.txt");
    // 	removeDir(LittleFS, "/mydir");
    // 	listDir(LittleFS, "/", 3);
    //     writeFile(LittleFS, "/hello.txt", "Hello ");
    appendFile(LittleFS, "/pass.txt", "Hello World!\r\n");
    //     readFile(LittleFS, "/hello.txt");
    //     renameFile(LittleFS, "/hello.txt", "/foo.txt");
    readFile(LittleFS, "/pass.txt");
    //     deleteFile(LittleFS, "/foo.txt");
    //     testFileIO(LittleFS, "/test.txt");
    //deleteFile(LittleFS, "/test.txt");


    // Configuração do ponto de acesso
    WiFi.softAP(ssid, password);
    Serial.println("Ponto de acesso iniciado");
    Serial.print("IP do ponto de acesso: ");
    Serial.println(WiFi.softAPIP());
    
    // Configuração do servidor web
    server.on("/adm", handleADMRoot);
    server.on("/", handleRoot);
    // server.on("/upload", HTTP_POST, []() {
    //     server.send(200);
    // }, handleFileUpload);
    // server.on("/file", HTTP_GET, handleFileView);
    server.on("/delete", HTTP_GET, handleFileDelete);
    server.onNotFound(handleNotFound);