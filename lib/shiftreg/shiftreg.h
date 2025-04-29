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
        int getBrtState(int pwrState, int brtState, int brtMdState);
        void off();
        void on(int pwrState, int brtState, int brtMdState);
        void seq(int pwrState, int brtState, int brtMdState, int spd);
};

#endif