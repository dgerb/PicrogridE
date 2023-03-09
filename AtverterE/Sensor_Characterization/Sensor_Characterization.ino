/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Output Voltage Controller for Buck Converter
  
*/

#include <AtverterE.h>

#define INPUT_VOLTAGE_JUMP 999
#define OUTPUT_VOLTAGE_JUMP 499
#define OUTPUT_VOLTAGE_STEADY_STATE 99
#define WINDOW_SIZE 150

AtverterE atverterE;
int ledState = HIGH;

uint16_t dutyCycle;
uint32_t lowVoltage;   //Output Voltage
uint32_t highVoltage;  //Input Voltage

int INDEX = 0;
uint32_t VALUE1 = 0;
uint32_t SUM1 = 0;
uint32_t READINGS1[WINDOW_SIZE];
uint32_t AVERAGED1 = 0;

uint32_t VALUE2 = 0;
uint32_t SUM2 = 0;
uint32_t READINGS2[WINDOW_SIZE];
uint32_t AVERAGED2 = 0;



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


  SUM1 = SUM1 - READINGS1[INDEX];
  SUM2 = SUM2 - READINGS2[INDEX];
  VALUE1 = ((double)atverterE.getActualVH() * 1.02) - 92;   // Collect the actual low voltage value
  VALUE2 = ((double)atverterE.getActualVL() * 1.03) + 36;   // Collect the actual low voltage value
  READINGS1[INDEX] = VALUE1;          // Add the newest reading to the window
  READINGS2[INDEX] = VALUE2;          // Add the newest reading to the window
  SUM1 = SUM1 + VALUE1;               // Add the newest reading to the sum
  SUM2 = SUM2 + VALUE2;               // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED1 = SUM1 / WINDOW_SIZE;     // Divide the sum of the window by the window size for the result
  AVERAGED2 = SUM2 / WINDOW_SIZE;

  Serial.print("\n\n");
  Serial.print("Average High Voltage: ");
  Serial.print(AVERAGED1);
  Serial.print(";     Average Low Voltage: ");
  Serial.print(AVERAGED2);
  Serial.print("\n\n");

  //atverterE.setDutyCycle(dutyCycle);
  // Serial.print("PWM Duty Cycle = ");
  // Serial.print(atverterE.getDutyCycle());
  // Serial.print("/1024, VH = ");
  // Serial.print(atverterE.getActualVH());
  // Serial.print("mV, IH = ");
  // Serial.print(atverterE.getIH());
  // Serial.print("mA, VL = ");
  // Serial.print(atverterE.getActualVL());
  // Serial.print("mV, IL = ");
  // Serial.print(atverterE.getIL());
  // Serial.println("mA");
  // atverterE.setLED(LED1G_PIN, ledState);
  // Serial.print("\n\n");
  // ledState = !ledState;
}