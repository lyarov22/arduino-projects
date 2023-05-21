const int  buttonPin = 2;    // кнопка на выводе 2
const int ledPin = 13;       // светодиод на выводе 13

int buttonPushCounter = 0;   // счётчик нажатия кнопки
int buttonState = 0;         // текущее состояние кнопки
int lastButtonState = 0;     // предыдущее состояние кнопки

void setup() {
  // устанавливаем режим ввода для кнопки
  pinMode(buttonPin, INPUT);
  // устанавливаем режим вывода для светодиода
  pinMode(ledPin, OUTPUT);
  // включаем последовательную передачу данных
  Serial.begin(9600);
}

void loop() {
  // считываем показания с вывода кнопки
  buttonState = digitalRead(buttonPin);

  // сравниваем состояние с предыдущим состоянием
  if (buttonState != lastButtonState) {
    // если состояние изменилось, увеличиваем счётчик
    if (buttonState == HIGH) {
      // если текущее состояние HIGH, значит кнопка включена
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // если текущее состояние LOW, значит кнопка выключена
      Serial.println("off");
    }
    // небольшая задержка для устранения эффекта дребезга
    delay(50);
  }
  // сохраняем текущее состояние как последнее состояние для следующего раза
  lastButtonState = buttonState;

  // включаем светодиод при каждом четвёртом нажатии, проверяя деление по остатку счётчика нажатий
  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else{
    
  }
}
