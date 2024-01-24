#include <Arduino.h>
// #include <WiFi.h>

// #include <GS_SDHelper.h>

// #define WIFI_SSID "VIVOFIBRA-9501"
// #define WIFI_PASSWORD "rgw7ucm3GT"

// #define PROJECT_ID "teste-b1ceb"

// // Service Account's client email
// #define CLIENT_EMAIL "esp32-550@teste-b1ceb.iam.gserviceaccount.com"

// // Service Account's private key
// const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCqgQCUw1yS/gxf\n6Ifmshh3T4iQAtnkvCfA8Q0W2EzKSC76Iuq1AXBm/5zQVpHKmXb89SW14b1NQGEP\nVLTEZ1CEGaK4M+JylWmEsVqcpvur/SZT/CI/0TXeRgtZM1dWZof26mPtqTV45fhD\nY5WFVWLm3L/xg36O0P48jh8vWa9AjsCg28vhYIHLMtIfKziBqhsMcaVE+xk63eim\nCkGrW2avYrdcfiOFwCyConoE8l9E/B8bAB7sJWBoQNXEvDaANJQTtNKV9ANMUm+x\nTCya7FKFqcRhilIRlgexSJ87j01hYnT86SFkrSbbf2aoa32U195D522KIJMcOTMD\neF6GZaXfAgMBAAECggEATxBe6pzk8qynpFm5mzp+qeTRmKYZ0D2H2aptvWgzw6FR\nV2CVobW3H6vsVZevJ1memZI8GGlDVO1DlM5cvK6D4Z3ZnL1ChovOUF/Fetrb3VcY\nTN2gLCOhbR7h6E0sdL460j7Cc9SBHTzWsLke/qMnp5I51454Q1Wabw4gW96kq7RE\nv+UhAMhK4Rd9Ny1M6vW6Eh05H8c6DlsNAdhNESPils7DS53ohYzMU1WYLWeKfdI0\n0xifESJGSDCiY4Ywlc4mQWIBCznYm3Qm6w/hIzMhHObYLahwUaPnk508nRQSedX+\nesVjKZcsg0xGK3XdWoGFaPyxHZ6RUETF47WYmM7yoQKBgQDWSWMxFOTNE4e5jQNv\nI4iLfM7+ZdvkXBu9S+8Ms6TuYe5ee4R/IQWn6vQDvWwgMLxIUhicTRPsjpp1iev6\nOVGjhCUUgp3zsgg3zlikygf9kiyS4Vc3mR+ueVhpA7kJqFAtq6ws4ur/jJ/xrhD4\nRFam8oYetIgHECp4La/LI8EHxwKBgQDLscaIyhR3Za9BN/uCmvq34PtT0jJhazmO\noKuIc9JFVSR4vAj0nBQuontEIeOd781R8mvubnff0qaBfFQ8YMZu1nznOVZDt+bU\ntgdbyLOjtq+tOcVxN+rFuK5i2EnGmKK+l5yiKgemM1qic7T4CzhIiCr04dR3XjS4\nTcsq7S9hKQKBgE+dMoJAzgU3dVzF/HmlTQzuEQXJmFoOsquw857Xe7apoeNuprqI\n7U4G6CQfk3WeRcXk4onnxThFfzOeS5NLCn7jENe+86pgAdeiDaMkALYAQhlMKZhZ\nhsDPCr7xiCUDaM6fErgWktLhT2d+kYV79mnOf3AXCNb+9Zhy+PZTUVtvAoGBAJPI\nez4rPwYRJEGxGCz9vAFEnZOG4T6EyNGOCGWLgncC+t8NrYGq64maIMyhub6QiOp3\nc48dXqNo9ZzkU0kq/UzVGPG5S7j9599T4arZxlt046hOTc2CwDaLcxoLyhroCss0\nvFN7IumWQJ+0SwvbOA6HnILmhXvFQYKmDk0qoEFhAoGASR0rg6VNLe6wdhiT1Dzw\nXm1Ovtsc9eD7T7675ixvxfB0wivh4HGOUxyo3239H5PXMGHOcJGZlH0cgGPdGngO\nlt/n8NBB/ACWD6DHYoFl8xy5GMiL7o3zSq7hDLdFg3eA4DLh2Kfaq/HJagW0yGrs\nBTu8eyXMopyG940QzeWiP20=\n-----END PRIVATE KEY-----\n";

