#include <Arduino.h>

const int serPin = 4;
const int oePin = 6;
const int latchPin = 7;
const int clkPin = 8;

// rgb
const int rPin = 9;
const int gPin = 10;
const int bPin = 11;

const int spdPot = A1;

// delay time
int dt = 100;

int num_sr = 6;
int num_led = 8;

// lights one LED at a time
int steps [] = {1, 2, 4, 8, 16, 32, 64, 128};

byte empty = 0x00;
byte full = 0xFF;

int readSpeedPot() {
  int speedPotVal = analogRead(spdPot);
  int speed = (speedPotVal / 6) + 1;
  return speed;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(serPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(oePin, OUTPUT);
}

void loop() {

  for (int i=0; i<num_sr; i++) { // one outer loop per shift register
    // prints for debugging
    Serial.print("Shift Register ");
    Serial.println(i);

    // inner loop, number of LEDs per shift register
    for (int d=0; d<num_led; d++) { 
      // prints for debugging
      Serial.print("LED ");
      Serial.println(d);
      
      // set latch low to shift in bits
      digitalWrite(latchPin, LOW);

      if (i == 0) {
        for (int r=0; r<num_sr-1; r++) {
          shiftOut(serPin, clkPin, MSBFIRST, empty);  
        }
        shiftOut(serPin, clkPin, MSBFIRST, steps[d]);
        } else {
          for (int t=0; t<num_sr-(i+1); t++) {
            shiftOut(serPin, clkPin, MSBFIRST, empty);  
          }
          // then shift in the 8 bits
          shiftOut(serPin, clkPin, MSBFIRST, steps[d]);
          // first, shift in 8 empty bits i number of times
          for (int r=0; r<i; r++) {
            shiftOut(serPin, clkPin, MSBFIRST, empty);  
          }      
        }
        digitalWrite(latchPin, HIGH);
        delay(dt);
      }
    }
}


    // for the first one(i=0), can just send in the 8 bits, then num_sr - 1 empty bytes
    // then i=1 for example, need to first do i bytes empty, then 8 real, then num_sr-(i+1)
  //   if (i == 0) {
  //     shiftOut(serPin, clkPin, LSBFIRST, steps[d]);
  //     for (int r=0; r<num_sr-1; r++) {
  //       shiftOut(serPin, clkPin, LSBFIRST, empty);  
  //     }
      
  //     } else {
  //       // first, shift in 8 empty bits i number of times
  //       for (int r=0; r<i; r++) {
  //         shiftOut(serPin, clkPin, LSBFIRST, empty);  
  //       }
  //       // then shift in the 8 bits
  //       shiftOut(serPin, clkPin, LSBFIRST, steps[d]);
  //       // then fill remaining shift registers with num_sr - (i+1) more empty bytes
  
  //       for (int t=0; t<num_sr-(i+1); t++) {
  //         shiftOut(serPin, clkPin, LSBFIRST, empty);  
  //       }
  //     }
      
  //     digitalWrite(latchPin, HIGH);
  //     delay(dt);
  //   }
  // }