/*
  AtverterE.h - Library for AtverterE pin and function mapping
  Created by Daniel Gerber, 9/19/22
  Released into the public domain.

*/

// Simply open the Arduino IDE, click on “Sketch” > “Include Library” > “Add .ZIP Library…”, and browse to find your .zip archive.
// https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

#ifndef AtverterE_h
#define AtverterE_h

#include "Arduino.h"

const int LED1R = 2; // Physical pin 4
const int LED1G = 3; // Physical pin 5
const int LED2R = 6; // Physical pin 12
const int LED2G = 7; // Physical pin 13

class AtverterE
{
  public:
    AtverterE();
    void setupPinMode();
};

#endif
