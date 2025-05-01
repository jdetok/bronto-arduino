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
    int h = 0xFF;
    int brt = getBrtState(pwrState, brtState, brtMdState);

    analogWrite(oePin, brt);
    digitalWrite(latchPin, LOW);
    shiftOut(serPin, clkPin, MSBFIRST, h);
    digitalWrite(latchPin, HIGH);
}

void ShfitReg::chase(int num_sr, int dt) {
    // each number represents a byte like 10000000, 01000000, etc
    int steps [] = {1, 2, 4, 8, 16, 32, 64, 128};

    // empty byte (00000000) to shift in
    byte empty = 0x00;
    
    // 8 LEDs per shift register
    int num_led = 8;

    // set OE low to enable output
    digitalWrite(oePin, LOW);

     // outer loop - one run per shift register
    for (int sr = 0; sr < num_sr; sr++) {
        // inner loop - one run per LED
        for (int led = 0; led < num_led; led++) { 
            // set latch low to shift in bits
            digitalWrite(latchPin, LOW);
            // first shift register
            if (sr == 0) {
                // shift num_sr - 1 (5 in this case) empty bytes into memory
                for (int r = 0; r < num_sr - 1; r++) {
                    shiftOut(serPin, clkPin, MSBFIRST, empty);  
                }
                
                // after all empty bytes are loaded, shift in the byte containing one lit LED
                shiftOut(serPin, clkPin, MSBFIRST, steps[led]);

            } else { // all shift registers after the first
                // first, shift in remaining empty bytes considering sr (loop iterator) and lit byte
                for (int t = 0; t < num_sr - (sr + 1); t++) {
                    shiftOut(serPin, clkPin, MSBFIRST, empty);  
                }

                // shift lit byte in
                shiftOut(serPin, clkPin, MSBFIRST, steps[led]);
              
                // shift in the rest of the empty bytes
                for (int r = 0; r < sr; r++) {
                    shiftOut(serPin, clkPin, MSBFIRST, empty);  
                }       
            }
            // run latch high to write all bits (48 in this case) to output at once 
            digitalWrite(latchPin, HIGH);
            delay(dt);
        }
    }

}
