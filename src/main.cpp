// Brontosaurus LED Display
// designed, built, and programmed by Justin DeKock 
// March/April 2025
// 48 green LEDs driven by six SN74HC595 shift registers connected to an Arduino Nano

#include <Arduino.h> // Arduino framework
#include "interact.h" // controls switches and pots
#include "sequence.h" // controls led sequences
#include "rgb.h" // controls RGB LED

// CONSTANTS FOR ARDUINO PINS =================================================
// switch pins
const int pwrSw = 2; // on/off switch
const int rgbPwrSw = 3; // turns RGB off
const int rgbModeSw = 5; // switches mode for RGB eye (activate RGB pots)

// pot pins
const int spdPot = A0; // controls delay time/speed of sequence
const int brtPot = A1; // controls brightness
const int rPot = A2; // controls amount of red in RGB eye
const int gPot = A3; // controls amount of green in RGB eye
const int bPot = A4; // controls amount of blue in RGB eye

// shift register pins
const int serPin = 4; // serial pin (14) on 74HC595
const int oePin = 6; // output enable pin (13) on 74HC595
const int latchPin = 7; // rclk pin (12) on 74HC595
const int clkPin = 8; // srclk pin (11) on 74HC595

// rgb pins
const int rPin = 9; // red
const int gPin = 10; // green
const int bPin = 11; // blue

void setup() {
  // input switches
  pinMode(pwrSw, INPUT);
  pinMode(rgbPwrSw, INPUT);
  pinMode(rgbModeSw, INPUT);

  // 74HC595 outputs
  pinMode(serPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clkPin, OUTPUT);

  // RGB outputs
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println("Hello");
}