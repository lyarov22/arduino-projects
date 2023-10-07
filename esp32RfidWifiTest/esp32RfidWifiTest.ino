#include <SPI.h>
#include <MFRC522.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define RST_PIN 5
#define SS_PIN 17

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, SCREEN_ADDRESS);



MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* ssid = "SGP621";
const char* password = "popopopa";

const char* serverUrl = "http://192.168.14.253:5000/api/users/register";

String text = "";

void displayWriter(const char* text){
  display.clearDisplay();

  //display.setTextSize(1);             // Normal 1:1 pixel scale
  // display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text

  // display.println(F("askpkl          v.0.2"));
  // display.println();
  
  display.setCursor(0,0);             // Start at top-left corner
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print(text);
  Serial.println(text);
  display.display();
}

void wifiDebugger(){
  text = "";
  text += "Wifi Connected.\n";
  text += "IP:";
  text += WiFi.localIP().toString();
  text += "\nReading...\n";
  
  displayWriter(text.c_str());
}

void setup() {
    Wire.begin();
  Serial.begin(115200);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  displayWriter("Start!");
 
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  mfrc522.PCD_AntennaOff();
  mfrc522.PCD_AntennaOn();

  WiFi.begin(ssid, password);
  
  int count = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(600);

    displayWriter("Connecting..."+ count);
    count++;

    if (count > 6){
      displayWriter("Time out.\nReloading...");
      setup();
    }
  }
  
  wifiDebugger();
  
}

void loop() {
  text = "";
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      String uid = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        uid += String(mfrc522.uid.uidByte[i], HEX);
      }
      
      text += "UID: ";
      text += uid;
      displayWriter(text.c_str());

      // Create a JSON object
      DynamicJsonDocument jsonDoc(128);
      jsonDoc["uid"] = uid;

      // Serialize the JSON to a string
      String jsonString;
      serializeJson(jsonDoc, jsonString);

      // Create an HTTP client
      HTTPClient http;
      text += "\nSending request...";
      displayWriter(text.c_str());
      
      // Start the HTTP request
      http.begin(serverUrl);

      // Set the Content-Type header to indicate JSON data
      http.addHeader("Content-Type", "application/json");

      // Send the JSON data in the request body
      int httpResponseCode = http.POST(jsonString);

      if (httpResponseCode > 0) {
        String response = http.getString();
        
        text += "Response:\n";
        text += response;
        displayWriter(text.c_str());
        
      } else {
        text += "\nHTTP error: ";
        text += httpResponseCode;
        displayWriter(text.c_str());
      }

      http.end();
      delay(1000);

      mfrc522.PICC_HaltA();
    }
  }
}
