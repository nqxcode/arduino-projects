#include <LiquidCrystal.h>
#include <math.h>

#define THERMISTOR_PIN A0 // к какому аналоговому пину подключен термистор
#define THERMISTOR_NOMINAL 100000 // сопротивление при 25 градусах по Цельсию
#define TEMPERATURE_NOMINAL 25 // температура для номинального сопротивления (практически всегда равна 25 C)
#define COUNT_OF_MEASUREMENTS 15 // сколько показаний используем для определения среднего значения
#define B_COEFFICIENT 3100 // бета коэффициент термистора (обычно 3000-4000)
#define SERIES_RESISTOR 100000 // сопротивление второго резистора

int measurements[COUNT_OF_MEASUREMENTS];

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); // инициализируем LCD

byte p_rus[8] =
{
  B00000,
  B00000,
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000,
};

byte r_rus[8] =
{
  B00000,
  B00000,
  B11111,
  B10001,
  B10001,
  B11110,
  B10000,
  B00000,
};

byte t_rus[8] =
{
  B00000,
  B00000,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000,
};

byte m_rus[8] =
{
  B00000,
  B00000,
  B11011,
  B10101,
  B10101,
  B10001,
  B10001,
  B00000,
};
byte degree_symbol[8] =
{
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setup(void) {
  lcd.createChar(1, p_rus);
  lcd.createChar(2, r_rus);
  lcd.createChar(3, t_rus);
  lcd.createChar(4, m_rus);
  lcd.createChar(5, degree_symbol);

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
    measurements[i] = analogRead(THERMISTOR_PIN);
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
  resistence = SERIES_RESISTOR / resistence;

  // конвертируем значение в температуру
  temperature = resistence / THERMISTOR_NOMINAL; // (R/Ro)
  temperature = log(temperature); // ln(R/Ro)
  temperature /= B_COEFFICIENT; // 1/B * ln(R/Ro)
  temperature += 1.0 / (TEMPERATURE_NOMINAL + 273.15); // + (1/To)

  temperature = 1.0 / temperature; // инвертируем
  temperature -= 273.15; // конвертируем в градусы по Цельсию

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Te\4\1e\2a\3y\2a:");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print(" \5C");

  delay(500);
}
