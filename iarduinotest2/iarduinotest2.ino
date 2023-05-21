#include "iarduino_RTC.h"
iarduino_RTC time(RTC_DS1302,8,6,7);       // для модуля DS1307 с i2C

#include "Wire.h"                             // библиотека для устройств I2C 
#include "LiquidCrystal_I2C.h"       // подключаем библиотеку для дисплея
LiquidCrystal_I2C LCD(0x27,16,2);  // присваиваем имя дисплею

void setup() {
   delay(300);
   LCD.init();            // инициализация LCD дисплея
   LCD.backlight();  // включение подсветки дисплея
   time.begin();
   //time.settime(45, 20, 16, 16, 4, 23, 1); // 0  сек, 30 мин, 18 часов, 12, июня, 2020, четверг
}

void loop() {
   // если прошла 1 секунда выводим время на дисплей
   if (millis() % 1000 == 0) {
      LCD.setCursor(0,0);
      LCD.print(time.gettime("d M Y, D"));
      LCD.setCursor(4,1);
      LCD.print(time.gettime("H:i:s"));
      delay(1);
   }
}
