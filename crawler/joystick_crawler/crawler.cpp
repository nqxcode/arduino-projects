/***************************************************
  This is a library for crawler
 ****************************************************/

#include <Arduino.h>
#include "crawler.h"

Crawler::Crawler(unsigned int e1, unsigned int m1, unsigned int e2, unsigned int m2)
  : E1(e1), M1(m1), E2(e2), M2(m2) {
}

void Crawler::begin(void) {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void Crawler::debug(String message)
{
  Serial.print("[Crawler debug mode]: ");
  Serial.println(message);
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

    default:
      this->debug("Incorrect direction");
      return;
  }

  analogWrite(E1, this->rightSpeed);
  analogWrite(E2, this->leftSpeed);
}

void Crawler::speed(unsigned int leftSpeed, unsigned int rightSpeed)
{
  this->debug(String("left speed: ") + String(leftSpeed));
  this->debug(String("right speed: ") + String(rightSpeed));

  this->leftSpeed = leftSpeed;
  this->rightSpeed = rightSpeed;

  analogWrite(E1, this->rightSpeed);
  analogWrite(E2, this->leftSpeed);
}