// /**
// const char rootCACert[] PROGMEM = "-----BEGIN CERTIFICATE-----\n"
//                                   "MIIFVzCCAz+gAwIBAgINAgPlk28xsBNJiGuiFzANBgkqhkiG9w0BAQwFADBHMQsw\n"
//                                   "CQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEU\n"
//                                   "MBIGA1UEAxMLR1RTIFJvb3QgUjEwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAw\n"
//                                   "MDAwWjBHMQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZp\n"
//                                   "Y2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjEwggIiMA0GCSqGSIb3DQEBAQUA\n"
//                                   "A4ICDwAwggIKAoICAQC2EQKLHuOhd5s73L+UPreVp0A8of2C+X0yBoJx9vaMf/vo\n"
//                                   "27xqLpeXo4xL+Sv2sfnOhB2x+cWX3u+58qPpvBKJXqeqUqv4IyfLpLGcY9vXmX7w\n"
//                                   "Cl7raKb0xlpHDU0QM+NOsROjyBhsS+z8CZDfnWQpJSMHobTSPS5g4M/SCYe7zUjw\n"
//                                   "TcLCeoiKu7rPWRnWr4+wB7CeMfGCwcDfLqZtbBkOtdh+JhpFAz2weaSUKK0Pfybl\n"
//                                   "qAj+lug8aJRT7oM6iCsVlgmy4HqMLnXWnOunVmSPlk9orj2XwoSPwLxAwAtcvfaH\n"
//                                   "szVsrBhQf4TgTM2S0yDpM7xSma8ytSmzJSq0SPly4cpk9+aCEI3oncKKiPo4Zor8\n"
//                                   "Y/kB+Xj9e1x3+naH+uzfsQ55lVe0vSbv1gHR6xYKu44LtcXFilWr06zqkUspzBmk\n"
//                                   "MiVOKvFlRNACzqrOSbTqn3yDsEB750Orp2yjj32JgfpMpf/VjsPOS+C12LOORc92\n"
//                                   "wO1AK/1TD7Cn1TsNsYqiA94xrcx36m97PtbfkSIS5r762DL8EGMUUXLeXdYWk70p\n"
//                                   "aDPvOmbsB4om3xPXV2V4J95eSRQAogB/mqghtqmxlbCluQ0WEdrHbEg8QOB+DVrN\n"
//                                   "VjzRlwW5y0vtOUucxD/SVRNuJLDWcfr0wbrM7Rv1/oFB2ACYPTrIrnqYNxgFlQID\n"
//                                   "AQABo0IwQDAOBgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4E\n"
//                                   "FgQU5K8rJnEaK0gnhS9SZizv8IkTcT4wDQYJKoZIhvcNAQEMBQADggIBAJ+qQibb\n"
//                                   "C5u+/x6Wki4+omVKapi6Ist9wTrYggoGxval3sBOh2Z5ofmmWJyq+bXmYOfg6LEe\n"
//                                   "QkEzCzc9zolwFcq1JKjPa7XSQCGYzyI0zzvFIoTgxQ6KfF2I5DUkzps+GlQebtuy\n"
//                                   "h6f88/qBVRRiClmpIgUxPoLW7ttXNLwzldMXG+gnoot7TiYaelpkttGsN/H9oPM4\n"
//                                   "7HLwEXWdyzRSjeZ2axfG34arJ45JK3VmgRAhpuo+9K4l/3wV3s6MJT/KYnAK9y8J\n"
//                                   "ZgfIPxz88NtFMN9iiMG1D53Dn0reWVlHxYciNuaCp+0KueIHoI17eko8cdLiA6Ef\n"
//                                   "MgfdG+RCzgwARWGAtQsgWSl4vflVy2PFPEz0tv/bal8xa5meLMFrUKTX5hgUvYU/\n"
//                                   "Z6tGn6D/Qqc6f1zLXbBwHSs09dR2CQzreExZBfMzQsNhFRAbd03OIozUhfJFfbdT\n"
//                                   "6u9AWpQKXCBfTkBdYiJ23//OYb2MI3jSNwLgjt7RETeJ9r/tSQdirpLsQBqvFAnZ\n"
//                                   "0E6yove+7u7Y/9waLd64NnHi/Hm3lCXRSHNboTXns5lndcEZOitHTtNCjv0xyBZm\n"
//                                   "2tIMPNuzjsmhDYAPexZ3FL//2wmUspO8IFgV6dtxQ/PeEMMA3KgqlbbC1j+Qa3bb\n"
//                                   "bP6MvPJwNQzcmRk13NfIRmPVNnGuV/u3gm3c\n"
//                                   "-----END CERTIFICATE-----\n";
// */

