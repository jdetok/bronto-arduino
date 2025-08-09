#ifndef INTERACT_H
#define INTERACT_H

// define functions for interacting with switches/pots

 class SlideSwitch {
    public:
        uint8_t pin;
        SlideSwitch(uint8_t pin);
        void init();
        bool getState();
 };

 class Pot {
    //private:
        
    public:
        byte pin;    
        Pot(byte pin);
        int getInt();
        int getSpd();
        int getBrt();
 };


#endif