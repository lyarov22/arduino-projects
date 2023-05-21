#include <Wire.h>
#include <BMP180.h>
#include <LiquidCrystal_I2C.h>
#include "iarduino_RTC.h"
    
/*
Simple Info Display: Time, Temperature, Pressure

Arduino Nano Atmega328P (old bootloader)

BMP180:
SDA - A4
SCL - A5
VIN - 5V
GND - GND

LCD 1602 + I2C:
SCL - A5
SDA - A4
VCC - 5V
GND - GND

DS1302:
VCC - 5V
GND - GND
CLK - D6
DAT - D7
RST - D8

Button
D2                | none
GND(10k resistor) | 5V



*/

BMP180 myBMP(BMP180_ULTRAHIGHRES);
LiquidCrystal_I2C lcd(0x27,16,2); 
iarduino_RTC time(RTC_DS1302,8,6,7); 

int buttonPin = 2;  // Номер пина, к которому подключена кнопка
int buttonState = 0;  // Текущее состояние кнопки
int counter = 0;  // Счетчик нажатий на кнопку

void logo(){ 
  lcd.setCursor(1, 0);  // столбец 1 строка 0
  lcd.print("Meteo Time");
  lcd.setCursor(2, 1);
  lcd.print("v2.0");
  lcd.setCursor(8, 1);  // столбец 4 строка 1
  lcd.print("Display");
  
}

void screenAllSensors(){
  double temp1 = myBMP.getTemperature();
  double pres = myBMP.getSeaLevelPressure(700)* 0.00750062;

  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(temp1); lcd.print(" "); lcd.write(223); lcd.print("C"); 
  lcd.setCursor(0, 1);
  lcd.print("Pres: "); lcd.print(pres); lcd.print("mmHg"); 

}

void screenTemperature(){
  double temp1 = myBMP.getTemperature();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: "); 
  lcd.setCursor(1, 1);
  lcd.print(temp1); lcd.print(" "); lcd.write(223); lcd.print("C"); 

}

void screenPressure(){
  double pres = myBMP.getSeaLevelPressure(700)* 0.00750062;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressure: "); 
  lcd.setCursor(1, 1);
  lcd.print(pres); lcd.print(" mmHg"); 

}


void setup() {
  myBMP.begin();
  
  lcd.init();  // Инициализация экрана
  lcd.backlight();  // Включение подсветки экрана
  logo();  // Вывод начального сообщения на экран
  pinMode(buttonPin, INPUT);  // Настройка пина кнопки на вход

   time.begin();
   //time.settime(45, 20, 16, 16, 4, 23, 1); // 0  сек, 30 мин, 18 часов, 12, июня, 2020, четверг
  
}

unsigned long lastUpdateTime = 0;

void loop() {  
  
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
      counter++;
    if (counter == 1){
      lcd.clear();
      
      lcd.setCursor(0,0);
      lcd.print(time.gettime("d M Y, D"));
      lcd.setCursor(4,1);
      lcd.print(time.gettime("H:i:s"));
      lastUpdateTime = millis(); // сохраняем время последнего обновления времени
    } else if (counter == 2) {
      lcd.clear();
      screenAllSensors();
    } else if (counter == 3) {
      lcd.clear();
      screenTemperature();
    } else if (counter == 4) {
      lcd.clear();
      screenPressure();
    } else if (counter == 5) {
      lcd.clear();
      logo();
      counter = 0; 
    }

    delay(250);
  }
  
  // обновляем время каждую секунду, если кнопка нажата 1 раз
  if (counter == 1 && (millis() - lastUpdateTime) >= 1000) {
    lastUpdateTime = millis();
    lcd.setCursor(4,1);
    lcd.print(time.gettime("H:i:s"));
  }
}
