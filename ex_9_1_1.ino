int buzzerPin = 9;
int songLength = 93;

char notes[] = "C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C G A G C# D D C# D C C C C C C# D D D D D D# D# D# D# D D D D D# D D D# C# D D D# D C# D D D D D# D D D D D# D D# D D D# D C# C C";

int beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

int tempo = 200;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int duration;

  for (int i = 0; i < songLength; i++) {
    duration = beats[i] * tempo;

    if (notes[i] == ' ') {
      delay(duration);
    } else {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);
    }

    delay(tempo / 10);
  }
}

int frequency(char note) {
  int notes = 8;

  char names[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B', 'C' };
  int frequencies[] = { 262, 294, 330, 349, 392, 440, 494, 523 };

  for (int i = 0; i < notes; i++) {
    if (names[i] == note) {
      return frequencies[i];
    }
  }
  return 0;
}
