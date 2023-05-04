#include "Voltage_Controller_Buck.h"

Voltage_Controller_Buck::Voltage_Controller_Buck() {
    lowVoltage = 5000;                              
    atverterE.setupPinMode();        
    atverterE.initializePWMTimer();  
    atverterE.initializeInterruptTimer(1, &Voltage_Controller_Buck::update);  
    Serial.begin(9600);
    atverterE.setDutyCycle(dutyCycle);
    atverterE.startPWM();
}

void Voltage_Controller_Buck::begin() {
}

void Voltage_Controller_Buck::update() {
    actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104;

    if ((abs((int32_t)AVERAGED - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)) {
        if ((actualLowVoltage < lowVoltage)) {
            dutyCycle += 1;
        }
        else if ((actualLowVoltage > lowVoltage)) {
            dutyCycle -= 1;
        }
    }

    SUM = SUM - READINGS[INDEX];
    VALUE = actualLowVoltage;
    READINGS[INDEX] = VALUE;
    SUM = SUM + VALUE;
    INDEX = (INDEX + 1) % WINDOW_SIZE;
    AVERAGED = SUM / WINDOW_SIZE;

    atverterE.setDutyCycle(dutyCycle);
}

uint32_t Voltage_Controller_Buck::getOutputVoltage() {
    return AVERAGED;
}
