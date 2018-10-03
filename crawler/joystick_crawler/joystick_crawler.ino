#include <SoftwareSerial.h>
#include "crawler.h"
#include "controller.h"

SoftwareSerial BTserial(2, 3); // RX | TX
Crawler crawler(10, 12, 11, 13, 4); // E1, M1, E2, M2
Controller controller;


unsigned int xAxis = 512;
unsigned int yAxis = 512;
String command = "";

void setup()
{
  Serial.begin(9600);
  BTserial.begin(9600);
  crawler.begin();
  command.reserve(200);
}

void loop()
{
  while (BTserial.available())
  {
    char c = BTserial.read();

    if (c != '\n') {
      command += c;
      continue;
    }

    if (command.startsWith("S")) {
      yAxis = command.substring(1).toInt();
      if (yAxis > 1023) {
        yAxis = 1023;
      }
    }

    if (command.startsWith("D")) {
      xAxis = command.substring(1).toInt();
      if (xAxis > 1023) {
        xAxis = 1023;
      }
    }

    if (command.startsWith("B1")) {
      crawler.buzz();
    }

    command = "";
  }

  controller.setAxes(xAxis, yAxis);

  Crawler::Direction direction = controller.getDirection();
  unsigned int leftSpeed = controller.getLeftSpeed();
  unsigned int rightSpeed = controller.getRightSpeed();


  crawler.speed(leftSpeed, rightSpeed);
  crawler.run(direction);
}
