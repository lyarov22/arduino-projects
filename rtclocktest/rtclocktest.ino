#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

// Подключение датчика реального времени
DS1302 rtc(2, 3, 4); // RST, DAT, CLK

// Подключение дисплея 1602 I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Инициализация датчика реального времени
  rtc.halt(false);
  rtc.writeProtect(false);

  
  // Инициализация дисплея 1602 I2C
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Чтение времени из датчика реального времени
  DateTime now = rtc.now();
  
  // Вывод времени на дисплей
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  if (now.hour() < 10) {
    lcd.print("0");
  }
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.second());
  
  delay(1000);
}
