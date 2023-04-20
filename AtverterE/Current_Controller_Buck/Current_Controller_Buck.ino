/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Output Voltage Controller for Buck Converter
  
*/

#include <AtverterE.h>

#define INPUT_VOLTAGE_JUMP 999
#define OUTPUT_VOLTAGE_JUMP 499
#define OUTPUT_CURRENT_STEADY_STATE 99
#define WINDOW_SIZE 50

AtverterE atverterE;
int ledState = HIGH;

uint16_t dutyCycle;
uint32_t lowVoltage;   //Output Voltage
uint32_t highVoltage;  //Input Voltage
uint32_t prevHighVoltage = 0;
//double voltageRatio; // lowVoltage / highVoltage
uint32_t actualLowVoltage;  //Actual Output Voltage
int32_t lowCurrent;         //Output Current
int32_t actualLowCurrent;   //Actual Output Current

int INDEX = 0;
int32_t VALUE = 0;
int32_t SUM = 0;
int32_t READINGS[WINDOW_SIZE];
int32_t AVERAGED = 0;



void setup(void) {
  lowVoltage = 5000;  //Desired output voltage eventually find a way to get this value from the user
  lowCurrent = 2000;
  highVoltage = atverterE.getActualVH();          //Input voltage that is recovered from the
  dutyCycle = (lowVoltage * 1024 / highVoltage);  // * 1024; //buck duty cycle equation

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(1, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  //atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();
}

void loop(void) {
}

void controlUpdate(void) {
  highVoltage = atverterE.getActualVH();
  //actualLowVoltage = atverterE.getActualVL();
  actualLowCurrent = ((double)(-atverterE.getIL()) * 1.05) + 29;  // Negative since hall effect sensor put in backwards

  //if (abs((int32_t)highVoltage - (int32_t)prevHighVoltage) > INPUT_VOLTAGE_JUMP) {
  //  dutyCycle = (lowVoltage * 1024 / highVoltage);  // * 1024;
  // Serial.println("change detected");
  // Serial.println(highVoltage - prevHighVoltage);
  //SUM = READINGS[INDEX];
  //  prevHighVoltage = highVoltage;
  //} else if ((abs(AVERAGED - lowCurrent) > OUTPUT_CURRENT_STEADY_STATE) && (abs(actualLowCurrent - lowCurrent) > OUTPUT_CURRENT_STEADY_STATE)) {
  if ((abs(AVERAGED - lowCurrent) > OUTPUT_CURRENT_STEADY_STATE)/* && (abs(actualLowCurrent - lowCurrent) > OUTPUT_CURRENT_STEADY_STATE)*/) {
    // Serial.print("\n\n");
    // Serial.print("TRIGGERED");
    // Serial.print(", ");
    // Serial.print(actualLowVoltage);
    // Serial.print(", ");
    // Serial.print(AVERAGED);
    // Serial.print(", ");
    // Serial.print(abs(AVERAGED - lowCurrent));
    // Serial.print(", ");
    // Serial.print(abs(actualLowCurrent - lowCurrent));
    // Serial.print("\n\n");


    if ((actualLowCurrent < lowCurrent)) {
      dutyCycle += 1;                                 // If the output voltage is close to desired output then slowly move towards the more desired value
      //lowVoltage = (dutyCycle * highVoltage) / 1024;  // Update lowVoltage value
    } else if ((actualLowCurrent > lowCurrent)) {
      dutyCycle -= 1;                                 // If the output voltage is close to desired output then slowly move towards the more desired value
      //lowVoltage = (dutyCycle * highVoltage) / 1024;  // Update lowVoltage value
    }
  }

  // Use the moving average filter
  SUM = SUM - READINGS[INDEX];        // Remove the oldest entry from the sum
  VALUE = actualLowCurrent;           // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;            // Add the newest reading to the window
  SUM = SUM + VALUE;                  // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;       // Divide the sum of the window by the window size for the result

  //Serial.print("\n\n");
  //Serial.print(VALUE);
  //Serial.print(",");
  //Serial.print(SUM);
  //Serial.print(",");
  //Serial.print(AVERAGED);
  //Serial.print("\n\n");


  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(dutyCycle);
  //atverterE.setDutyCycle(600);
  //Serial.print("PWM Duty Cycle = ");
  Serial.print(atverterE.getDutyCycle());
  Serial.print("\n");
  //Serial.print("/1024, VH = ");
  // Serial.print(atverterE.getActualVH());
  // Serial.print("mV, IH = ");
  // Serial.print(atverterE.getIH());
  // Serial.print("mA, VL = ");
  // Serial.print(atverterE.getActualVL());
  // Serial.print("mV, IL = ");
  Serial.print(atverterE.getIL());
  // Serial.println("mA");
  // atverterE.setLED(LED1G_PIN, ledState);
  Serial.print("\n\n");
  ledState = !ledState;
}