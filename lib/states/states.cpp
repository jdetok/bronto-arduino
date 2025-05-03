#include <Arduino.h>

bool state(int pin) {
    return digitalRead(pin);
}

int val (int pin) {
    return analogRead(pin);
}