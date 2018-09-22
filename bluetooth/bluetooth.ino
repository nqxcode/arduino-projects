#include <SoftwareSerial.h>

// Connect the HC-06 TX to the Arduino RX on pin 2.
// Connect the HC-06 RX to the Arduino TX on pin 3 through a voltage divider.
SoftwareSerial BTserial(2, 3); // RX | TX

String commandString = "";

void setup()
{
  Serial.begin(9600);

  // HC-06 default serial speed is 9600
  BTserial.begin(9600);

  commandString.reserve(200);
}

void loop()
{
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  while (BTserial.available())
  {
    char c = BTserial.read();

    if (c != ';') {
      commandString += c;
      continue;
    }

    Serial.println(commandString);
    commandString = "";
    
    Serial.println("-----command complete-------");
  }
}
