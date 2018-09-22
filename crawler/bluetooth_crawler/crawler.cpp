/***************************************************
  This is a library for crawler
 ****************************************************/

#include "crawler.h"
#include <Arduino.h>

Crawler::Crawler(unsigned int e1, unsigned int m1, unsigned int e2, unsigned int m2)
  : E1(e1), M1(m1), E2(e2), M2(m2) {

}

void Crawler::debug(char* message)
{
  Serial.print("[Crawler debug mode]: ");
  Serial.println(message);
}

void Crawler::begin(void) {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void Crawler::go(void)
{
  this->debug("go");

  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 255);
  analogWrite(E2, 255);
}

void Crawler::back(void)
{
  this->debug("back");

  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 200);
  analogWrite(E2, 200);
}

void Crawler::rotate(int direction)
{
  if (direction == 1) {
    this->debug("rotate left");

    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);

  } else {
    this->debug("rotate right");

    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
  }

  analogWrite(E1, 200);
  analogWrite(E2, 200);
}

void Crawler::wait(void)
{
  this->debug("wait");

  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
