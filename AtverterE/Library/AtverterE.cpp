/*
  AtverterE.cpp - Library for AtverterE pin and function mapping
  Created by Daniel Gerber, 9/19/22
  Released into the public domain.
*/

// https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

#include "Arduino.h"
#include "AtverterE.h"

AtverterE::AtverterE()
{
}

// sets up the pin mode for all AtverterE pins
void AtverterE::setupPinMode()
{
  pinMode(LED1R, OUTPUT);
  pinMode(LED1G, OUTPUT);
  pinMode(LED2R, OUTPUT);
  pinMode(LED2G, OUTPUT);
}
