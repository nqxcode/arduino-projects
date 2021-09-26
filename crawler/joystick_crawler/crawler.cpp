/***************************************************
  This is a library for crawler
 ****************************************************/

#include <Arduino.h>
#include "crawler.h"

Crawler::Crawler(unsigned int e1, unsigned int m1, unsigned int e2, unsigned int m2, unsigned int buzzer)
  : E1(e1), M1(m1), E2(e2), M2(m2), Buzzer(buzzer) {    
}

void Crawler::begin(void) {
  pinMode(this->M1, OUTPUT);
  pinMode(this->M2, OUTPUT);
  pinMode(this->Buzzer, OUTPUT);
}

void Crawler::debug(String message)
{
  if (debugMode) {
    Serial.print("[Crawler debug mode]: ");
    Serial.println(message);
  }
}

void Crawler::run(Crawler::Direction direction)
{
  switch (direction) {
    case Crawler::Direction::forward:
      this->debug("forward");

      digitalWrite(M1, HIGH);
      digitalWrite(M2, LOW);
      break;

    case Crawler::Direction::backward:
      this->debug("backward");

      digitalWrite(M1, LOW);
      digitalWrite(M2, HIGH);
      break;

    case Crawler::Direction::left_rotation:
      this->debug("left rotation");

      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      break;

    case Crawler::Direction::right_rotation:
      this->debug("right rotation");

      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
      break;

    default:
      this->debug("Incorrect direction");
      return;
  }

  this->refreshSpeed();
}

void Crawler::speed(unsigned int leftSpeed, unsigned int rightSpeed)
{
  this->debug(String("left speed: ") + String(leftSpeed));
  this->debug(String("right speed: ") + String(rightSpeed));

  this->leftSpeed = leftSpeed;
  this->rightSpeed = rightSpeed;

  this->refreshSpeed();
}

void Crawler::refreshSpeed(void)
{
  analogWrite(E2, this->rightSpeed);
  analogWrite(E1, this->leftSpeed);
}

void Crawler::buzz(void)
{
  tone (this->Buzzer, 500);
  delay(100);
  tone(this->Buzzer, 1000);
  delay(100);
  noTone(this->Buzzer);
}

void Crawler::enableDebugMode(void)
{
 this->debugMode = true; 
}
