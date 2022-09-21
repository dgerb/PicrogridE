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

// In Arduino IDE, go to Sketch -> Include Library -> Manage Libraries
#include <TimerOne.h> // In Library Manager, search for "TimerOne"
#include <MsTimer2.h> // In Library Manager, search for "MsTimer2"
#include <SystemStatus.h> // In Library Manager, search for "MsTimer2"


// pins for turning on the LEDs
const int LED1R_PIN = 2; // Physical pin 4
const int LED1G_PIN = 3; // Physical pin 5
const int LED2R_PIN = 6; // Physical pin 12
const int LED2G_PIN = 7; // Physical pin 13

// Atmega328p (Arduino Uno):
// Pins 5 and 6: controlled by Timer 0 (8 MHz)
// Pins 9 and 10: controlled by Timer 1 (16 MHz)
// Pins 11 and 3: controlled by Timer 2 (8 MHz)
const int PWM_PIN = 9; // Physical pin 15, timer 1

// pin to reset the protection circuit, enabling the gate driver
const int PRORESET_PIN = 4; // Physical pin 6

// pins for voltage and current sensing
const int VH_PIN = 14; // physical pin 23, attenuated high side voltage
const int IH_PIN = 15; // physical pin 24, high side current sensor output
const int VL_PIN = 16; // physical pin 25, attenuated low side voltage
const int IL_PIN = 17; // physical pin 26, low side current sensor output

// moving average window length for voltages and currents
const int AVGWIN = 10;

class AtverterE
{
  public:
    AtverterE();
    void setupPinMode();
    void initializePWMTimer();
    void initializeInterruptTimer(int periodms, void (*interruptFunction)(void));
    void startPWM();
    void setDutyCycle(int dutyCycle);
    void setDutyCycleFloat(float dutyCycleFloat);
    int getDutyCycle();
    float getDutyCycleFloat();
    void setLED(int led, int state);
    int raw2mV(int raw);
    unsigned int raw2mVActual(int raw);
    int raw2mA(int raw);
    int getRawVH();
    int getVH();
    unsigned int getActualVH();
    int getRawIH();
    int getIH();
    int getRawVL();
    int getVL();
    unsigned int getActualVL();
    int getRawIL();
    int getIL();
  private:
    int _dutyCycle = 512; // Timer1 library uses 10-bit (1024 value) PWM
    int _vHaverage = 0; // high side voltage mV
    int _iHaverage = 0; // high side current mA
    int _vLaverage = 0; // low side voltage mV
    int _iLaverage = 0; // low side current mA
};


#endif
