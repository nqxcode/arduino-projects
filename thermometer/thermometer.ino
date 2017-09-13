#include <LiquidCrystal.h>
#include <math.h>

// к какому аналоговому пину мы подключены

#define THERMISTORPIN A0

// сопротивление при 25 градусах по Цельсию

#define THERMISTORNOMINAL 100000

// temp. для номинального сопротивления (практически всегда равна 25 C)

#define TEMPERATURENOMINAL 25

// сколько показаний используем для определения среднего значения

#define NUMSAMPLES 5

// бета коэффициент термистора (обычно 3000-4000)

#define BCOEFFICIENT 3950

// сопротивление второго резистора

#define SERIESRESISTOR 100000

int samples[NUMSAMPLES];

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); // инициализируем LCD


void setup(void) {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);

  Serial.begin(9600);

}

void loop(void) {
  uint8_t i;

  float average;

  // сводим показания в вектор с небольшой задержкой между снятием показаний

  for (i = 0; i < NUMSAMPLES; i++) {

    samples[i] = analogRead(THERMISTORPIN);

    delay(10);

  }

  // рассчитываем среднее значение

  average = 0;

  for (i = 0; i < NUMSAMPLES; i++) {

    average += samples[i];

  }

  average /= NUMSAMPLES;

  // конвертируем значение в сопротивление

  average = 1023 / average - 1;

  average = SERIESRESISTOR / average;

  float steinhart;

  steinhart = average / THERMISTORNOMINAL; // (R/Ro)

  steinhart = log(steinhart); // ln(R/Ro)

  steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)

  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)

  steinhart = 1.0 / steinhart; // инвертируем

  steinhart -= 273.15; // конвертируем в градусы по Цельсию

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature is:");
  lcd.setCursor(0, 1);
  lcd.print(steinhart);
  lcd.print(" C");

  delay(500);
}

