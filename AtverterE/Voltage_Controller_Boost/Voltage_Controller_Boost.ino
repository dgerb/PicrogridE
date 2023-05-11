/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Output Voltage Controller for Buck Converter
  
*/

#include <AtverterE.h>

#define OUTPUT_VOLTAGE_STEADY_STATE 499
#define WINDOW_SIZE 50

AtverterE atverterE;
int ledState = HIGH;

uint16_t dutyCycle = 200;
uint32_t lowVoltage;   //Input Voltage
uint32_t highVoltage;  //Output Voltage
uint32_t actualHighVoltage;  //Actual Output Voltage

int INDEX = 0;
uint32_t VALUE = 0;
uint32_t SUM = 0;
uint32_t READINGS[WINDOW_SIZE];
uint32_t AVERAGED = 0;



void setup(void) {
  highVoltage = 5000;                              //Desired output voltage eventually find a way to get this value from the user

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(1, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();
  
}

void loop(void) {
}

void controlUpdate(void) {
  //highVoltage = ((double)atverterE.getActualVH() * 1.02) - 92; // Atverter1
  //actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36; // Atverter1 
  //actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104; // Atverter2
  actualHighVoltage = ((double)atverterE.getActualVH() * 0.92) + 20; // Atverter2

  if ((abs((int32_t)AVERAGED - (int32_t)highVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)) {

    if ((actualHighVoltage < highVoltage) && (dutyCycle > 0)) {
      dutyCycle -= 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      //Serial.print("HI");
    }

    else if ((actualHighVoltage > highVoltage) && (dutyCycle < 1024)) {
      dutyCycle += 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      //Serial.print("Hello");
    }
  }

  // Use the moving average filter
  SUM = SUM - READINGS[INDEX];        // Remove the oldest entry from the sum
  VALUE = actualHighVoltage;           // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;            // Add the newest reading to the window
  SUM = SUM + VALUE;                  // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;       // Divide the sum of the window by the window size for the result

  // Serial.print("\n\n");
  // Serial.print(VALUE);
  // Serial.print(",");
  // Serial.print(SUM);
  // Serial.print(",");
  Serial.print(AVERAGED);
  // Serial.print(" ");
  Serial.print("\n\n");


  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(dutyCycle);
  //atverterE.setDutyCycle(400);
  //Serial.println(highVoltage);
  // //Serial.println(voltageRatio);
  //Serial.println(dutyCycle);
  // Serial.print("PWM Duty Cycle = ");
  Serial.print(atverterE.getDutyCycle());
  Serial.print("/1024, VH = ");
  //Serial.print(atverterE.getActualVH());
  // Serial.print("mV, IH = ");
  // Serial.print(atverterE.getIH());
  // Serial.print("mA, VL = ");
  // Serial.print(atverterE.getActualVL());
  // Serial.print("mV, IL = ");
  // Serial.print(atverterE.getIL());
  // Serial.println("mA");
  // atverterE.setLED(LED1G_PIN, ledState);
  Serial.print("\n\n");
  ledState = !ledState;
}