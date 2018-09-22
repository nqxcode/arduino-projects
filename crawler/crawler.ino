int E1 = 10;
int M1 = 12;
int E2 = 11;
int M2 = 13;

int echoPin = 9;
int trigPin = 8;

int MIN_DISTANCE = 80; // в сантиметрах

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

void go()
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 255);
  analogWrite(E2, 255);
}

void back()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 200);
  analogWrite(E2, 200);
}

void rotate(int direction)
{
  if (direction == 1) {
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
  } else {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
  }
  analogWrite(E1, 200);
  analogWrite(E2, 200);
}

void wait()
{
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}

void setup()
{
  Serial.begin (9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  int waitFirst = true;
  int direction = 0;
  
  while (true) {
    int distance = getDistance();
    Serial.print(distance);
    Serial.println(" cm");
    
    if (distance > MIN_DISTANCE) {
      go();
      break;
      
    } else {
      wait();
      delay(500);
      rotate(direction);
      delay(200);
    }
  }
}
