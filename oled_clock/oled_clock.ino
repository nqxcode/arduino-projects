#include <OLED_I2C.h>
#include <iarduino_RTC.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

iarduino_RTC time(RTC_DS1302, 7, 9, 8);

OneWire oneWire(10);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

OLED  myOLED(SDA, SCL, 8);

extern uint8_t MegaNumbers[];
extern uint8_t SmallFont[];
extern uint8_t RusFont[];

int i = 0;

void setup() {
  delay(300);
  Serial.begin(9600);
  time.begin(); // time.settime(58, 50, 19, 15, 10, 17, 7);

  myOLED.begin();

  sensors.begin();
  sensors.getAddress(insideThermometer, 0);
  sensors.setResolution(insideThermometer, 11);
}
void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(insideThermometer);
  double c;
  String tempCString = String(int(tempC)) + "," + String(int(modf(tempC, &c) * 100)) + "  C";

  myOLED.clrScr();

  String date = time.gettime("d.m.Y");
  String H = time.gettime("H");
  String i = time.gettime("i");
  String s = time.gettime("s");

  String dayOfWeek = getDayOfWeek(atoi(time.gettime("w")));

  myOLED.setFont(RusFont);
  myOLED.print(dayOfWeek, CENTER, 0);

  myOLED.setFont(MegaNumbers);
  myOLED.print(H, 4, 12);
  myOLED.print(i, 75, 12);

  myOLED.setFont(SmallFont);
  myOLED.print(date, LEFT, 57);

  myOLED.setFont(SmallFont);
  myOLED.print(s, CENTER, 30);

  myOLED.setFont(SmallFont);
  myOLED.print(tempCString, RIGHT, 57);

  myOLED.setFont(SmallFont);
  myOLED.print((char*)"o", 115, 55);

  myOLED.update();
  delay(100);
}

String getDayOfWeek(int dayOfWeek)
{
  switch (dayOfWeek) {
    case 0:
      return "Djcrhtctymt";
    case 1:
      return "Gjytltkmybr";
    case 2:
      return "Dnjhybr";
    case 3:
      return "Chtlf";
    case 4:
      return "Xtndthu";
    case 5:
      return "Gznybwf";
    case 6:
      return "Ce,,jnf";
  }
}

