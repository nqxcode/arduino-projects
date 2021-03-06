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
}

void loop()
{
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  while (BTserial.available())
  {
    char c = BTserial.read();

    if (c != ';') { // TODO change delimiter to \n or \r
      commandString += c;
      continue;
    }
    execute(commandString);
    commandString = "";
  }
}

void execute(String commandString)
{
  if (commandString == "right") {
    crawler.run(Crawler::Direction::right);

  } else if (commandString == "left") {
    crawler.run(Crawler::Direction::left);

  } else if (commandString == "forward") {
    crawler.run(Crawler::Direction::forward);

  } else if (commandString == "backward") {
    crawler.run(Crawler::Direction::backward);

  } else if (commandString == "stop") {
    crawler.stop();

  } else if (commandString.startsWith("speed:")) {
    unsigned int _speed = commandString.substring(6).toInt();

    crawler.speed(_speed);

  } else {
    Serial.println("Incorrect command!");
  }
}
