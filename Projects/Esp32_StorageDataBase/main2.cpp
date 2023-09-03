#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "VIVOFIBRA-9501"
#define WIFI_PASSWORD "rgw7ucm3GT"
#define API_KEY "AIzaSyDMipFQn8eW6vfLVoQ-rWxYuF_cRyXEVoc"
#define DATABASE_URL "https://teste-b1ceb-default-rtdb.firebaseio.com"
#define USER_EMAIL "agigor@outlook.com"
#define USER_PASSWORD "1207rogi"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool taskCompleted = false;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;

  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "lnB2E1gGijt9Ryb8fWTFnelL4f7VWCPImvWTUBEP";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

bool flag = true;

void loop(){
  if (Firebase.ready() && !taskCompleted){
    taskCompleted = true;

    Serial.printf("Set timestamp... %s\n", Firebase.RTDB.setTimestamp(&fbdo, "/esp32/timestamp") ? "ok" : fbdo.errorReason().c_str());

    if (fbdo.httpCode() == FIREBASE_ERROR_HTTP_CODE_OK){
      Serial.print("TIMESTAMP (Seconds): ");
      Serial.println(fbdo.to<int>());
      printf("TIMESTAMP (milliSeconds): %lld\n", fbdo.to<uint64_t>());
    }

    Serial.printf("Get timestamp... %s\n", Firebase.RTDB.getDouble(&fbdo, "/esp32/timestamp") ? "ok" : fbdo.errorReason().c_str());
    if (fbdo.httpCode() == FIREBASE_ERROR_HTTP_CODE_OK) printf("TIMESTAMP: %lld\n", fbdo.to<uint64_t>());
    FirebaseJson json;

    json.set("Data", "Hello");
    json.set("Ts/.sv", "timestamp");

    Serial.printf("Set data with timestamp... %s\n", Firebase.RTDB.setJSON(&fbdo, "/esp32/set/data", &json) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());

    // Push data with timestamp
    Serial.printf("Push data with timestamp... %s\n", Firebase.RTDB.pushJSON(&fbdo, "/esp32/push/data", &json) ? "ok" : fbdo.errorReason().c_str());

    // Get previous pushed data
    Serial.printf("Get previous pushed data... %s\n", Firebase.RTDB.getJSON(&fbdo, "/esp32/push/data/" + fbdo.pushName()) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());
  }

  if(((millis()/1000)%60)){
    if(flag){
      flag = false;
      taskCompleted = false;
      Serial.println(millis()/1000);}
  }
  else flag = true;
}