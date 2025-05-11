#include <Arduino.h>
#include "interact.h"

// slideswitch methods
SlideSwitch::SlideSwitch(byte pin) {
    this->pin = pin;
    init();
}

void SlideSwitch::init() {
    pinMode(pin, INPUT);
}

bool SlideSwitch::getState() {
    return (digitalRead(pin));
}

// pot methods
// pot class constructor
Pot::Pot(byte pin) {
    this->pin = pin;
}

// return value of pot 0-255
int Pot::getInt() {
    return (analogRead(pin) / 4);
}

int Pot::getBrt() {
    return ((analogRead(pin) / 4) - 255);
}

int Pot::getSpd() {
    return analogRead(pin); // should return 0 - 1123
}