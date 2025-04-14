#include <Arduino.h>
#include "interact.h"

// slideswitch methods
SlideSwitch::SlideSwitch(int pin) {
    this->pin = pin;
    init();
}

void SlideSwitch::init() {
    pinMode(pin, INPUT_PULLUP);
}

bool SlideSwitch::getState() {
    return (digitalRead(pin));
}

// pot methods
// pot class constructor
Pot::Pot(int pin) {
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