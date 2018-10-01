#include <SoftwareSerial.h>
#include "crawler.h"
#include "controller.h"

SoftwareSerial BTserial(2, 3); // RX | TX
Crawler crawler(10, 12, 11, 13); // E1, M1, E2, M2
Controller controller;

String commandString = "";

void setup()
{
  Serial.begin(9600);
  BTserial.begin(9600);
  crawler.begin();
  commandString.reserve(200);
}


unsigned int xAxis = 512;
unsigned int yAxis = 512;

void loop()
{
  while (BTserial.available())
  {
    char c = BTserial.read();

    if (c != '\n') {
      commandString += c;
      continue;
    }

    if (commandString.startsWith("S")) {
      yAxis = commandString.substring(1).toInt();
      if (yAxis > 1023) {
        yAxis = 1023;
      }
    }

    if (commandString.startsWith("D")) {
      xAxis = commandString.substring(1).toInt();
      if (xAxis > 1023) {
        xAxis = 1023;
      }
    }

    commandString = "";
  }

  controller.setAxes(xAxis, yAxis);

  Crawler::Direction direction = controller.getDirection();
  unsigned int leftSpeed = controller.getLeftSpeed();
  unsigned int rightSpeed = controller.getRightSpeed();

  Serial.print("Left speed: ");
  Serial.print(leftSpeed);
  Serial.println();
  Serial.print("Right speed: ");
  Serial.print(rightSpeed);
  Serial.println();

  crawler.speed(leftSpeed, rightSpeed);
  crawler.run(direction);
}
