// Toccata and Fugue in D Minor

#define melodyPin 3

int melody[] = {
  880, 784, 880, 784, 698, 659, 587, 554, 587, 440, 392, 440, 330, 349, 277, 294, 220, 196, 220, 196, 175, 165, 147, 139, 147, 139, 165, 196, 233, 277, 330, 294, 165, 185, 277, 294, 330, 277, 294, 330, 277, 294, 330, 277, 294, 330, 349, 392, 330, 349, 392, 330, 349, 392, 330, 349, 392, 440, 466, 392, 440, 466, 392, 440, 466, 392, 440, 554, 587, 659, 554, 587, 659, 554, 587, 659, 554, 587, 659, 659, 698, 784, 659, 698, 784, 659, 698, 784, 659, 698, 784, 880, 932, 784, 880, 932, 784, 880, 932, 784, 880, 880, 784, 932, 659, 784, 932, 659, 698, 880, 587, 698, 880, 587, 659, 784, 523, 659, 784, 523, 587, 698, 466, 587, 698, 466, 523, 659, 440, 523, 659, 440, 466, 587, 392, 466, 587, 392, 440, 523, 349, 440, 523, 349, 392, 466, 330, 392, 466, 330, 349, 440, 294, 349, 440, 294, 330, 392, 277, 330, 392, 277, 139, 165, 196, 233, 277, 330, 392, 466, 440, 392, 349, 330, 294, 277, 247, 277, 220, 277, 330, 392, 349, 392, 349, 392, 349, 392, 349, 392, 349, 392, 349, 330, 294, 440, 587, 440, 659, 440, 698, 440, 587, 440, 659, 440, 698, 440, 784, 440, 659, 440, 698, 440, 784, 440, 880, 440, 698, 440, 784, 440, 880, 440, 932, 440, 784, 440, 880, 440, 698, 440, 784, 440, 659, 440, 698, 440, 587, 440, 659, 659, 440, 554, 440, 587, 440, 440, 440, 466, 440, 392, 440, 440, 440, 349, 440, 392, 440, 330, 440, 349, 440, 294, 440, 392, 440, 330, 440, 349, 440, 294, 440, 330, 440, 277, 440, 294, 440, 220, 440, 233, 440, 196, 440, 220, 440, 175, 440, 196, 440, 165, 440, 175, 440, 147, 440, 196, 440, 165, 440, 175, 440, 147, 440, 165, 440, 139, 440, 147, 294, 349, 466, 349, 262, 330, 440, 330, 233, 294, 392, 294, 220, 277, 330, 440, 294, 466, 220, 440, 233, 392, 440, 294, 349, 466, 349, 262, 330, 440, 330, 233, 294, 392, 294, 220, 277, 330, 440, 294, 466, 220, 440, 233, 392, 440, 392, 349, 330, 294, 277, 247, 277, 220, 247, 277, 294, 330, 349, 392, 440, 392, 349, 330, 349, 294, 349, 440, 554, 587, 440, 494, 554, 587, 659, 698, 784, 880, 932, 587, 932, 440, 880, 466, 784, 880, 587, 698, 932, 698, 523, 659, 880, 659, 466, 587, 784, 587, 440, 554, 659, 880, 587, 932, 440, 880, 466, 784, 880, 494, 554, 494, 440, 554, 659, 784, 932, 880, 784, 698, 659, 698, 659, 587, 554, 587, 523, 466, 440, 392, 349, 330, 294, 392, 659, 554, 466, 554, 466, 554, 659, 554, 466, 554, 466, 554, 659, 554, 466, 554, 466, 554, 659, 554, 466, 554, 466, 392, 466, 392, 330, 392, 330, 392, 466, 392, 330, 392, 330, 392, 466, 392, 330, 392, 330, 392, 466, 392, 330, 392, 330, 277, 330, 277, 233, 277,
};

