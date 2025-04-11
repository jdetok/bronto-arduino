#include <Arduino.h>
#include "shiftreg.h"

ShfitReg::ShfitReg(int serPin, int oePin, int latchPin, int clkPin) {
    this->serPin = serPin;
    this->oePin = oePin;
    this->latchPin = latchPin;
    this->clkPin = clkPin;
    pinMode(serPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clkPin, OUTPUT);
    //init();
}
 
void ShfitReg::init() {
    pinMode(serPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clkPin, OUTPUT);
}

void ShfitReg::off() {
    // drive oePin high to turn off all leds
    digitalWrite(oePin, HIGH);
}

void ShfitReg::on() {
    // drive oePin high to turn off all leds
    digitalWrite(oePin, LOW);
}