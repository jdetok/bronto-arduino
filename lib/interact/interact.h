#ifndef INTERACT_H
#define INTERACT_H

// define functions for interacting with switches/pots

 class SlideSwitch {
    private:
        int pin;

    public:
        SlideSwitch(int pin);
        void init();
        bool getState();
 };

 class Pot {
    private:
        int pin;
    public:
        Pot(int pin);
        int getInt();
        int getSpd();
        int getBrt();
 };


#endif