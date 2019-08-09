#include "pitches.h"
int melody[] = {
  NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_G4,NOTE_C4,NOTE_D4,NOTE_E4,
};

int noteDurations[] = {
  4,4,2,4,4,2,4,4,4,4,1
};

void setup() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}

void loop() {
}
