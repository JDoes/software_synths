/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.

    Demonstrates the use of Oscil to play a wavetable.

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.com/Mozzi/

    Mozzi documentation/API
		https://sensorium.github.io/Mozzi/doc/html/index.html

		Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2012, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, CONTROL_RATE> kVib(SIN2048_DATA);


// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 128 // Hz, powers of 2 are most reliable

int pot0, pot1, pot2, pot3;
int frequency1, frequency2, amount, volume;

void setup(){
  startMozzi(CONTROL_RATE); // :)

}


void updateControl(){
  pot0 = mozziAnalogRead(A0);
  pot1 = mozziAnalogRead(A1);
  pot2 = mozziAnalogRead(A2);
  pot3 = mozziAnalogRead(A3); 
  frequency1 = 3*pot0;
  frequency2 = 0.04*pot1+0.7;
  amount = map(pot2, 0, 1023, 0, 400);
  volume = map(pot3, 0, 1023, 0, 255);
  
  aSin2.setFreq(frequency2);

  if(digitalRead(2)){
    volume=0;

}
}


int updateAudio(){
  aSin1.setFreq(frequency1+(amount*(aSin2.next())>>8));
  return volume*(aSin1.next())>>8; 
}


void loop(){
  audioHook(); // required here
}
