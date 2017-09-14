#include <LiquidCrystal.h>
#include <math.h>

#define THERMISTORPIN A0 // к какому аналоговому пину подключен термистор
#define THERMISTORNOMINAL 100000 // сопротивление при 25 градусах по Цельсию
#define TEMPERATURENOMINAL 25 // temp. для номинального сопротивления (практически всегда равна 25 C)
#define COUNT_OF_MEASUREMENTS 15 // сколько показаний используем для определения среднего значения
#define BCOEFFICIENT 3950 // бета коэффициент термистора (обычно 3000-4000)
#define SERIESRESISTOR 100000 // сопротивление второго резистора

int measurements[COUNT_OF_MEASUREMENTS];

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); // инициализируем LCD

void setup(void) {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop(void) {
  uint8_t i;

  float averageMeasurement;
  float temperature;
  float resistence;

  // снимаем показания несколько раз с небольшой задержкой между снятием показаний
  for (i = 0; i < COUNT_OF_MEASUREMENTS; i++) {
    measurements[i] = analogRead(THERMISTORPIN);
    delay(10);
  }

  // рассчитываем среднее значение
  averageMeasurement = 0;
  for (i = 0; i < COUNT_OF_MEASUREMENTS; i++) {
    averageMeasurement += measurements[i];
  }

  averageMeasurement /= COUNT_OF_MEASUREMENTS;

  // конвертируем значение в сопротивление
  resistence = 1023 / averageMeasurement - 1;
  resistence = SERIESRESISTOR / resistence;

  // конвертируем значение в температуру
  temperature = resistence / THERMISTORNOMINAL; // (R/Ro)
  temperature = log(temperature); // ln(R/Ro)
  temperature /= BCOEFFICIENT; // 1/B * ln(R/Ro)
  temperature += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)

  temperature = 1.0 / temperature; // инвертируем
  temperature -= 273.15; // конвертируем в градусы по Цельсию

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature is:");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print(" C");

  delay(500);
}
