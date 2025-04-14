#include <Arduino.h>
#include "shiftreg.h"
#include "interact.h"

ShfitReg::ShfitReg(int serPin, int oePin, int latchPin, int clkPin) {
    this->serPin = serPin;
    this->oePin = oePin;
    this->latchPin = latchPin;
    this->clkPin = clkPin;
    pinMode(serPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clkPin, OUTPUT);

    digitalWrite(oePin, HIGH);
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

void ShfitReg::on(int pwrState, int brtState, int brtMdState) {
    //int h = 255;
    int h = 0b11111111;
    int brt = 255;
    
    // if pwrSw (pin D2) is on, set brt based on brtSw (pin D3) and brtMdSw (pin D5)
    if (pwrState == 1) {
        if (brtState == 0) { 
            if (brtMdState == 0) { 
                brt = 254; // brtSw low, brtMdSw low = lowest brightness
            } else {
                brt = 230; // brtSw low, brtMdSw high = slightly brighter
            }
        } else {
            if (brtMdState == 0) {
                brt = 180; // brtSw high, brtMdSw low = second brightest
            } else {
                brt = 70; // brtSw high, brtMdSw high = highest brightness
            }
        }
    }

    analogWrite(oePin, brt);
    digitalWrite(latchPin, LOW);
    shiftOut(serPin, clkPin, MSBFIRST, h);
    digitalWrite(latchPin, HIGH);

}