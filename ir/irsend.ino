#include <IRremote.h>
IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  irsend.sendNEC(0x807F18E7, 32);
  delay(3000);
}
