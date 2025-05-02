// Brontosaurus LED Display
// designed, built, and programmed by Justin DeKock 
// spring 2025
// 48 green LEDs driven by six SN74HC595 shift registers connected to an Arduino Nano

#include <Arduino.h> // Arduino framework
#include "interact.h" // controls switches and pots
#include "shiftreg.h"
#include "rgb.h" // controls RGB LED

// construct switch object(s)
SlideSwitch pwrSw(5); // D2 - main power switch
SlideSwitch brtSw(3); // D3 - rgb power switch
SlideSwitch brtMdSw(2); // D5 - rgb mode switch (swtiches between rgb sequence and pot color control)

// only A0 - A5 can be used as digital sadly
// maybe run a jumper from A6-A5 and A7-A1
SlideSwitch pSw(A6);
SlideSwitch sSw(A7);

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

  rgbEye.on(pwrSw.getState(), brtSw.getState(), brtMdSw.getState(), 
            rPot.getInt(), gPot.getInt(), bPot.getInt());

  Serial.println(sSw.getState());
  // using intensity (brt mode) switch until figuring out sSw and pSw not working digital
  if (brtMdSw.getState() == 0) {
    shiftReg.on(pwrSw.getState(), brtSw.getState(), brtMdSw.getState());
  } else {
    shiftReg.chase(6, 200);
  }
}