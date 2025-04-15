// Brontosaurus LED Display
// designed, built, and programmed by Justin DeKock 
// March/April 2025
// 48 green LEDs driven by six SN74HC595 shift registers connected to an Arduino Nano

#include <Arduino.h> // Arduino framework
#include "interact.h" // controls switches and pots
#include "shiftreg.h"
#include "sequence.h" // controls led sequences
#include "rgb.h" // controls RGB LED

// construct switch object(s)
SlideSwitch pwrSw(2); // D2 - main power switch
SlideSwitch brtSw(3); // D3 - rgb power switch
SlideSwitch brtMdSw(5); // D5 - rgb mode switch (swtiches between rgb sequence and pot color control)
SlideSwitch rgbPwrSw(A5);
SlideSwitch gSw(A6);
SlideSwitch bSw(A7);

// construct potentiometer object(s)
Pot spdPot(A0); // LED sequence speed
Pot brtPot(A1); // LED brightness
Pot rPot(A2); // red level
Pot gPot(A3); // green level
Pot bPot(A4); // blue level

// construct shift register object
ShfitReg shiftReg(4, 6, 7, 8); // D4-serPin, D6-oePin, D7-latchPin, D8-clkPin

// construct RGB object(s)
RGB rgbEye(9, 10, 11);

Sequence ledSeq(shiftReg.serPin, shiftReg.oePin, shiftReg.latchPin, shiftReg.clkPin, 8);

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
}

void loop() {

  //Serial.println("loop");
  Serial.println(gSw.getState());
  //digitalWrite(shiftReg.oePin, !pwrSw.getState());
  //analogWrite(shiftReg.oePin, brtPot.getInt());
  //ledSeq.runSeq(pwrSw.getState(), spdPot.getSpd());  
  rgbEye.on(pwrSw.getState(), rgbPwrSw.getState(), brtSw.getState(), brtMdSw.getState(), rPot.getInt(), gPot.getInt(), bPot.getInt());
  //rgbEye.onSw(rSw.getState(), gSw.getState(), bSw.getState(), 100);
  shiftReg.on(pwrSw.getState(), brtSw.getState(), brtMdSw.getState());
  delay(1);
}