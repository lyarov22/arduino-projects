// Пин, к которому подключено реле
const int relayPin = 2;

// Время работы реле в миллисекундах
const unsigned long relayTime = 90000; // 120 секунд

// Интервал между включениями реле в минутах
const unsigned long interval = 60; // каждые 60 минут

// Переменная для хранения времени последнего включения реле
unsigned long previousMillis = 0;

// Функция для включения реле на заданное время
void activateRelay() {
  digitalWrite(relayPin, HIGH); // Включаем реле
  delay(relayTime); // Ждем заданное время
  digitalWrite(relayPin, LOW); // Выключаем реле
}

void setup() {
  // Устанавливаем пин реле в режим OUTPUT
  pinMode(relayPin, OUTPUT);

  activateRelay();
}

void loop() {
  // Получаем текущее время
  unsigned long currentMillis = millis();

  // Проверяем, прошло ли достаточно времени с момента последнего включения реле
  if (currentMillis - previousMillis >= interval * 6000) {
    // Если прошло достаточно времени, включаем реле
    activateRelay();

    // Запоминаем время последнего включения реле
    previousMillis = currentMillis;
  }
}
