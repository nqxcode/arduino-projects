#include "crawler.h"

Crawler crawler;

void setup()
{
  Serial.begin (9600);
  crawler.begin();

}

void loop()
{
  delay(1000);
  crawler.go();
  delay(1000);
}
