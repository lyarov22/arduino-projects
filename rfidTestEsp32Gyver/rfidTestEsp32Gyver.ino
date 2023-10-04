#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         22          // Пин для сброса (RST)
#define SS_PIN          21          // Пин для выбора Slave (SDA)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Создаем экземпляр MFRC522

void setup() {
  Serial.begin(115200); // Инициализируем сериальный порт
  SPI.begin();                     // Инициализация SPI
  mfrc522.PCD_Init();                 // Инициализация модуля
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);  // Установка усиления антенны
  mfrc522.PCD_AntennaOff();           // Перезагружаем антенну
  mfrc522.PCD_AntennaOn();            // Включаем антенну
  
  Serial.println(F("Наведите метку RFID для считывания UID..."));

}

void loop() {
  /*static uint32_t rebootTimer = millis(); // Важный костыль против зависания модуля!
  if (millis() - rebootTimer >= 1000) {   // Таймер с периодом 1000 мс
    rebootTimer = millis();               // Обновляем таймер
    digitalWrite(RST_PIN, HIGH);          // Сбрасываем модуль
    delayMicroseconds(2);                 // Ждем 2 мкс
    digitalWrite(RST_PIN, LOW);           // Отпускаем сброс
    mfrc522.PCD_Init();                      // Инициализируем заного
  }
  */
  
  // Проверяем, есть ли новая метка в поле считывания
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Выбираем метку
    if (mfrc522.PICC_ReadCardSerial()) {
      // Считываем UID метки
      String uid = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        uid += String(mfrc522.uid.uidByte[i], HEX);
      }
      Serial.print(F("UID метки: "));
      Serial.println(uid);
      
      // Ожидаем, пока метка не будет удалена из поля считывания
      mfrc522.PICC_HaltA();
    }
  }
}