int noteDurations[] = {
  14, 10, 122, 12, 11, 10, 12, 57, 157, 12, 15, 125, 29, 22, 30, 218, 12, 12, 126, 12, 11, 11, 14, 62, 216, 44, 41, 43, 45, 63, 167, 88, 68, 357, 42, 14, 14, 13, 11, 12, 13, 13, 14, 11, 30, 25, 21, 12, 16, 12, 11, 14, 12, 12, 13, 23, 25, 17, 16, 15, 10, 12, 13, 10, 14, 16, 200, 45, 18, 15, 12, 12, 13, 11, 12, 12, 11, 22, 8, 23, 16, 12, 14, 12, 12, 13, 11, 11, 13, 22, 22, 16, 15, 15, 11, 12, 13, 12, 12, 16, 184, 32, 25, 20, 19, 20, 16, 16, 16, 14, 14, 16, 12, 11, 13, 12, 12, 15, 13, 11, 13, 12, 12, 12, 13, 10, 13, 12, 11, 14, 11, 11, 13, 12, 12, 13, 12, 11, 13, 12, 13, 14, 12, 11, 13, 12, 12, 14, 12, 10, 13, 11, 10, 14, 13, 12, 14, 13, 15, 17, 19, 125, 22, 13, 13, 12, 12, 9, 17, 304, 30, 24, 18, 12, 14, 14, 16, 16, 14, 14, 16, 22, 8, 8, 5, 7, 6, 5, 8, 5, 6, 6, 36, 63, 468, 38, 18, 14, 15, 16, 15, 17, 13, 16, 15, 11, 17, 14, 14, 19, 9, 23, 8, 21, 11, 17, 14, 15, 19, 10, 18, 11, 16, 9, 21, 10, 17, 13, 13, 16, 14, 15, 13, 16, 14, 15, 13, 17, 16, 12, 1, 17, 11, 18, 11, 15, 16, 14, 14, 15, 13, 17, 11, 18, 10, 18, 10, 17, 12, 15, 12, 17, 12, 19, 9, 19, 8, 20, 8, 18, 10, 17, 11, 17, 10, 18, 11, 16, 15, 13, 16, 12, 16, 13, 15, 16, 14, 14, 12, 16, 12, 16, 12, 23, 6, 18, 9, 19, 9, 16, 13, 15, 13, 15, 14, 14, 16, 13, 24, 128, 15, 13, 14, 12, 13, 12, 11, 12, 12, 9, 12, 14, 14, 14, 14, 21, 39, 35, 33, 35, 30, 44, 117, 14, 13, 15, 13, 14, 13, 12, 15, 13, 10, 14, 16, 14, 15, 15, 22, 42, 36, 36, 35, 37, 51, 206, 35, 20, 16, 16, 15, 14, 16, 16, 11, 11, 12, 10, 11, 9, 9, 8, 10, 10, 17, 17, 15, 16, 17, 25, 16, 13, 16, 18, 14, 10, 8, 12, 118, 42, 34, 30, 32, 35, 45, 147, 21, 12, 12, 11, 12, 12, 11, 11, 11, 12, 10, 13, 15, 16, 15, 31, 44, 39, 30, 32, 35, 45, 131, 117, 137, 38, 27, 24, 10, 11, 64, 24, 15, 15, 15, 14, 13, 12, 12, 14, 12, 11, 12, 16, 15, 13, 28, 403, 35, 25, 20, 16, 13, 14, 15, 14, 12, 13, 20, 19, 15, 15, 13, 10, 11, 12, 12, 15, 13, 10, 15, 13, 14, 13, 12, 10, 11, 12, 12, 13, 13, 11, 14, 15, 12, 13, 15, 12, 12, 12, 13, 14, 13, 14, 14, 13, 15, 15, 11, 11,
};


void setup()
{

}

void loop()
{
  int totalNotes = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < totalNotes; thisNote++) {

    int noteDuration =  noteDurations[thisNote] * 8;
    tone(melodyPin, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(melodyPin);
  }

  delay(2000);
}


