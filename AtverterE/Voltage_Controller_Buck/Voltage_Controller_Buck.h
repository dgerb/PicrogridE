#ifndef Voltage_Controller_Buck_h
#define Voltage_Controller_Buck_h

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
    uint32_t getOutputVoltage();
private:
    AtverterE atverterE;
    uint16_t dutyCycle;
    uint32_t lowVoltage;   
    uint32_t highVoltage;  
    uint32_t prevHighVoltage = 0;
    uint32_t actualLowVoltage;  
    int INDEX = 0;
    uint32_t VALUE = 0;
    uint32_t SUM = 0;
    uint32_t READINGS[WINDOW_SIZE];
    uint32_t AVERAGED = 0;
};

#endif
