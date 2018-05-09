#include <Wire.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Adafruit_BME280 bme;

void setup() {
  delay(300);
  bme.begin(0x76);

  delay(100);
  lcd.init();
  lcd.backlight();
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 133.3;

  double c;

  String temperatureString = String(uint8_t(temperature)) + "," + String(uint8_t(modf(temperature, &c) * 10)) + " " + String((char)223) + "C";
  String humidityString = String(uint8_t(ceil(humidity))) + "%";
  String pressureString = String(int(ceil(pressure))) + "mm";

  lcd.setCursor(0, 0);
  lcd.print(temperatureString);

  lcd.setCursor(12, 0);
  lcd.print(humidityString);

  lcd.setCursor(6, 1);
  lcd.print(pressureString);

  delay(500);
}

