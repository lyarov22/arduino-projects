#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Адрес экрана и его размер

int buttonPin = 2;  // Номер пина, к которому подключена кнопка
int buttonState = 0;  // Текущее состояние кнопки
int counter = 0;  // Счетчик нажатий на кнопку

void setup() {
  lcd.init();  // Инициализация экрана
  lcd.backlight();  // Включение подсветки экрана
  lcd.print("Hello");  // Вывод начального сообщения на экран
  pinMode(buttonPin, INPUT);  // Настройка пина кнопки на вход
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Считываем состояние кнопки
  if (buttonState == HIGH) {  // Если кнопка нажата
    counter++;  // Увеличиваем счетчик нажатий
    if (counter == 1) {  // Если это первое нажатие
      lcd.clear();  // Очищаем экран
      lcd.print("Hello1");  // Выводим сообщение на экран
    } else if (counter == 2) {  // Если это второе нажатие
      lcd.clear();  // Очищаем экран
      lcd.print("Hello2");  // Выводим сообщение на экран
    } else if (counter == 3) {  // Если это третье нажатие
      lcd.clear();  // Очищаем экран
      lcd.print("Hello1");  // Выводим сообщение на экран
      counter = 0;  // Сбрасываем счетчик нажатий
    }
    delay(250);  // Задержка для предотвращения дребезга контактов кнопки
  }
}
