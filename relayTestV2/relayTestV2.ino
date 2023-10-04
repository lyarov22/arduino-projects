const int relayPin = 3;
const unsigned long relayTime = 120000; // 120 секунд
const unsigned long interval = 3600000; // каждый час в миллисекундах
unsigned long previousMillis = 0;

void activateRelay() {
  digitalWrite(relayPin, HIGH); // Включаем реле
  delay(relayTime); // Ждем заданное время
  digitalWrite(relayPin, LOW); // Выключаем реле
}

void setup() {
  pinMode(relayPin, OUTPUT);
  activateRelay(); // Включаем реле при старте
  previousMillis = millis(); // Запоминаем текущее время
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    activateRelay();
    previousMillis = currentMillis;
  }
}
