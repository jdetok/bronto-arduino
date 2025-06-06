#include <Arduino.h>
#include "shiftreg.h"
#include "interact.h"
#include "rgb.h"

// steps for sequence
int steps [] = {1, 2, 4, 8, 16, 32, 64, 128};
int stepr [] = {128, 64, 32, 16, 8, 4, 2, 1};

ShfitReg::ShfitReg(byte serPin, byte oePin, byte latchPin, byte clkPin, 
    byte pwrPin, byte brtPin, byte intPin, byte seqPin, byte ptrnPin, byte spdPin, byte bPin) {
    
    this->serPin = serPin;
    this->oePin = oePin;
    this->latchPin = latchPin;
    this->clkPin = clkPin;

    this->pwrPin = pwrPin;
    this->brtPin = brtPin;
    this->intPin = intPin;
    this->seqPin = seqPin;
    this->ptrnPin = ptrnPin;
    this->spdPin = spdPin;
    this->bPin = bPin;

    pinMode(serPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clkPin, OUTPUT);

    digitalWrite(oePin, HIGH);
}

void ShfitReg::selector(int num_sr, int num_led) {
    if (digitalRead(pwrPin) == 1) {
        if (digitalRead(seqPin) == 1) {
            seq(num_sr, num_led);
        } else {
            on();
        }
    } else {
        off();
    }
}

// SEQUENCE FUNCTION
void ShfitReg::seq(int num_sr, int num_led) {
    for (int sr = 0; sr < num_sr; sr++) {
        for (int led = 0; led < num_led; led++) { 
            digitalWrite(latchPin, LOW);
            delay(seqSpd());

            if (digitalRead(ptrnPin) == 0) {
                if (sr == 0) {
                    bitsFirst(num_sr, sr, led); 
                } else {
                    bitsAfter(num_sr, sr, led);
                }
            } else {
                //if (analogRead(bPin) > 0) {
                    shiftOut(serPin, clkPin, MSBFIRST, steps[led]);
                // } else {
                //     if (sr == num_sr-1) {
                //         bitsFirstr(num_sr, sr, led); 
                //     } else {
                //         bitsAfterr(num_sr, sr, led);
                //     }
                // }                
            }
            analogWrite(oePin, getBrtState());
            digitalWrite(latchPin, HIGH);
        }
    }
}

// send in an empty byte
void ShfitReg::emptyByteIn(char dir = 'm') {
    byte empty = 0x00;
    
    if (dir == 'm') {
        shiftOut(serPin, clkPin, MSBFIRST, empty);
    } else if (dir == 'l') {
        shiftOut(serPin, clkPin, LSBFIRST, empty);
    }
}

// one led at a time
void ShfitReg::bitsFirst(int num_sr, int sr, int led) {
    for (int r = 0; r < num_sr - 1; r++) {
        emptyByteIn('m'); 
    }
    shiftOut(serPin, clkPin, MSBFIRST, steps[led]); 
}

void ShfitReg::bitsAfter(int num_sr, int sr, int led) {
    for (int r = 0; r < num_sr - (sr + 1); r++) {
        emptyByteIn('m');
    }
    
    shiftOut(serPin, clkPin, MSBFIRST, steps[led]);
    
    for (int r = 0; r < sr; r++) {  
        emptyByteIn('m');
    }    
}

// reverse one led at a time
void ShfitReg::bitsFirstr(int num_sr, int sr, int led) {
    for (int r = 0; r < num_sr - 1; r++) {
        emptyByteIn('m'); 
    }

    for (int r = 0; r < num_sr - (sr + 1); r++) {
        emptyByteIn('m');
    }
    shiftOut(serPin, clkPin, MSBFIRST, stepr[led]); 
}
void ShfitReg::bitsAfterr(int num_sr, int sr, int led) {
    for (int r = 0; r < sr; r++) {  
        emptyByteIn('m');
    }  
    shiftOut(serPin, clkPin, MSBFIRST, stepr[led]);

    for (int r = 0; r < num_sr - (sr + 1); r++) {
        emptyByteIn('m');
    }
}

// drive oePin high to turn off all leds
void ShfitReg::off() {
    digitalWrite(oePin, HIGH);
}
// all on
void ShfitReg::on() {
    int h = 0xFF;
    int brt = getBrtState();

    analogWrite(oePin, brt);
    digitalWrite(latchPin, LOW);
    shiftOut(serPin, clkPin, MSBFIRST, h);
    digitalWrite(latchPin, HIGH);
    delay(1);
}

// brightness based on brightness and intensity switches
int ShfitReg::getBrtState() {
    int brt = 255;
    int low = 254;
    int medlow = 230;
    int medhigh = 180;
    int high = 70;

    // if pwrSw (pin D2) is on, set brt based on brtSw (pin D3) and brtMdSw (pin D5)
    if (digitalRead(pwrPin) == 1) {
        if (digitalRead(brtPin) == 0) { 
            if (digitalRead(intPin) == 0) { 
                brt = low; // brtSw low, brtMdSw low = lowest brightness
            } else {
                brt = medlow; // brtSw low, brtMdSw high = slightly brighter
            }
        } else {
            if (digitalRead(intPin) == 0) {
                brt = medhigh; // brtSw high, brtMdSw low = second brightest
            } else {
                brt = high; // brtSw high, brtMdSw high = highest brightness
            }
        }
    }
    return brt;
}

// get the delay speed
int ShfitReg::seqSpd() {
    return analogRead(spdPin);
}