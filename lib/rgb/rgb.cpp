#include <Arduino.h>
#include "rgb.h"
#include "interact.h"

RGB::RGB(int rPin, int gPin, int bPin) {
    this->rPin = rPin;
    this->gPin = gPin;
    this->bPin = bPin;
}

void RGB::init() {
    for (int pin : rgbPins) {
        pinMode(pin, OUTPUT);
    }
}

void RGB::off() {
    for (int pin : rgbPins) {
        digitalWrite(pin, LOW);
    }
}

void RGB::red() {
    analogWrite(rPin, 255);
    analogWrite(gPin, 0);
    analogWrite(bPin, 0);
}

void RGB::grn() {
    analogWrite(rPin, 0);
    analogWrite(gPin, 255);
    analogWrite(bPin, 0);
}

void RGB::blu() {
    analogWrite(rPin, 0);
    analogWrite(gPin, 0);
    analogWrite(bPin, 255);
}

int RGB::setBrtDiv(int brtState, int brtMdState) {
    int dv = 0;
    if (brtState == 1) {
        if (brtMdState == 1) {
            dv = 1; 
        } else {
            dv = 2;
        }
    } else {
        if (brtMdState == 1) {
            dv = 4;
        } else {
            dv = 8;
        }
    }
    return dv;
}

// pass three values 0-255 to turn on RGB
void RGB::on(int pwrState, int brtState, int brtMdState,  int rVal, int gVal, int bVal) {
    int dv = 0;
    if (pwrState == 1) {
        // divide respective pot value by appropriate divider dv value
        dv = setBrtDiv(brtState, brtMdState);
        analogWrite(rPin, (rVal / dv));
        analogWrite(gPin, (gVal / dv));
        analogWrite(bPin, (bVal / dv));
        } else {
        digitalWrite(rPin, LOW);
        digitalWrite(gPin, LOW);
        digitalWrite(bPin, LOW);
    }
}

void RGB::on1() {
    digitalWrite(rPin, HIGH);
        //digitalWrite(gPin, HIGH);
        digitalWrite(bPin, HIGH);
}

void RGB::onSw(int rState, int gState, int bState, int brt) {
    if (rState == 1) {
        analogWrite(rPin, brt);
    }
    if (gState == 1) {
        analogWrite(gPin, brt);
    }
    if (bState == 1) {
        analogWrite(bPin, brt);
    }
}
