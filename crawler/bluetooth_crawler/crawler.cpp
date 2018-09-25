/***************************************************
  This is a library for crawler
 ****************************************************/

#include <Arduino.h>
#include "crawler.h"

Crawler::Crawler(unsigned int e1, unsigned int m1, unsigned int e2, unsigned int m2, unsigned int _speed = 150)
  : E1(e1), M1(m1), E2(e2), M2(m2), _speed(_speed) {
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

    case Crawler::Direction::left:
      this->debug("left rotation");

      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      break;

    case Crawler::Direction::right:
      this->debug("right rotation");

      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
      break;

    default:
      this->debug("Incorrect direction");
      return;
  }

  analogWrite(E1, this->_speed);
  analogWrite(E2, this->_speed);

  this->started = true;
}

void Crawler::stop(void)
{
  this->debug("stop");

  analogWrite(E1, 0);
  analogWrite(E2, 0);

  this->started = false;
}

void Crawler::speed(unsigned int _speed)
{
  this->debug(String("speed: ") + String(_speed));

  this->_speed = _speed;

  if (this->started) {
    analogWrite(E1, this->_speed);
    analogWrite(E2, this->_speed);
  }
}

