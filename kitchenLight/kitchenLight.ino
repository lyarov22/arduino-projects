const int mic = 2; // KY-038
const int relay = 3; // RELAY 5V 

boolean status;
void setup()
{
  pinMode(mic, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);

  status = false;
  digitalWrite(relay, HIGH);
}
 
void loop()
{
  Serial.println(digitalRead(mic));
  if (digitalRead(mic)) {
    status =! status;
    digitalWrite(relay, status);
    delay(20);
  }

}
