/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Output Voltage Controller for Buck Converter
  
*/

#ifndef VOLTAGE_CONTROLLER_BUCK_H
#define VOLTAGE_CONTROLLER_BUCK_H

#include "Arduino.h"
#include <AtverterE.h>

#define INPUT_VOLTAGE_JUMP 999
#define OUTPUT_VOLTAGE_JUMP 499
#define OUTPUT_VOLTAGE_STEADY_STATE 99
#define WINDOW_SIZE 50

class Voltage_Controller_Buck {
  public:
    Voltage_Controller_Buck();
    void begin();
    void update();
  private:
    AtverterE atverterE;
    uint16_t dutyCycle; //Dutycyle of the switches
    uint32_t lowVoltage;   //Output Voltage
    uint32_t highVoltage;  //Input Voltage
    uint32_t prevHighVoltage = 0;
    uint32_t actualLowVoltage;  //Actual Output Voltage

    int INDEX = 0;
    uint32_t VALUE = 0;
    uint32_t SUM = 0;
    uint32_t READINGS[WINDOW_SIZE];
    uint32_t AVERAGED = 0;
};

#endif
