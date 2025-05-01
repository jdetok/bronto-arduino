#ifndef SHIFTREG_H
#define SHIFTREG_H

class ShfitReg {
    public:
        int serPin;
        int oePin;
        int latchPin;
        int clkPin;

        ShfitReg(int serPin, int oePin, int latchPin, int clkPin);
        int getBrtState(int pwrState, int brtState, int brtMdState);
        void off();
        void on(int pwrState, int brtState, int brtMdState);
        void chase(int num_sr, int dt);
};

#endif