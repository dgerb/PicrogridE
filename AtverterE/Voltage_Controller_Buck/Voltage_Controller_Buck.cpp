#include "Voltage_Controller_Buck.h"

Voltage_Controller_Buck::Voltage_Controller_Buck() {}

void Voltage_Controller_Buck::begin() {
  lowVoltage = 5000;                              //Desired output voltage eventually find a way to get this value from the user

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(1, &Voltage_Controller_Buck::update);  //Get interrupts enabled
  Serial.begin(9600);

  atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();
}

void Voltage_Controller_Buck::update() {
  //actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36; // Atverter1 
  actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104; // Atverter2

  if ((abs((int32_t)AVERAGED - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)/* && (abs((int32_t)actualLowVoltage - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)*/) {

    if ((actualLowVoltage < lowVoltage)) {
      dutyCycle += 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
    }

    else if ((actualLowVoltage > lowVoltage)) {
      dutyCycle -= 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
    }
  }

  // Use the moving average filter
  SUM = SUM - READINGS[INDEX];        // Remove the oldest entry from the sum
  VALUE = actualLowVoltage;           // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;            // Add the newest reading to the window
  SUM = SUM + VALUE;                  // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;       // Divide the sum of the window by the window size for the result

  atverterE.setDutyCycle(dutyCycle);
  ledState = !ledState;
}
