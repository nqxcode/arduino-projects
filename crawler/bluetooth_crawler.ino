<<<<<<< HEAD
#include <SoftwareSerial.h>
#include "crawler.h"


// Connect the HC-06 TX to the Arduino RX on pin 2.
// Connect the HC-06 RX to the Arduino TX on pin 3 through a voltage divider.
SoftwareSerial BTserial(2, 3); // RX | TX

Crawler crawler(10, 12, 11, 13); // E1, M1, E2, M2

String commandString = "";

void setup()
{
  Serial.begin(9600);
  BTserial.begin(9600);
  crawler.begin();

  commandString.reserve(200);
=======
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
>>>>>>> 5c059c02adfa68637972e711d902512e4950c7ba
}

void loop()
{
<<<<<<< HEAD
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  while (BTserial.available())
  {
    char c = BTserial.read();

    if (c != ';') {
      commandString += c;
      continue;
    }
    execute(commandString);
    commandString = "";
  }
}

void execute(String commandString)
{
  Serial.print("Input command: ");
  Serial.println(commandString);

  if (commandString == "right") {
    crawler.rotate(0);

  } else if (commandString == "left") {
    crawler.rotate(1);

  } else if (commandString == "go") {
    crawler.go();

  } else if (commandString == "back") {
    crawler.back();

  } else if (commandString == "wait") {
    crawler.wait();

  } else {
    Serial.println("Incorrect command!");
=======
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
>>>>>>> 5c059c02adfa68637972e711d902512e4950c7ba
  }
}

