#include "crawler.h"
#include "controller.h"

Crawler crawler(10, 12, 11, 13); // E1, M1, E2, M2
Controller controller;

void setup()
{
  Serial.begin(9600);
  crawler.begin();
}

void loop()
{
  unsigned int xAxis = analogRead(A0); // Read Joysticks X-axis
  unsigned int yAxis = analogRead(A1); // Read Joysticks Y-axis
  
  controller.setAxes(xAxis, yAxis);

  Crawler::Direction direction = controller.getDirection();
  unsigned int leftSpeed = controller.getLeftSpeed();
  unsigned int rightSpeed = controller.getRightSpeed();

  crawler.speed(leftSpeed, rightSpeed);
  crawler.run(direction);
}
