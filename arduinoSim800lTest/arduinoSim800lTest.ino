#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3);        // 8 - RX Arduino (TX SIM800L), 9 - TX Arduino (RX SIM800L)
void setup() {
  delay(3000);
  Serial.begin(9600);             
  Serial.println("Start!");
  SIM800.begin(9600);
  delay(3000);             
  SIM800.println("AT");
}

void loop() {
  if (SIM800.available())         
    Serial.write(SIM800.read()); 
  if (Serial.available())         
    SIM800.write(Serial.read()); 
}
