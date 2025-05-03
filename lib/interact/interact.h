#ifndef INTERACT_H
#define INTERACT_H

// define functions for interacting with switches/pots

 class SlideSwitch {
//    private:
        

    public:
        int pin;
        SlideSwitch(int pin);
        void init();
        bool getState();
 };

 class Pot {
    //private:
        
    public:
        int pin;    
        Pot(int pin);
        int getInt();
        int getSpd();
        int getBrt();
 };


#endif