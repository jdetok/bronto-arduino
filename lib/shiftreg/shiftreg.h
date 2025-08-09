#ifndef SHIFTREG_H
#define SHIFTREG_H

class ShfitReg {
    public:
        uint8_t serPin;
        uint8_t oePin;
        uint8_t latchPin;
        uint8_t clkPin;
        uint8_t pwrPin;
        uint8_t brtPin;
        uint8_t intPin;
        uint8_t seqPin;
        uint8_t ptrnPin;
        uint8_t spdPin;
        uint8_t bPin;
        
        ShfitReg(
            uint8_t serPin, 
            uint8_t oePin, 
            uint8_t latchPin, 
            uint8_t clkPin, 
            uint8_t pwrPin, 
            uint8_t brtPin, 
            uint8_t intPin, 
            uint8_t seqPin, 
            uint8_t ptrnPin, 
            uint8_t spdPin, 
            uint8_t bPin);
        
        void selector(int num_sr, int num_led);
        void seq(int num_sr, int num_led);
        void emptyByteIn(); // dir = 'm' for MSBFIRST or 'l' for LSBFIRST
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