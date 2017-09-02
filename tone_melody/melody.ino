#include "pitches.h"

#define melodyPin 3

float tempo = 190; // ~ beat per minute

int threshold = 100;

int melody[] = {
  NOTE_D6, NOTE_D6, 0, NOTE_FS6, NOTE_DS6, NOTE_D6,
  NOTE_FS6, NOTE_FS6, 0, NOTE_A6, NOTE_G6, NOTE_FS6,
  NOTE_G6, NOTE_G6, 0, NOTE_AS6, NOTE_A6, NOTE_G6,
  NOTE_FS6, NOTE_DS6, NOTE_D6,

  NOTE_D6, NOTE_D6, 0, NOTE_FS6, NOTE_DS6, NOTE_D6,
  NOTE_FS6, NOTE_FS6, 0, NOTE_A6, NOTE_G6, NOTE_FS6,
  NOTE_G6, NOTE_G6, 0, NOTE_AS6, NOTE_A6, NOTE_G6,
  NOTE_FS6, NOTE_DS6, NOTE_D6,

  NOTE_FS6, NOTE_FS6, NOTE_DS6, NOTE_D6, NOTE_D6, NOTE_D6,
  NOTE_DS6, NOTE_DS6, NOTE_D6, NOTE_C6, NOTE_C6, NOTE_C6,
  NOTE_C6, NOTE_DS6, NOTE_D6, NOTE_C6, NOTE_G6,
  NOTE_FS6, NOTE_DS6, NOTE_D6,

  NOTE_FS6, NOTE_FS6, NOTE_DS6, NOTE_D6, NOTE_D6, NOTE_D6,
  NOTE_DS6, NOTE_DS6, NOTE_D6, NOTE_C6, NOTE_C6, NOTE_C6,
  NOTE_C6, NOTE_DS6, NOTE_D6, NOTE_C6, NOTE_G6,
  NOTE_FS6, NOTE_DS6, NOTE_D6,

  NOTE_G6, NOTE_G6,
  NOTE_G6, NOTE_G6, NOTE_G6, NOTE_G6,

  NOTE_G6, NOTE_G6, NOTE_AS6, NOTE_A6, NOTE_G6, NOTE_AS6, NOTE_A6, NOTE_G6,
  NOTE_G6, NOTE_G6, NOTE_AS6, NOTE_A6, NOTE_G6, NOTE_AS6, NOTE_A6, NOTE_G6,

  NOTE_A6, NOTE_A6, NOTE_C6, NOTE_AS6, NOTE_A6, NOTE_C6, NOTE_AS6, NOTE_A6,
  NOTE_A6, NOTE_A6, NOTE_C6, NOTE_AS6, NOTE_A6, NOTE_C6, NOTE_AS6, NOTE_A6,

  NOTE_A6, NOTE_A6, NOTE_D7, 0,
  NOTE_A6, NOTE_A6, NOTE_D7, 0,

  NOTE_D6, NOTE_D6, NOTE_AS6, NOTE_A6, NOTE_G6, NOTE_FS6,

  NOTE_G6,

};

int noteDurations[] = {
  4, 4, 8, 8, 8, 8,
  4, 4, 8, 8, 8, 8,
  4, 4, 8, 8, 8, 8,
  4, 4, 2,

  4, 4, 8, 8, 8, 8,
  4, 4, 8, 8, 8, 8,
  4, 4, 8, 8, 8, 8,
  4, 4, 2,

  8, 4, 8, 8, 8, 4,
  8, 4, 8, 8, 8, 4,
  4, 8, 8, 4, 4,
  4, 4, 2,

  8, 4, 8, 8, 8, 4,
  8, 4, 8, 8, 8, 4,
  4, 8, 8, 4, 4,
  4, 4, 2,

  2, 2,
  4, 4, 4, 4,

  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  8, 8, 2, 4,
  8, 8, 2, 4,

  4, 4, 8, 8, 8, 8,
  1,
};

float getCurrentTempo()
{
  static float currentTempo;
  if (Serial.available() > 0) {
    currentTempo = Serial.parseFloat();
  }

  if (currentTempo == 0) {
    currentTempo = tempo;
  }

  return currentTempo;
}

void setup() //процедура setup
{

  pinMode(13, OUTPUT); //указываем, что светодиод - выход
  pinMode(3, OUTPUT); //указываем, что светодиод - выход
  Serial.begin(9600);

}

void loop() //процедура loop
{

  int totalNotes = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < totalNotes; thisNote++) {

    float currentTempo = getCurrentTempo();
    int noteDuration =  190 / currentTempo * 1000 / noteDurations[thisNote];
    tone(melodyPin, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(melodyPin);
  }
}

