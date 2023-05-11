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
    AtverterE(); // constructor
  // Atmega initialization
    void setupPinMode(); // sets appropriate pinMode() for each const pin
    void initializePWMTimer(); // starts the PWM timer at 62.5 kHz

    void initializeInterruptTimer(int periodms, // starts periodic control timer
      void (*interruptFunction)(void)); // inputs: period (ms), controller function reference
      
    //void initializeInterruptTimer(int periodms, void interruptFunction());
    //void initializeInterruptVoltageBuck(int periodms, void (Voltage_Controller_Buck::*methodPtr)());
    void startPWM(); // resets protection latch, enabling the gate driver
  // duty cycle
    void setDutyCycle(int dutyCycle); // sets duty cycle (0 to 1023)
    void setDutyCycleFloat(float dutyCycleFloat); // sets duty cycle (0.0 to 1.0)
    int getDutyCycle(); // gets the current duty cycle (0 to 1023)
    float getDutyCycleFloat(); // gets the current duty cycle (0.0 to 1.0)
  // voltages and current sensing
    int getRawVH(); // gets high side voltage (0 to 1023)
    int getVH(); // gets high side voltage (mV) measured at ADC
    unsigned int getActualVH(); // gets high side voltage (mV) at terminal
    int getRawIH(); // gets high side current (0 to 1023)
    int getIH(); // gets high side current (mA) (-5000 to 5000)
    int getRawVL(); // gets low side voltage (0 to 1023)
    int getVL(); // gets low side voltage (mV) measured at ADC
    unsigned int getActualVL(); // gets low side voltage (mV) at terminal
    int getRawIL(); // gets low side current (0 to 1023)
    int getIL(); // gets low side current (mA) (-5000 to 5000)
  // diagnostics
    void setLED(int led, int state); // sets an LED to HIGH or LOW
  private:
    int _dutyCycle = 512; // the most recently set duty cycle (0 to 1023)
    int raw2mV(int raw); // converts raw ADC voltage to mV
    unsigned int raw2mVActual(int raw); // also scales raw2mV by resistor divider
    int raw2mA(int raw); // converts raw ADC current sense output to mA
};


#endif
