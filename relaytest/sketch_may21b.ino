#define RELAY_IN 3
void setup() {
  // пин реле как выход
  pinMode(RELAY_IN, OUTPUT);
}
void loop() {
  // "мигаем"
  digitalWrite(RELAY_IN, HIGH);
  delay(1000);
  digitalWrite(RELAY_IN, LOW);
  delay(1000);
}
