#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "VIVOFIBRA-9501"
#define WIFI_PASSWORD "rgw7ucm3GT"
#define API_KEY "AIzaSyBM9aYbeDMxQ6M0F1ZPfbF4sELpEshUb14"//"AIzaSyDMipFQn8eW6vfLVoQ-rWxYuF_cRyXEVoc"
#define USER_EMAIL "agigor@outlook.com"
#define USER_PASSWORD "1207rogi"
#define DATABASE_URL "https://esp32-c39f4-default-rtdb.firebaseio.com/"//"https://teste-b1ceb-default-rtdb.firebaseio.com/"


// Define Firebase Data object
FirebaseData stream;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

int count = 0;

String chip_id = "CHIP_ID_";

void streamCallback(StreamData data)
{
  Serial.printf("sream path, %s\nevent path, %s\ndata type, %s\nevent type, %s\n\n",
                data.streamPath().c_str(),
                data.dataPath().c_str(),
                data.dataType().c_str(),
                data.eventType().c_str());
  printResult(data); // see addons/RTDBHelper.h
  Serial.println();

  // This is the size of stream payload received (current and max value)
  // Max payload size is the payload size under the stream path since the stream connected
  // and read once and will not update until stream reconnection takes place.
  // This max value will be zero as no payload received in case of ESP8266 which
  // BearSSL reserved Rx buffer size is less than the actual stream payload.
  //Serial.printf("Received stream payload size: %d (Max. %d)\n\n", data.payloadLength(), data.maxPayloadLength());
  
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
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
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

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
  stream.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

  Firebase.begin(&config, &auth);

  // You can use TCP KeepAlive For more reliable stream operation and tracking the server connection status, please read this for detail.
  // https://github.com/mobizt/Firebase-ESP32#enable-tcp-keepalive-for-reliable-http-streaming
  stream.keepAlive(5, 5, 1);

  if (!Firebase.beginStream(stream, "/test/stream/data"))
    Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());

  Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);

  /** Timeout options, below is default config.

  //Network reconnect timeout (interval) in ms (10 sec - 5 min) when network or WiFi disconnected.
  config.timeout.networkReconnect = 10 * 1000;

  //Socket begin connection timeout (ESP32) or data transfer timeout (ESP8266) in ms (1 sec - 1 min).
  config.timeout.socketConnection = 30 * 1000;

  //ESP32 SSL handshake in ms (1 sec - 2 min). This option doesn't allow in ESP8266 core library.
  config.timeout.sslHandshake = 2 * 60 * 1000;

  //Server response read timeout in ms (1 sec - 1 min).
  config.timeout.serverResponse = 10 * 1000;

  //RTDB Stream keep-alive timeout in ms (20 sec - 2 min) when no server's keep-alive event data received.
  config.timeout.rtdbKeepAlive = 45 * 1000;

  //RTDB Stream reconnect timeout (interval) in ms (1 sec - 1 min) when RTDB Stream closed and want to resume.
  config.timeout.rtdbStreamReconnect = 1 * 1000;

  //RTDB Stream error notification timeout (interval) in ms (3 sec - 30 sec). It determines how often the readStream
  //will return false (error) when it called repeatedly in loop.
  config.timeout.rtdbStreamError = 3 * 1000;

  */


	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: "); Serial.println(ESP.getEfuseMac());

  chip_id += ESP.getEfuseMac();

  String path_chip_id = "/ESP32/";
  path_chip_id += chip_id;

  FirebaseJson json_id;
  json_id.add("chip_id", ESP.getEfuseMac());
  json_id.add("chip_model", ESP.getChipModel());
  json_id.add("chip_rev", ESP.getChipRevision());
  json_id.add("chip_cores", ESP.getChipCores());

  Serial.printf("Set json... %s\n\n", Firebase.setJSON(fbdo, path_chip_id , json_id) ? "ok" : fbdo.errorReason().c_str());

}

void loop()
{

  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    count++;
    FirebaseJson json;
    json.add("data", "hello");
    json.add("num", count);
    Serial.printf("Set json... %s\n\n", Firebase.setJSON(fbdo, "/test/stream/data/json", json) ? "ok" : fbdo.errorReason().c_str());
  }

  // After calling stream.keepAlive, now we can track the server connecting status
  if (!stream.httpConnected())
  {
    // Server was disconnected!
  }
}

// To pause stream
// stream.pauseFirebase(true);
// stream.clear(); // close session and release memory

// To resume stream with callback
// stream.pauseFirebase(false);
// Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);