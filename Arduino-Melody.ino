/*
  Based on Tom Igoe's code
  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"
#include <Servo.h>

Servo myServo;

const int buzzerPin = 3;
const int buttonPin = 7;
int buttonState = 7;
const int ledPin = 9;

// notes in the melody:
// use 0 for a rest
// put each measure on its own line
int melody[] = {
  NOTE_E4, NOTE_B4, NOTE_C4, NOTE_D4, 0, 
  NOTE_C4, NOTE_B4, NOTE_A4, 0,
  NOTE_A4, NOTE_C4, NOTE_E4, 0,
  NOTE_D4, NOTE_C4, NOTE_B4, 0,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A4, NOTE_A4, 0, 0,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, 0,
  NOTE_C4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, 0,
  NOTE_B4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A4, NOTE_A4
  
};

// note durations: 1 = whole note, 4 = quarter note, 8 = eighth note, etc.:
// be sure each note or rest in the melody above has a corresponding duration below
// put each measure on its own line
int noteDurations[] = {
  2, 4, 4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 2, 2, 4, 4, 2, 2,
  4, 4, 2, 4, 4, 4, 4,
  4, 2, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2, 2
};

// set the tempo
// a tempo of 60 is one beat per second
// a tempo of 120 would be twice as fast
int beatsPerMinute = 298;

void setup() {
  myServo.attach(10);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH){

    digitalWrite(ledPin, HIGH);
    myServo.write(180);
    playSong();
    myServo.write(0);
    digitalWrite(ledPin, LOW);

  }
  else{
    digitalWrite (ledPin, LOW);
  }
}


void playSong(){
// iterate over the notes of the melody:
  int len = sizeof(melody)/sizeof(melody[0]);
  for (int thisNote = 0; thisNote < len; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = static_cast<int>(1000 / noteDurations[thisNote] * 298 / beatsPerMinute);
    tone(buzzerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
    
  }
 }
