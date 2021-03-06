#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <OLED_I2C.h>
#include <iarduino_RTC.h>

#define melodyPin 3
#define maxTHI 70.5 // >72 Thermal stress

iarduino_RTC time(RTC_DS1302, 7, 9, 8);

OLED  myOLED(SDA, SCL, 8);

Adafruit_BME280 bme;

extern uint8_t MegaNumbers[];
extern uint8_t SmallFont[];
extern uint8_t RusFont[];

void setup() {
  delay(300);
  time.begin(); // time.settime(00, 20, 01, 23, 11, 17, 4);

  bme.begin(0x76);
  delay(100);

  myOLED.begin();
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 133.3;

  double c;

  String temperatureString = String(uint8_t(temperature)) + "," + String(uint8_t(modf(temperature, &c) * 10)) + "  C";
  String humidityString = String(uint8_t(ceil(humidity))) + "%";
  String pressureString = String(int(ceil(pressure))) + "mm";

  myOLED.clrScr();

  String date = time.gettime("d.m.Y");
  String H = time.gettime("H");
  String i = time.gettime("i");
  String s = time.gettime("s");

  String dayOfWeek = getDayOfWeek(atoi(time.gettime("w")));

  myOLED.setFont(RusFont);
  myOLED.print(dayOfWeek, LEFT, 0);

  myOLED.setFont(MegaNumbers);
  myOLED.print(H, 4, 12);
  myOLED.print(i, 75, 12);

  myOLED.setFont(SmallFont);
  myOLED.print(date, RIGHT, 0);

  myOLED.setFont(SmallFont);
  myOLED.print(s, CENTER, 30);

  myOLED.setFont(SmallFont);
  myOLED.print(temperatureString, RIGHT, 57);

  myOLED.setFont(SmallFont);
  myOLED.print((char*)"o", 115, 55);

  myOLED.setFont(SmallFont);
  myOLED.print(humidityString, CENTER, 57);

  myOLED.setFont(SmallFont);
  myOLED.print(pressureString, LEFT, 57);

  myOLED.update();
  delay(100);

  notifyOfHighTemperature(temperature, humidity);
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

float getTHI(float temperature, float humidity)
{
  float THI = (1.8 * temperature + 32) - ((0.55 - 0.0055 * humidity) * (1.8 * temperature - 26));
  
  return THI;
}

void notifyOfHighTemperature(float temperature, float humidity)
{
  if (getTHI(temperature, humidity) < maxTHI) {
    return;
  }

  int second = String(time.gettime("s")).toInt();

  if (0 == second) {
    for (int i; i < 3; i++) {
      tone(melodyPin, 220, 157);
      delay(100);
      noTone(melodyPin);
      delay(50);
    }
  }

  delay(1000);
}
