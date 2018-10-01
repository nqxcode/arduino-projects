/***************************************************
  This is a library for controller
 ****************************************************/

#include <Arduino.h>
#include "crawler.h"
#include "controller.h"

Controller::Controller(void) {
}

void Controller::setAxes(unsigned int xAxis, unsigned int yAxis) {
  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    // Set motors backward
    this->direction = Crawler::Direction::backward;

    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    this->leftSpeed = map(yAxis, 470, 0, 0, 255);
    this->rightSpeed = map(yAxis, 470, 0, 0, 255);

  }
  else if (yAxis > 550) {
    // Set motors forward
    this->direction = Crawler::Direction::forward;

    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    this->leftSpeed = map(yAxis, 550, 1023, 0, 255);
    this->rightSpeed = map(yAxis, 550, 1023, 0, 255);

  }
  // If joystick stays in middle the motors are not moving
  else {
    this->leftSpeed = 0;
    this->rightSpeed = 0;
  }

  // X-axis used for left and right control
  if (xAxis < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);

    // Move to left - decrease left motor speed, increase right motor speed
    this->leftSpeed = this->leftSpeed - xMapped;
    this->rightSpeed = this->rightSpeed + xMapped;

    // Confine the range from 0 to 255
    if (this->leftSpeed < 0) {
      this->leftSpeed = 0;
    }
    if (this->rightSpeed > 255) {
      this->rightSpeed = 255;
    }
  }
  if (xAxis > 550) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    this->leftSpeed = this->leftSpeed + xMapped;
    this->rightSpeed = this->rightSpeed - xMapped;
    // Confine the range from 0 to 255
    if (this->leftSpeed > 255) {
      this->leftSpeed = 255;
    }
    if (this->rightSpeed < 0) {
      this->rightSpeed = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (this->leftSpeed < 70) {
    this->leftSpeed = 0;
  }
  if (this->rightSpeed < 70) {
    this->rightSpeed = 0;
  }
}

Crawler::Direction Controller::getDirection() {
  return this->direction;
}

unsigned int Controller::getLeftSpeed() {
  return this->leftSpeed;
}

unsigned int Controller::getRightSpeed() {
  return this->rightSpeed;
}
