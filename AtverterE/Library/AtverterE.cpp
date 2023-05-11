/*
  AtverterE.cpp - Library for AtverterE pin and function mapping
  Created by Daniel Gerber, 9/19/22
  Released into the public domain.
*/

// https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

#include "AtverterE.h"

AtverterE::AtverterE()
{
}

// sets up the pin mode for all AtverterE pins
void AtverterE::setupPinMode()
{
  pinMode(LED1R_PIN, OUTPUT);
  pinMode(LED1G_PIN, OUTPUT);
  pinMode(LED2R_PIN, OUTPUT);
  pinMode(LED2G_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(PRORESET_PIN, OUTPUT);
  pinMode(VH_PIN, INPUT);
  pinMode(IH_PIN, INPUT);
  pinMode(VL_PIN, INPUT);
  pinMode(IL_PIN, INPUT);
}

// intializes timer 1 as PWM timer and timer 2 as control interrupt timer
void AtverterE::initializePWMTimer()
{
  // Timer1.intialize(period in microseconds)
  // 16 us = 62.5 kHz: highest frequency for 7-bit (128 values) PWM resolution
  // For 16 us, dutyCycle is in increments of 8 (out of 1024)
  Timer1.initialize(16);
}

// initializes timer 2 as the periodic control timer
// inputs: control period in milliseconds, controller interrupt function reference
// example usage: atverterE.initializeInterruptTimer(1, &controlUpdate);

void AtverterE::initializeInterruptTimer(int periodms, void interruptFunction())
{
  // MsTimer2::set(period in milliseconds, interrupt function to call)
  MsTimer2::set(periodms, interruptFunction);
  MsTimer2::start(); // start timer 2 and interrupt handler
}

// intializes timer 1 as PWM timer and timer 2 as control interrupt timer
void AtverterE::startPWM()
{
  digitalWrite(PRORESET_PIN, HIGH);
  delayMicroseconds(500);
  digitalWrite(PRORESET_PIN, LOW);
}

// sets the duty cycle, integer argument (0-1023)
void AtverterE::setDutyCycle(int dutyCycle)
{
  _dutyCycle = dutyCycle;
  // Timer1.pwm(pin number, duty cycle 0-1023)
  Timer1.pwm(PWM_PIN, dutyCycle);
}

// sets the duty cycle, float argument (0.0-1.0)
void AtverterE::setDutyCycleFloat(float dutyCycleFloat)
{
  setDutyCycle((int)(dutyCycleFloat * 1024));
}

// get the duty cycle as a 10-bit int (0-1023)
int AtverterE::getDutyCycle()
{
  return _dutyCycle;
}

// get the duty cycle as a float (0.0-1.0)
float AtverterE::getDutyCycleFloat()
{
  return ((float)getDutyCycle() / 1024.0);
}

// sets one of the LEDs to a given state (HIGH or LOW)
void AtverterE::setLED(int led, int state)
{
  digitalWrite(led, state);
}

// converts a raw 10-bit analog reading (0-1023) to a mV reading (0-5000)
// assumes VCC = 5V; if not the case, will have to readVCC
int AtverterE::raw2mV(int raw)
{
  long rawL = (long)raw;
  return rawL * 5000 / 1024; // analogRead/1024*VCC
}

// converts a raw 10-bit analog reading (0-1023) to the actual mV (0-65000)
// assumes VCC = 5V; if not the case, will have to readVCC
unsigned int AtverterE::raw2mVActual(int raw)
{
  long rawL = (long)raw;
  return (unsigned int)(rawL * 8125 / 128); // analogRead/1024*VCC * (120k+10k)/10k
}

// converts a raw 10-bit analog reading (0-1023) to a mA reading (-5000 to 5000)
// conversion based on current sensor 400mV/1000mA, 0A=2.5V
// assumes VCC = 5V; if not the case, will have to readVCC
int AtverterE::raw2mA(int raw)
{
  long rawL = (long)raw;
  return (rawL - 512) * 3125 / 256; // (analogRead/1024*VCC - 2500)*1000/400
}

// get the raw high side voltage (0-1023)
int AtverterE::getRawVH()
{
  return analogRead(VH_PIN);
}

// get the high side voltage (mV) (0-5000)
int AtverterE::getVH()
{
  return raw2mV(getRawVH());
}

// get the high side voltage (mV) (0-65000)
unsigned int AtverterE::getActualVH()
{
  return raw2mVActual(getRawVH());
}

// get the raw high side current (0-1023)
int AtverterE::getRawIH()
{
  return analogRead(IH_PIN);
}

// get the high side current (mA) (-5000 to 5000)
int AtverterE::getIH()
{
  return raw2mA(getRawIH());
}

// get the raw low side voltage (0-1023)
int AtverterE::getRawVL()
{
  return analogRead(VL_PIN);
}

// get the low side voltage (mV) (0-5000)
int AtverterE::getVL()
{
  return raw2mV(getRawVL());
}

// get the low side voltage (mV) (0-65000)
unsigned int AtverterE::getActualVL()
{
  return raw2mVActual(getRawVL());
}

// get the raw low side current (0-1023)
int AtverterE::getRawIL()
{
  return analogRead(IL_PIN);
}

// get the low side current (mA) (-5000 to 5000)
int AtverterE::getIL()
{
  return raw2mA(getRawIL());
}

/*
// returns the VCC voltage in miliVolts
long AtverterE::readVCC() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
     ADMUX = _BV(MUX5) | _BV(MUX0) ;
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif

  delayMicroseconds(100); // Wait for Vref to settle (originally 2 ms delay)
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}
*/
