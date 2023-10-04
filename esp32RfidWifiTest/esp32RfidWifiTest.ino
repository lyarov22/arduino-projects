#include <SPI.h>
#include <MFRC522.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define RST_PIN 22
#define SS_PIN 21

MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* ssid = "OPPO_A74";
const char* password = "04060708";

const char* serverUrl = "http://192.168.14.253:5000/api/users/register";

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  mfrc522.PCD_AntennaOff();
  mfrc522.PCD_AntennaOn();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connected to Wi-Fi");
  Serial.println(F("Hold an RFID tag near the reader..."));
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      String uid = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        uid += String(mfrc522.uid.uidByte[i], HEX);
      }
      Serial.print(F("UID: "));
      Serial.println(uid);

      // Create a JSON object
      DynamicJsonDocument jsonDoc(128);
      jsonDoc["uid"] = uid;

      // Serialize the JSON to a string
      String jsonString;
      serializeJson(jsonDoc, jsonString);

      // Create an HTTP client
      HTTPClient http;

      Serial.println("Sending POST request to the server...");

      // Start the HTTP request
      http.begin(serverUrl);

      // Set the Content-Type header to indicate JSON data
      http.addHeader("Content-Type", "application/json");

      // Send the JSON data in the request body
      int httpResponseCode = http.POST(jsonString);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("Response from the server: ");
        Serial.println(response);
      } else {
        Serial.print("HTTP request error: ");
        Serial.println(httpResponseCode);
      }

      http.end();
      delay(1000);

      mfrc522.PICC_HaltA();
    }
  }
}
