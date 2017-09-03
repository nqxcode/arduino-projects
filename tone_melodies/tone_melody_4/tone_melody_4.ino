// Imperial March

#define melodyPin 3

int melody[] = {
  392, 392, 392, 311, 466, 392, 311, 466, 392, 587, 587, 587, 622, 466, 370, 311, 466, 392, 784, 392, 392, 784, 740, 698, 659, 622, 659, 415, 554, 523, 494, 466, 440, 466, 311, 370, 311, 370, 466, 392, 466, 587, 784, 392, 392, 784, 740, 698, 659, 622, 659, 415, 554, 523, 494, 466, 440, 466, 311, 370, 311, 466, 392, 311, 466, 392,
};

int noteDurations[] = {
  201, 198, 178, 139, 52, 195, 147, 50, 382, 190, 196, 192, 139, 50, 188, 144, 53, 389, 181, 157, 45, 191, 149, 42, 45, 39, 199, 101, 190, 145, 51, 46, 50, 192, 92, 190, 148, 49, 194, 141, 50, 385, 181, 157, 45, 191, 149, 42, 45, 39, 199, 101, 190, 145, 51, 46, 50, 192, 92, 190, 148, 49, 194, 141, 50, 257,
};


void setup()
{

}

void loop()
{
  int totalNotes = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < totalNotes; thisNote++) {

    int noteDuration =  noteDurations[thisNote] * 2;
    tone(melodyPin, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(melodyPin);
  }

  delay(2000);
}


