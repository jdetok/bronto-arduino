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
}
 
void ShfitReg::init() {
    pinMode(serPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clkPin, OUTPUT);
}

int ShfitReg::getBrtState(int pwrState, int brtState, int brtMdState) {
    int brt = 255;
    
    int low = 254;
    int medlow = 230;
    int medhigh = 180;
    int high = 70;

    // if pwrSw (pin D2) is on, set brt based on brtSw (pin D3) and brtMdSw (pin D5)
    if (pwrState == 1) {
        if (brtState == 0) { 
            if (brtMdState == 0) { 
                brt = low; // brtSw low, brtMdSw low = lowest brightness
            } else {
                brt = medlow; // brtSw low, brtMdSw high = slightly brighter
            }
        } else {
            if (brtMdState == 0) {
                brt = medhigh; // brtSw high, brtMdSw low = second brightest
            } else {
                brt = high; // brtSw high, brtMdSw high = highest brightness
            }
        }
    }
    return brt;
}

void ShfitReg::off() {
    // drive oePin high to turn off all leds
    digitalWrite(oePin, HIGH);
}

void ShfitReg::on(int pwrState, int brtState, int brtMdState) {
    int h = 0b11111111;
    int brt = getBrtState(pwrState, brtState, brtMdState);

    analogWrite(oePin, brt);
    digitalWrite(latchPin, LOW);
    shiftOut(serPin, clkPin, MSBFIRST, h);
    digitalWrite(latchPin, HIGH);
}

void ShfitReg::seq(int pwrState, int brtState, int brtMdState, int spd) {
    int repeats = 8;
    int n = 1;
    for (int i = 0; i < repeats; i++) {
        analogWrite(oePin, getBrtState(pwrState, brtState, brtMdState));
        digitalWrite(latchPin, LOW);
        shiftOut(serPin, clkPin, MSBFIRST, n);
        digitalWrite(latchPin, HIGH);
        
        n = n * 2;
        Serial.println(n);
        delay(spd);
    }
}
