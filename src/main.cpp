// Brontosaurus LED Display
// designed, built, and programmed by Justin DeKock 
// spring 2025
// 48 green LEDs driven by six SN74HC595 shift registers connected to an Arduino Nano

#include <Arduino.h> // Arduino framework
#include "interact.h" // controls switches and pots
#include "shiftreg.h" // main light display control
#include "rgb.h" // controls RGB LED

// six shift registers, 8 LEDs
const int NUM_SR = 6;
const int NUM_LED = 8;

// construct switch object(s)
SlideSwitch pwrSw(5); // power
SlideSwitch brtSw(3); // brightness
SlideSwitch brtMdSw(2); // intensity

// only A0 - A5 can be used as digital sadly
// maybe run a jumper from A6-A5 and A7-A1
SlideSwitch seqSw(A0); // sequence/solid - A7 to A0
SlideSwitch ptrnSw(A5); // pattern - change from A6 to A5

// construct potentiometer object(s)
Pot spdPot(A1); // LED sequence speed
Pot rPot(A4); // red level
Pot gPot(A3); // green level
Pot bPot(A2); // blue level

// construct shift register object
ShfitReg shiftReg(4, 6, 7, 8, // D4-serPin, D6-oePin, D7-latchPin, D8-clkPin
                  pwrSw.pin, brtSw.pin, brtMdSw.pin, 
                  seqSw.pin, ptrnSw.pin, spdPot.pin, bPot.pin); 

// construct RGB object(s)
RGB rgbEye(9, 10, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // control rgb
  if (seqSw.getState() == 0) {
    rgbEye.on(pwrSw.getState(), brtSw.getState(), brtMdSw.getState(), 
      rPot.getInt(), gPot.getInt(), bPot.getInt());
  } else {
    rgbEye.off();
  }
  
  // control shift register leds
  shiftReg.selector(NUM_SR, NUM_LED);  
}
