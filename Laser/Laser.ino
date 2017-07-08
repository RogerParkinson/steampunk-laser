// Do not remove the include below
#include "Laser.h"


/*


 Plays a melody on ATTiny85 using tone() PWM pin 4

 circuit:
 * 8-ohm speaker on digital pin 0

 */

#define TONE_PIN 4
#define NOTE_DURATION 1
#define LED_PIN PORTB3
#define LED_PIN1 PORTB0
int LED_cycle=0;


void setup(void);
void loop(void);

void setup() {
  DDRB |= _BV(LED_PIN);
  DDRB |= _BV(LED_PIN1);
  PINB |= _BV(LED_PIN);
  //setupTimer1(myISR);

}
#ifndef ARDUINO                     //main() function not required in Arduino environment
int main(void) {
    setup();
    for(;;) {loop();}
    return 0;
}
#endif
void myISR() {                      //this function will be called every 10ms
    static uint8_t myCounter;

    if (++myCounter == 100) {       //has a second elapsed?
        myCounter = 0;
        PINB |= _BV(LED_PIN);           //toggle the LED
        PINB |= _BV(LED_PIN1);           //toggle the LED
    }
}

void loop() {
  // repeat the melody.
  static uint8_t myCounter;
  if (++myCounter == 100) {       //has a second elapsed?
    myCounter = 0;
    }

  if (myCounter % 1 == 0) {
    PINB |= _BV(LED_PIN);           //toggle the LED
    PINB |= _BV(LED_PIN1);           //toggle the LED
  }

//  digitalWrite(LED_PIN, HIGH);
  for (int thisNote=95; thisNote<105; thisNote++)
  {
    playNote(thisNote,NOTE_DURATION);;
  }
//  digitalWrite(LED_PIN, LOW);
//  digitalWrite(LED_PIN1, HIGH);

  for (int thisNote=105; thisNote>95; thisNote--)
  {
    playNote(thisNote,NOTE_DURATION);
  }
//  digitalWrite(LED_PIN1, LOW);
}

void playNote(int note, int duration)
{
    int noteDuration = 1000/(duration*16);
    tone(TONE_PIN, note,noteDuration);
    int pauseBetweenNotes = noteDuration * 1/4;//1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(TONE_PIN);

 //   tone(TONE_PIN, 90,noteDuration);
 //   delay(pauseBetweenNotes/4);
    // stop the tone playing:
 //   noTone(TONE_PIN);
 }
