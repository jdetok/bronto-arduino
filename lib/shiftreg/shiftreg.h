#ifndef SHIFTREG_H
#define SHIFTREG_H

class ShfitReg {
    public:
        int serPin;
        int oePin;
        int latchPin;
        int clkPin;

        ShfitReg(int serPin, int oePin, int latchPin, int clkPin);
        void init();
        void off();
        void on();
};

#endif