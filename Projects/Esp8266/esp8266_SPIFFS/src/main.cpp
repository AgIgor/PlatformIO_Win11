#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "VIVOFIBRA-9501"
#define STAPSK "rgw7ucm3GT"
#endif

const char *ssid = "";
const char *pass = "";

long timezone = -4;
byte daysavetime = 1;

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

void readFile(const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) { Serial.write(file.read()); }
  file.close();
}

void writeFile(const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  delay(2000);  // Make sure the CREATE and LASTWRITE times are different
  file.close();
}

void appendFile(const char *path, const char *message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = LittleFS.open(path, "a");
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(const char *path1, const char *path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (LittleFS.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (LittleFS.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}



void salvarConfiguracao() {
  StaticJsonDocument<128> doc;

  doc["SSID"] = ssid;
  doc["Senha"] = pass;

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Erro ao abrir o arquivo de configuração para escrita.");
    return;
  }

  serializeJson(doc, configFile);
  configFile.close();
}

void carregarConfiguracao() {
  File configFile = LittleFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Erro ao abrir o arquivo de configuração para leitura.");
    return;
  }

  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, configFile);
  if (error) {
    Serial.println("Erro ao analisar o arquivo de configuração JSON.");
    return;
  }

  const char* ssidFromJson = doc["SSID"];
  const char* passwordFromJson = doc["Senha"];

  if (ssidFromJson && passwordFromJson) {
    ssid = ssidFromJson;
    pass = passwordFromJson;
  }

  configFile.close();
}


void setup() {
  Serial.begin(115200);
/*
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Contacting Time Server");
  configTime(3600 * timezone, daysavetime * 3600, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");
  struct tm tmstruct;
  delay(2000);
  tmstruct.tm_year = 0;
  getLocalTime(&tmstruct, 5000);
  
  Serial.printf("\nNow is : %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct.tm_year) + 1900, (tmstruct.tm_mon) + 1, tmstruct.tm_mday, tmstruct.tm_hour, tmstruct.tm_min, tmstruct.tm_sec);
  Serial.println("");
  */
  // listDir("/");
  // deleteFile("/hello.txt");
  // writeFile("/hello.txt", "Hello ");
  // appendFile("/hello.txt", "World!\n");
  // listDir("/");

  // Inicialize o sistema de arquivos LittleFS
  if (!LittleFS.begin()) {
    Serial.println("Falha ao inicializar o sistema de arquivos LittleFS.");
    while (1);
  }
  
  //LittleFS.format();

  // Verifique se o arquivo JSON de configuração existe
  if (!LittleFS.exists("/config.json")) {
    Serial.println("Arquivo JSON de configuração não encontrado. Criando um novo...");
    salvarConfiguracao();
  }

  // Carregue as configurações do arquivo JSON
  carregarConfiguracao();

  // Exiba as configurações carregadas
  Serial.println("Configurações carregadas:");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Senha: ");
  Serial.println(pass);
}

void loop() {
  delay(1);
}