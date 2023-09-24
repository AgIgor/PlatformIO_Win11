#include <Arduino.h>
#include <LittleFS.h>
#include <FS.h>

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.print("fileContent: ");
  Serial.println(fileContent);
  return fileContent;
}
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
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

int data = 4; 

void setup() {
  Serial.begin(115200);
  if (!LittleFS.begin()) { //to start littlefs
  Serial.println("LittleFS mount failed");
  return;
  }
}

void loop() {
  data = readFile(LittleFS, "/data.txt").toInt();
  Serial.println(data);
  
  
  delay(5000);
  String msg = "";
  msg = String(millis()/1000);
  writeFile(LittleFS, "/data.txt", msg.c_str());
  delay(500);
  
}