// This is probably the correct FakeRat program
// Do not remove the include below
#include "FakeRat.h"
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int timeCount = 9999; // initial high values so it fires on startup
#define LED_PIN 0
#define TONE_PIN 1
volatile boolean f_wdt = 1;

void setup(){
  pinMode(LED_PIN,OUTPUT);
  setup_watchdog(9); // approximately 8 seconds sleep
}
#ifndef ARDUINO                     //main() function not required in Arduino environment
int main(void) {
    setup();
    for(;;) {loop();}
    return 0;
}
#endif

void loop(){
  if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
    f_wdt=0;       // reset flag

    if (timeCount++ > 225) // should be 30 mins
    {
		digitalWrite(LED_PIN,HIGH);  // let led on
		tone(TONE_PIN, NOTE_CS4,1000);
		delay(500);
		tone(TONE_PIN, NOTE_FS4,1000);
		delay(500);
		tone(TONE_PIN, NOTE_B0,1000);
		delay(500);
		noTone(TONE_PIN);
		digitalWrite(LED_PIN,LOW); // led off
		timeCount = 0;
    }
    pinMode(LED_PIN,INPUT); // set all used port to input to save power
    pinMode(TONE_PIN,INPUT); // set all used port to input to save power
    system_sleep();
    pinMode(LED_PIN,OUTPUT); // set all ports into state before sleep
    pinMode(TONE_PIN,OUTPUT); // set all ports into state before sleep
  }
}
// set system into the sleep state
// system wakes up when wtchdog is timed out
void system_sleep() {
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}
