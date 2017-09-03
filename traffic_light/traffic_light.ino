// Led pin 3...7

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int val = analogRead(0);

  int pin = map(val, 0, 1023, 2, 7);

  Serial.println(pin);

  if (pin > 2) {
    digitalWrite(pin, HIGH);
    delay(20);
    digitalWrite(pin, LOW);
  }
}

