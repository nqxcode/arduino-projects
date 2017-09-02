int ledPin = 9;

int val = 10;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.parseInt();
  }

 //val = analogRead(0);

  analogWrite(ledPin, val / 4);
}
