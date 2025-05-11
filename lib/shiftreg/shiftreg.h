#ifndef SHIFTREG_H
#define SHIFTREG_H

class ShfitReg {
    public:
        byte serPin;
        byte oePin;
        byte latchPin;
        byte clkPin;
        byte pwrPin;
        byte brtPin;
        byte intPin;
        byte seqPin;
        byte ptrnPin;
        byte spdPin;
        byte bPin;
        
        ShfitReg(byte serPin, byte oePin, byte latchPin, byte clkPin, 
                    byte pwrPin, byte brtPin, byte intPin, byte seqPin, byte ptrnPin, byte spdPin, byte bPin);
        
        void selector(int num_sr, int num_led);
        void seq(int num_sr, int num_led);
        void emptyByteIn(char dir); // dir = 'm' for MSBFIRST or 'l' for LSBFIRST
        void bitsFirst(int num_sr, int sr, int led);
        void bitsAfter(int numsr, int sr, int led);
        void bitsFirstr(int num_sr, int sr, int led);
        void bitsAfterr(int numsr, int sr, int led);
        void off();
        void on();
        int getBrtState();
        int seqSpd();
};

#endif