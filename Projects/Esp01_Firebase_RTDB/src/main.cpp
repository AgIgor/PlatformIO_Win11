#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "VIVOFIBRA-9501"
#define WIFI_PASSWORD "rgw7ucm3GT"
#define API_KEY "AIzaSyDMipFQn8eW6vfLVoQ-rWxYuF_cRyXEVoc"
#define USER_EMAIL "agigor@outlook.com"
#define USER_PASSWORD "1207rogi"
#define DATABASE_URL "https://teste-b1ceb-default-rtdb.firebaseio.com/"

#define LED_BUILTIN 0 //led vermelho 0 //led azul 2


FirebaseData stream;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool taskCompleted = true;

unsigned long sendDataPrevMillis = 0;
int count = 0;
volatile bool dataChanged = false;

void streamCallback(FirebaseStream data)
{
  // Serial.printf("stream path, %s\nevent path, %s\ndata type, %s\nevent type, %s\n\n",
  //               data.streamPath().c_str(),
  //               data.dataPath().c_str(),
  //               data.dataType().c_str(),
  //               data.eventType().c_str());
  // printResult(data); // see addons/RTDBHelper.h
  // Serial.println('\n');

  //Serial.printf("Received stream payload size: %d (Max. %d)\n\n", data.payloadLength(), data.maxPayloadLength());
  dataChanged = true;
  String payload="";
  payload = data.stringData().c_str();
  
  Serial.println(payload);
  
  if(payload == "{\"ledPin2\":true}"){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if(payload == "{\"ledPin2\":false}"){
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  if(data.dataPath() == "/ledPin2"){
    if(data.boolData() or data.intData()){
      digitalWrite(LED_BUILTIN, HIGH);
    }else{
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
    Serial.println("stream timed out, resuming...\n");

  if (!stream.httpConnected())
    Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, true);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
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
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
  stream.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
  Firebase.begin(&config, &auth);
  
  if (!Firebase.RTDB.beginStream(&stream, "/test/stream/data")) Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());

  Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);

}

void loop()
{

  // if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  // {
  //   sendDataPrevMillis = millis();
  //   count++;
  //   FirebaseJson json;
  //   json.add("data", "hello");
  //   json.add("num", count);
  //   Serial.printf("Set json... %s\n\n", Firebase.RTDB.setJSON(&fbdo, "/test/stream/data/json", &json) ? "ok" : fbdo.errorReason().c_str());
  // }

  if (dataChanged)
  {
    dataChanged = false;
    // When stream data is available, do anything here...
    // Serial.println("mudanças");
  }

  // After calling stream.keepAlive, now we can track the server connecting status
  if (!stream.httpConnected())
  {
    // Server was disconnected!
  }

// To pause stream
// stream.pauseFirebase(true);
// stream.clear(); // close session and release memory

// To resume stream with callback
// stream.pauseFirebase(false);
// Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);

  if (Firebase.ready() && !taskCompleted)
  {
    taskCompleted = true;

    Serial.printf("Set timestamp... %s\n", Firebase.RTDB.setTimestamp(&fbdo, "/test/timestamp") ? "ok" : fbdo.errorReason().c_str());

    if (fbdo.httpCode() == FIREBASE_ERROR_HTTP_CODE_OK)
    {

      // In setTimestampAsync, the following timestamp will be 0 because the response payload was ignored for all async functions.

      // Timestamp saved in millisecond, get its seconds from int value
      Serial.print("TIMESTAMP (Seconds): ");
      Serial.println(fbdo.to<int>());

      // Or print the total milliseconds from double value
      // Due to bugs in Serial.print in Arduino library, use printf to print double instead.
      printf("TIMESTAMP (milliSeconds): %lld\n", fbdo.to<uint64_t>());
    }

    Serial.printf("Get timestamp... %s\n", Firebase.RTDB.getDouble(&fbdo, "/test/timestamp") ? "ok" : fbdo.errorReason().c_str());
    if (fbdo.httpCode() == FIREBASE_ERROR_HTTP_CODE_OK)
      printf("TIMESTAMP: %lld\n", fbdo.to<uint64_t>());

    // To set and push data with timestamp, requires the JSON data with .sv placeholder
    FirebaseJson json;

    json.set("Data", "Hello");
    // now we will set the timestamp value at Ts
    json.set("Ts/.sv", "timestamp"); // .sv is the required place holder for sever value which currently supports only string "timestamp" as a value

    // Set data with timestamp
    Serial.printf("Set data with timestamp... %s\n", Firebase.RTDB.setJSON(&fbdo, "/test/set/data", &json) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());

    // Push data with timestamp
    Serial.printf("Push data with timestamp... %s\n", Firebase.RTDB.pushJSON(&fbdo, "/test/push/data", &json) ? "ok" : fbdo.errorReason().c_str());

    // Get previous pushed data
    Serial.printf("Get previous pushed data... %s\n", Firebase.RTDB.getJSON(&fbdo, "/test/push/data/" + fbdo.pushName()) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());
  }
}