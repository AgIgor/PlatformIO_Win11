#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/SDHelper.h>

#define WIFI_SSID "VIVOFIBRA-9501"
#define WIFI_PASSWORD "rgw7ucm3GT"

#define API_KEY "AIzaSyDMipFQn8eW6vfLVoQ-rWxYuF_cRyXEVoc"
#define USER_EMAIL "agigor@outlook.com"
#define USER_PASSWORD "1207rogi"

#define STORAGE_BUCKET_ID "teste-b1ceb.appspot.com"

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
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    
    config.fcs.upload_buffer_size = 512;
    SD_Card_Mounting();
}

void fcsUploadCallback(FCS_UploadStatusInfo info){
    if (info.status == fb_esp_fcs_upload_status_init){
        Serial.printf("Uploading file %s (%d) to %s\n", info.localFileName.c_str(), info.fileSize, info.remoteFileName.c_str());
    }
    else if (info.status == fb_esp_fcs_upload_status_upload){
        Serial.printf("Uploaded %d%s, Elapsed time %d ms\n", (int)info.progress, "%", info.elapsedTime);
    }
    else if (info.status == fb_esp_fcs_upload_status_complete){
        Serial.println("Upload completed\n");
        FileMetaInfo meta = fbdo.metaData();
        Serial.printf("Name: %s\n", meta.name.c_str());
        Serial.printf("Bucket: %s\n", meta.bucket.c_str());
        Serial.printf("contentType: %s\n", meta.contentType.c_str());
        Serial.printf("Size: %d\n", meta.size);
        Serial.printf("Generation: %lu\n", meta.generation);
        Serial.printf("Metageneration: %lu\n", meta.metageneration);
        Serial.printf("ETag: %s\n", meta.etag.c_str());
        Serial.printf("CRC32: %s\n", meta.crc32.c_str());
        Serial.printf("Tokens: %s\n", meta.downloadTokens.c_str());
        Serial.printf("Download URL: %s\n\n", fbdo.downloadURL().c_str());
    }
    else if (info.status == fb_esp_fcs_upload_status_error){
        Serial.printf("Upload failed, %s\n", info.errorMsg.c_str());
    }
}

void loop(){
    if (Firebase.ready() && !taskCompleted){
        taskCompleted = true;
    
        Serial.printf("List files... %s\n", Firebase.Storage.listFiles(&fbdo, STORAGE_BUCKET_ID) ? "ok" : fbdo.errorReason().c_str());
    
        if (fbdo.httpCode() == FIREBASE_ERROR_HTTP_CODE_OK){
            FileList *files = fbdo.fileList();
            for (size_t i = 0; i < files->items.size(); i++)
                Serial.printf("name: %s, bucket: %s\n", files->items[i].name.c_str(), files->items[i].bucket.c_str());
        }
        fbdo.fileList()->items.clear();
        
        Serial.println("\nUpload file...\n");
        if (!Firebase.Storage.upload(&fbdo, STORAGE_BUCKET_ID, "data/media.mp4", mem_storage_type_sd, "media.mp4", "video/mp4", fcsUploadCallback))
            Serial.println(fbdo.errorReason());
    }
}
