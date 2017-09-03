int echoPin = 9;
int trigPin = 8;

int getDistance()
{
  int duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  return duration / 58;
}

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  int cm = getDistance();
  Serial.print(cm);
  Serial.println(" cm");
  delay(100);
}
