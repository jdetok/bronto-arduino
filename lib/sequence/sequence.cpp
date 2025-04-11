#include <Arduino.h>
#include "sequence.h"
#include "interact.h"
#include "shiftreg.h"

Sequence::Sequence(int ser, int oe, int latch, int clk, int num_leds) {
    this->clk = clk;
    this->oe = oe;
    this-> latch = latch;
    this->clk = clk;
    this->num_leds = num_leds;
    //digitalWrite(oe, HIGH);
}

void Sequence::onOff(byte state, int spd){
    while (state == HIGH) {
        runSeq(state, spd);
    } 
}

void Sequence::runSeq(byte state, int spd) {
    int steps[] = {1, 2, 4, 8, 16, 32, 64, 128};
        digitalWrite(oe, !state);
        for (int i=0; i<num_leds; i++) {
            int step = steps[i];
            digitalWrite(latch, LOW);
            shiftOut(ser, clk, MSBFIRST, step);
            digitalWrite(latch, HIGH);
            delay(spd);    
        } 
   // }
}