// bool taskComplete = false;
// void tokenStatusCallback(TokenInfo info);

// void setup()
// {

//     Serial.begin(115200);
//     Serial.println();
//     Serial.println();

//     GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);

//     WiFi.setAutoReconnect(true);
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//     Serial.print("Connecting to Wi-Fi");
//     unsigned long ms = millis();
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         Serial.print(".");
//         delay(300);
//     }
//     Serial.println();
//     Serial.print("Connected with IP: ");
//     Serial.println(WiFi.localIP());
//     Serial.println();

//     // In case SD/SD_MMC storage file access, mount the SD/SD_MMC card.
//     // SD_Card_Mounting(); // See src/GS_SDHelper.h

//     // GSheet.setCert(rootCACert); // or GSheet.setCertFile("path/to/certificate/file.pem", esp_google_sheet_file_storage_type_flash /* or esp_google_sheet_file_storage_type_sd */);

//     // Set the callback for Google API access token generation status (for debug only)
//     GSheet.setTokenCallback(tokenStatusCallback);
//     GSheet.setPrerefreshSeconds(10 * 60);

//     // Begin the access token generation for Google API authentication
//     GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);

//     // Or begin with the Service Account JSON file
//     // GSheet.begin("path/to/serviceaccount/json/file", esp_google_sheet_file_storage_type_flash /* or esp_google_sheet_file_storage_type_sd */);
// }

// void loop()
// {
//     bool ready = GSheet.ready();

//     if (ready && !taskComplete)
//     {
//         FirebaseJson response;

//         // Serial.println("Get spreadsheet...");
//         // Serial.println("------------------------");

//         // // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets/get

//         // bool success = GSheet.get(&response, "1eeQOpmJqLZ6AIPJwQrTQNlipk3eJpqj1yaKsujG31Eo");
//         // response.toString(Serial, true);
//         // Serial.println();

//         // Serial.println("\nGet spreadsheet by data filter...");
//         // Serial.println("----------------------------------");

//         FirebaseJsonArray dataFiltersArr;

//         FirebaseJson dataFilters1;
//         dataFilters1.add("a1Range", "Sheet1!A1");
//         dataFiltersArr.add(dataFilters1);

//         // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets/getByDataFilter

//         bool success = GSheet.getByDataFilter(&response, "1eeQOpmJqLZ6AIPJwQrTQNlipk3eJpqj1yaKsujG31Eo", &dataFiltersArr , "true");

//         if (success)
//             response.toString(Serial, true);
//         else
//             Serial.println(GSheet.errorReason());
//         Serial.println();
//         Serial.println(ESP.getFreeHeap());

//         taskComplete = true;
//     }
// }

// void tokenStatusCallback(TokenInfo info)
// {
//     if (info.status == token_status_error)
//     {
//         GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
//         GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
//     }
//     else
//     {
//         GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
//     }
// }


#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "VIVOFIBRA-9501";
const char* password = "rgw7ucm3GT";

String id = "1eeQOpmJqLZ6AIPJwQrTQNlipk3eJpqj1yaKsujG31Eo";
String intervalo = "A1:A3";
String api_key = "?key=AIzaSyDNzcnbwIxFIT4zQHpCTWNVEjMlcOyedAE";

void getdata(){
  HTTPClient http;
  String url = "https://sheets.googleapis.com/v4/spreadsheets/"+ id +"/values/" + intervalo + api_key;
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("Código de resposta HTTP: %d\n", httpCode);

    String payload = http.getString();
    Serial.println("Resposta do servidor: ");
    Serial.println(payload);
  } else {
    Serial.println("Falha na requisição HTTP");
  }
  http.end();
}//end getb data


void postData(){

  StaticJsonDocument<64> doc;
  String payLoad = "";
  
  doc["range"] = "A5";
  doc["values"]["igor"] = 26;
  
  serializeJson(doc, payLoad);
  
  HTTPClient http;
  String url = "https://sheets.googleapis.com/v4/spreadsheets/"+ id +"/values/" + "A6" + api_key;
  http.begin(url);
  
  int httpCode = http.PUT(payLoad);

  if (httpCode > 0) {
    Serial.printf("Código de resposta HTTP: %d\n", httpCode);

    String payload = http.getString();
    Serial.println("Resposta do servidor: ");
    Serial.println(payload);
  } else {
    Serial.println("Falha na requisição HTTP");
  }
  http.end();
}//end post data

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");
}//end setup

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    getData();
    //postData();
  }

  delay(5000);
}

