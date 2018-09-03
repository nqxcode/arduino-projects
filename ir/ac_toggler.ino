#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <IRremote.h>
#include <avr/pgmspace.h>

#define minTemperature 24.0 // case when AC turn off
#define maxTemperature 25.0 // Thermal stress, AC turn on

int stateOn = 1;

Adafruit_BME280 bme;

IRsend irsend;
int khz = 38;
const unsigned int signal_turn_on[] PROGMEM = {3520, 1712, 468, 404, 468, 1276, 468, 404, 468, 400, 472, 400, 468, 408, 468, 400, 468, 404, 472, 404, 464, 404, 472, 400, 468, 404, 468, 404, 468, 1276, 468, 400, 472, 404, 468, 380, 492, 404, 468, 404, 468, 404, 468, 404, 468, 1276, 468, 1272, 472, 1276, 468, 404, 464, 404, 472, 1272, 468, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 400, 472, 400, 472, 404, 468, 404, 468, 404, 468, 404, 468, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 468, 408, 468, 400, 468, 404, 472, 400, 472, 400, 468, 408, 464, 404, 468, 404, 468, 380, 492, 404, 468, 384, 488, 1272, 472, 1276, 468, 400, 472, 404, 468, 404, 468, 404, 468, 400, 472, 9996, 3516, 1712, 468, 400, 472, 1272, 472, 400, 472, 400, 472, 400, 472, 404, 468, 404, 464, 408, 464, 380, 496, 400, 472, 376, 492, 404, 468, 404, 468, 1276, 468, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 400, 472, 1252, 492, 1276, 464, 1276, 468, 408, 468, 400, 472, 1272, 472, 400, 468, 400, 476, 380, 488, 408, 464, 408, 468, 396, 476, 400, 468, 404, 468, 404, 468, 400, 472, 380, 492, 404, 468, 404, 468, 1276, 468, 404, 468, 400, 472, 1272, 472, 1252, 492, 1276, 464, 408, 464, 408, 468, 400, 468, 1276, 468, 1276, 468, 1276, 468, 404, 468, 1276, 468, 404, 468, 400, 472, 404, 468, 400, 472, 400, 472, 404, 464, 404, 468, 404, 472, 404, 468, 1272, 472, 1272, 468, 404, 468, 404, 468, 404, 468, 400, 472, 1272, 472, 404, 468, 1276, 468, 404, 468, 404, 468, 1276, 468, 1272, 472, 400, 472, 400, 468, 404, 472, 380, 492, 380, 488, 404, 472, 400, 468, 404, 472, 400, 468, 408, 464, 404, 468, 404, 468, 404, 468, 1276, 468, 1276, 468, 1276, 468, 400, 472, 404, 468, 404, 468, 400, 472, 404, 468, 400, 472, 404, 464, 408, 468, 400, 468, 1276, 468, 1256, 488, 1272, 476, 400, 468, 404, 468, 404, 468, 400, 472, 380, 492, 404, 472, 376, 492, 400, 472, 380, 492, 400, 472, 404, 468, 404, 468, 404, 468, 380, 492, 404, 468, 400, 472, 1272, 472, 400, 468, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 1276, 468, 400, 472, 404, 468, 404, 468, 400, 472, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 400, 472, 404, 468, 400, 468, 404, 472, 400, 468, 404, 472, 380, 492, 1272, 472, 400, 468, 404, 468, 1280, 464, 404, 468, 380, 492, 408, 464, 400, 472};
const unsigned int signal_turn_off[] PROGMEM = {3520, 1708, 468, 384, 492, 1272, 472, 404, 464, 400, 472, 384, 488, 404, 468, 400, 472, 400, 472, 400, 472, 404, 468, 400, 472, 400, 472, 400, 472, 1272, 472, 380, 492, 400, 472, 400, 472, 400, 472, 400, 468, 404, 468, 404, 468, 1276, 468, 1276, 472, 1268, 472, 404, 468, 404, 468, 1272, 472, 400, 476, 396, 472, 400, 472, 380, 492, 400, 468, 404, 472, 400, 472, 400, 472, 400, 468, 404, 468, 404, 468, 404, 472, 400, 468, 404, 468, 384, 488, 404, 468, 404, 468, 400, 472, 380, 492, 404, 468, 400, 472, 400, 472, 400, 472, 400, 472, 400, 468, 404, 472, 400, 472, 400, 472, 400, 472, 400, 472, 1272, 472, 1268, 476, 400, 472, 400, 468, 404, 468, 380, 492, 404, 468, 9996, 3520, 1708, 472, 400, 472, 1272, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 468, 404, 468, 404, 468, 404, 468, 404, 468, 1276, 468, 380, 492, 404, 468, 404, 468, 400, 472, 400, 472, 404, 468, 400, 472, 1272, 472, 1272, 472, 1272, 472, 400, 472, 400, 468, 1276, 468, 400, 476, 396, 472, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 404, 468, 400, 472, 400, 472, 400, 472, 404, 468, 400, 472, 400, 472, 400, 468, 404, 472, 1272, 472, 1272, 472, 1272, 468, 404, 472, 396, 476, 400, 468, 1272, 472, 1276, 468, 1272, 472, 400, 472, 1272, 472, 400, 472, 400, 472, 400, 472, 400, 472, 380, 492, 380, 492, 400, 468, 404, 472, 400, 472, 1272, 468, 1276, 468, 404, 468, 400, 472, 380, 492, 400, 472, 1272, 472, 404, 468, 1272, 472, 400, 472, 400, 472, 1272, 472, 1272, 472, 400, 472, 400, 472, 400, 468, 404, 468, 404, 472, 396, 472, 400, 472, 404, 468, 404, 468, 400, 472, 404, 468, 400, 472, 400, 472, 1276, 468, 1272, 472, 1272, 472, 400, 468, 404, 472, 400, 472, 400, 468, 404, 468, 404, 468, 404, 472, 400, 468, 404, 472, 1248, 492, 1276, 468, 1272, 472, 380, 492, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 400, 468, 404, 472, 400, 468, 404, 468, 404, 472, 1252, 488, 404, 468, 404, 468, 400, 472, 384, 488, 400, 472, 404, 468, 1276, 468, 400, 472, 400, 472, 400, 472, 400, 472, 400, 472, 376, 492, 404, 472, 400, 468, 404, 468, 404, 468, 404, 468, 404, 472, 400, 468, 400, 472, 404, 472, 400, 468, 400, 472, 404, 468, 400, 472, 1272, 472, 404, 468, 404, 468, 400, 472, 400, 472};

void setup() {
  bme.begin(0x76);
  delay(100);

  Serial.begin(9600);
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 133.3;

  toggleAcPower(temperature, humidity);
  delay(3000);
}

void toggleAcPower(float temperature, float humidity)
{
  Serial.println(temperature);
  
  if (temperature <= minTemperature) {
    turnOffAC();
    return;
  }
  
  if (temperature >= maxTemperature) {
    turnOnAC();
    return;
  }
}

void turnOnAC() {
  int size = sizeof(signal_turn_on) / sizeof(int);
  unsigned int buffer[size];

  for (int i = 0; i < size; i++) {
    buffer[i] = pgm_read_dword(&signal_turn_on[i]);
  }

  irsend.sendRaw(buffer, size, khz);
}

void turnOffAC() {
  int size = sizeof(signal_turn_off) / sizeof(int);
  unsigned int buffer[size];

  for (int i = 0; i < size; i++) {
    buffer[i] = pgm_read_dword(&signal_turn_off[i]);
  }

  irsend.sendRaw(buffer, size, khz);
}
