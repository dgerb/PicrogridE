/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Output Voltage Controller for Buck Converter
  
*/

#include <AtverterE.h>

#define INPUT_VOLTAGE_JUMP 999
#define OUTPUT_VOLTAGE_JUMP 499
#define OUTPUT_VOLTAGE_STEADY_STATE 99
#define WINDOW_SIZE 100

AtverterE atverterE;
int ledState = HIGH;

uint16_t dutyCycle;
uint32_t lowVoltage;   //Output Voltage
uint32_t highVoltage;  //Input Voltage

int INDEX = 0;
uint32_t VALUE = 0;
uint32_t SUM = 0;
uint32_t READINGS[WINDOW_SIZE];
uint32_t AVERAGED = 0;



void setup(void) {
  lowVoltage = 5000;                              //Desired output voltage eventually find a way to get this value from the user
  highVoltage = atverterE.getActualVH();          //Input voltage that is recovered from the
  dutyCycle = (lowVoltage * 1024 / highVoltage);  // * 1024; //buck duty cycle equation

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(1, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();
}

void loop(void) {
}

void controlUpdate(void) {

  SUM = SUM - READINGS[INDEX];                               // Remove the oldest entry from the sum
  VALUE = ((double)atverterE.getActualVH() * 0.9861) + 290;  // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;                                   // Add the newest reading to the window
  SUM = SUM + VALUE;                                         // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;                         // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;                              // Divide the sum of the window by the window size for the result

  Serial.print("\n\n");
  Serial.print("Average High Voltage: ");
  Serial.print(AVERAGED);
  Serial.print("\n\n");

  //atverterE.setDutyCycle(dutyCycle);
  Serial.print("PWM Duty Cycle = ");
  Serial.print(atverterE.getDutyCycle());
  Serial.print("/1024, VH = ");
  Serial.print(atverterE.getActualVH());
  Serial.print("mV, IH = ");
  Serial.print(atverterE.getIH());
  Serial.print("mA, VL = ");
  Serial.print(atverterE.getActualVL());
  Serial.print("mV, IL = ");
  Serial.print(atverterE.getIL());
  Serial.println("mA");
  atverterE.setLED(LED1G_PIN, ledState);
  Serial.print("\n\n");
  ledState = !ledState;
}