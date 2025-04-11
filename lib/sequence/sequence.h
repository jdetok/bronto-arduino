#ifndef SEQUENCE_H
#define SEQUENCE_H

class Sequence {
    private:
        int ser;
        int oe;
        int latch;
        int clk;
    
    public:
        int num_leds;
        // ShfitReg shiftReg;
        
        //Sequence(){}
        //Sequence(int ser, int oe, int latch, int clk, int num_leds){};
        Sequence(int, int, int, int, int);
        void onOff(byte state, int spd);
        void runSeq(byte state, int spd);
};

#endif