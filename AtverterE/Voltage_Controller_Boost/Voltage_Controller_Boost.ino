/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Output Voltage Controller for Buck Converter
  
*/

#include <AtverterE.h>

#define INTERRUPT_TIME 1

AtverterE atverterE;
int ledState = HIGH;

uint16_t dutyCycle;
//int32_t lowVoltage;         //Input Voltage
int32_t highVoltage;        //Output Voltage
int32_t actualHighVoltage;  //Actual Output Voltage

// Control gain variables
//Atverter 1
// const double kp = 0.65;  // Proportional Control: kp * error
// const double ki = 0.1;   // Integral Control: summation of (ki * error * sample_time)
// const double kd = 0.0;   // Derivative Control: 

//Atverter 2
const double kp = 0.65;  // Proportional Control: kp * error
const double ki = 0.04;   // Integral Control: summation of (ki * error * sample_time)
const double kd = 0.0;   // Derivative Control: 

double integralControl = 0.0;
int32_t prevVoltageError = 0;


void setup(void) {
  highVoltage = 20000;  //Desired output voltage eventually find a way to get this value from the user
  //int32_t lowVoltage = atverterE.getActualVL();

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(INTERRUPT_TIME, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  dutyCycle = (highVoltage - atverterE.getActualVL()) * 1024 / highVoltage;  //(Vo - Vi) / Vo
  //dutyCycle = 100;
  atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();
}

void loop(void) {
}

void controlUpdate(void) {
  // Depending on which Atverter you are using
  //actualHighVoltage = ((double)atverterE.getActualVH() * 1.02) - 92; // Atverter1
  //actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36; // Atverter1
  //actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104; // Atverter2
  actualHighVoltage = ((double)atverterE.getActualVH() * 0.92) + 20;  // Atverter2

  Serial.print("Actual High Voltage: ");
  Serial.print(actualHighVoltage);
  Serial.print("\n\n");

  // Static variables used in the
  
  int32_t voltageError = highVoltage - actualHighVoltage;             // Instantaneous error of the desired output versus actual output voltage

  // Allows for us to convert from voltage error to dutycycle error
  // Negative sign used since boost converter is inversely proportional to dutycycle
  double proportionalControl = -(kp * ((double)voltageError / (double)actualHighVoltage));  // Proportional control: -kp * percent error
  Serial.print("Proportional Control: ");
  Serial.print(proportionalControl);
  Serial.print("\n\n");

  integralControl += -(ki * ((double)voltageError * (double)INTERRUPT_TIME / (double)actualHighVoltage));  // Integral control: -ki * (dutycycle) * percent error * sample_time
  Serial.print("Integral Control: ");
  Serial.print(integralControl);
  Serial.print("\n\n");

  double derivativeControl = -(kd * ((double)(voltageError - prevVoltageError) / (double)INTERRUPT_TIME)); // Derivative control: -kd * (error - prev_error) / sample_time
  //derivativeControl = constrain(derivativeControl, -0.5, 0.5);
  // Serial.print("Derivative Control: ");
  // Serial.print(derivativeControl);
  // Serial.print("\n\n");


  prevVoltageError = voltageError;

  /*
  // Use the moving average filter
  SUM = SUM - READINGS[INDEX];        // Remove the oldest entry from the sum
  VALUE = actualHighVoltage;           // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;            // Add the newest reading to the window
  SUM = SUM + VALUE;                  // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;       // Divide the sum of the window by the window size for the result
*/

  // Serial.print("\n\n");
  // Serial.print(VALUE);
  // Serial.print(",");
  // Serial.print(SUM);
  // Serial.print(",");
  //Serial.print(AVERAGED);
  // Serial.print(" ");
  //Serial.print("\n\n");
  
  Serial.print("dutyCycle: ");
  Serial.print(dutyCycle);
  Serial.print("\n\n");
  dutyCycle += (double)dutyCycle * (proportionalControl + integralControl + derivativeControl);
  Serial.print("dutyCycle: ");
  Serial.print(dutyCycle);
  Serial.print("\n\n");

  //dutyCycle = constrain(dutyCycle, 10, 1014);

  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(constrain(dutyCycle, 10, 1014));
  //atverterE.setDutyCycle(400);
  //Serial.println(highVoltage);
  //Serial.println(dutyCycle);
  // Serial.print("PWM Duty Cycle = ");
  Serial.print(atverterE.getDutyCycle());
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
  Serial.print("\n\n");
  //ledState = !ledState;
}




/*
#include <AtverterE.h>

#define OUTPUT_VOLTAGE_STEADY_STATE 999
#define WINDOW_SIZE 50

AtverterE atverterE;
int ledState = HIGH;

uint16_t dutyCycle;
uint32_t lowVoltage;   //Input Voltage
uint32_t highVoltage;  //Output Voltage
uint32_t actualHighVoltage;  //Actual Output Voltage

int INDEX = 0;
uint32_t VALUE = 0;
uint32_t SUM = 0;
uint32_t READINGS[WINDOW_SIZE];
uint32_t AVERAGED = 0;



void setup(void) {
  highVoltage = 42000;                              //Desired output voltage eventually find a way to get this value from the user
  lowVoltage = atverterE.getActualVL();

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(1, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  dutyCycle = (highVoltage - lowVoltage) * 1024 / highVoltage; //(Vo - Vi) / Vo
  //dutyCycle = 100;
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

    if ((AVERAGED < highVoltage) && (dutyCycle > 10)) {
      dutyCycle -= 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      //Serial.print("HI");
    }

    else if ((AVERAGED > highVoltage) && (dutyCycle < 1014)) {
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
  //Serial.print(AVERAGED);
  // Serial.print(" ");
  //Serial.print("\n\n");


  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(dutyCycle);
  //atverterE.setDutyCycle(400);
  //Serial.println(highVoltage);
  // //Serial.println(voltageRatio);
  //Serial.println(dutyCycle);
  // Serial.print("PWM Duty Cycle = ");
  Serial.print(atverterE.getDutyCycle());
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
  Serial.print("\n\n");
  //ledState = !ledState;
}
*/