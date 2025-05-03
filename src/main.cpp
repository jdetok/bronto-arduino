// Brontosaurus LED Display
// designed, built, and programmed by Justin DeKock 
// spring 2025
// 48 green LEDs driven by six SN74HC595 shift registers connected to an Arduino Nano

#include <Arduino.h> // Arduino framework
#include "interact.h" // controls switches and pots
#include "shiftreg.h"
#include "rgb.h" // controls RGB LED
#include "states.h"

// construct switch object(s)
SlideSwitch pwrSw(5); // power
SlideSwitch brtSw(3); // brightness
SlideSwitch brtMdSw(2); // intensity

// only A0 - A5 can be used as digital sadly
// maybe run a jumper from A6-A5 and A7-A1
SlideSwitch pSw(A5); // pattern - change from A6 to A5
SlideSwitch sSw(A0); // sequence/solid - A7 to A0

// construct potentiometer object(s)
Pot spdPot(A1); // LED sequence speed
Pot rPot(A4); // red level
Pot gPot(A3); // green level
Pot bPot(A2); // blue level

// construct shift register object
ShfitReg shiftReg(4, 6, 7, 8); // D4-serPin, D6-oePin, D7-latchPin, D8-clkPin

// construct RGB object(s)
RGB rgbEye(9, 10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
}

void loop() {
  Serial.println(state(pSw.pin));
  //Serial.println(pSw.getState());
  rgbEye.off();
  // using intensity (brt mode) switch until figuring out sSw and pSw not working digital
  if (sSw.getState() == 0) {
    rgbEye.on(pwrSw.getState(), brtSw.getState(), brtMdSw.getState(), 
    rPot.getInt(), gPot.getInt(), bPot.getInt());
    shiftReg.on(pwrSw.getState(), brtSw.getState(), brtMdSw.getState());
  } else {
    // shiftReg.chase(6, spdPot.getSpd(), pSw.getState());
    shiftReg.chase(6, spdPot.getSpd(), pwrSw.pin, sSw.pin, pSw.pin, brtSw.pin, brtMdSw.pin);
  }
}