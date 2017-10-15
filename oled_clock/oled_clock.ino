#include <OLED_I2C.h>
#include <iarduino_RTC.h>

iarduino_RTC time(RTC_DS1302, 10, 13, 12);

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
}
void loop() {
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
  //myOLED.print((char*)"/", 51, 12);
  myOLED.print(i, 75, 12);

  myOLED.setFont(SmallFont);
  myOLED.print(date, CENTER, 57);

  myOLED.setFont(SmallFont);
  myOLED.print(s, CENTER, 30);


  myOLED.update();
  delay(500);
  myOLED.setFont(MegaNumbers);                     // Скрытие двоеточия
  //myOLED.print((char*)"-", 51, 12);
  myOLED.update();
  delay(500);

  Serial.println(time.gettime("d-m-Y, H:i:s, D"));
  Serial.println(dayOfWeek);
  Serial.println(time.gettime("w"));
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

