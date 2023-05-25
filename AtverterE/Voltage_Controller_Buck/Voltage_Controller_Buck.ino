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
int32_t lowVoltage;         //Output Voltage
int32_t highVoltage;        //Input Voltage
int32_t actualLowVoltage;  //Actual Output Voltage

// Control gain variables
const double kp = 0.65;   // Proportional Control: kp * error
const double ki = 0.0;  // Integral Control: summation of (ki * error * sample_time)
const double kd = 0.0;   // Derivative Control:

double integralControl = 0.0;
int32_t prevVoltageError = 0;


void setup(void) {
  lowVoltage = 10000;  //Desired output voltage eventually find a way to get this value from the user
  highVoltage = atverterE.getActualVL();

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(INTERRUPT_TIME, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  dutyCycle = (lowVoltage * 1024) / highVoltage;
  //dutyCycle = 100;
  atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();
}

void loop(void) {
}

void controlUpdate(void) {
  // Depending on which Atverter you are using
  //highVoltage = ((double)atverterE.getActualVH() * 1.02) - 92; // Atverter1
  actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36; // Atverter1
  //actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104; // Atverter2
  //actualHighVoltage = ((double)atverterE.getActualVH() * 0.92) + 20;  // Atverter2

  // Static variables used in the

  int32_t voltageError = lowVoltage - actualLowVoltage;  // Instantaneous error of the desired output versus actual output voltage
  Serial.print("Voltage Error: ");
  Serial.print(voltageError);
  Serial.print("\n\n");

  // Allows for us to convert from voltage error to dutycycle error
  // Negative sign used since boost converter is inversely proportional to dutycycle
  double proportionalControl = (kp * ((double)voltageError / (double)actualLowVoltage));  // Proportional control: -kp * percent error
  // Serial.print("Proportional Control: ");
  // Serial.print(proportionalControl);
  // Serial.print("\n\n");

  integralControl += (ki * ((double)voltageError * (double)INTERRUPT_TIME / (double)actualLowVoltage));  // Integral control: -ki * (dutycycle) * percent error * sample_time
  Serial.print("Integral Control: ");
  Serial.print(integralControl);
  Serial.print("\n\n");

  //double derivativeControl = (kd * ((double)(voltageError - prevVoltageError) / (double)INTERRUPT_TIME));  // Derivative control: -kd * (error - prev_error) / sample_time
  //derivativeControl = constrain(derivativeControl, -0.5, 0.5);
  // Serial.print("Derivative Control: ");
  // Serial.print(derivativeControl);
  // Serial.print("\n\n");

  //prevVoltageError = voltageError;

  // Serial.print("dutyCycle: ");
  // Serial.print(dutyCycle);
  // Serial.print("\n\n");
  dutyCycle += (double)dutyCycle * (proportionalControl + integralControl/* + derivativeControl*/);
  // Serial.print("dutyCycle: ");
  // Serial.print(dutyCycle);
  // Serial.print("\n\n");

  //dutyCycle = constrain(dutyCycle, 10, 1014);

  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(constrain(dutyCycle, 10, 1014));
  //atverterE.setDutyCycle(400);
  //Serial.println(highVoltage);
  //Serial.println(dutyCycle);
  // Serial.print("PWM Duty Cycle = ");
  //Serial.print(atverterE.getDutyCycle());
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
  //Serial.print("\n\n");
  //ledState = !ledState;
}


/*
#include <AtverterE.h>

#define INPUT_VOLTAGE_JUMP 999
#define OUTPUT_VOLTAGE_JUMP 499
#define OUTPUT_VOLTAGE_STEADY_STATE 99
#define WINDOW_SIZE 50

AtverterE atverterE;
int ledState = HIGH;

uint16_t dutyCycle;
uint32_t lowVoltage;   //Output Voltage
uint32_t highVoltage;  //Input Voltage
uint32_t prevHighVoltage = 0;
//double voltageRatio; // lowVoltage / highVoltage
uint32_t actualLowVoltage;  //Actual Output Voltage

int INDEX = 0;
uint32_t VALUE = 0;
uint32_t SUM = 0;
uint32_t READINGS[WINDOW_SIZE];
uint32_t AVERAGED = 0;



void setup(void) {
  lowVoltage = 5000;                              //Desired output voltage eventually find a way to get this value from the user
  //highVoltage = atverterE.getActualVH();          //Input voltage that is recovered from the
  //dutyCycle = (lowVoltage * 1024 / highVoltage);  // * 1024; //buck duty cycle equation

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
  //highVoltage = ((double)atverterE.getActualVH() * 1.02) - 92;
  //actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36; // Atverter1 
  actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104; // Atverter2

  if ((abs((int32_t)AVERAGED - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)) {
    // Serial.print("\n\n");
    // Serial.print("TRIGGERED");
    // Serial.print(", ");
    // Serial.print(actualLowVoltage);
    // Serial.print(", ");
    // Serial.print(AVERAGED);
    // Serial.print(", ");
    // Serial.print(abs((int32_t)AVERAGED - (int32_t)lowVoltage));
    // Serial.print(", ");
    // Serial.print(abs((int32_t)actualLowVoltage - (int32_t)lowVoltage));
    // Serial.print("\n\n");

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



  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(dutyCycle);
  //Serial.println(highVoltage);
  // //Serial.println(voltageRatio);
  //Serial.println(dutyCycle);
  // Serial.print("PWM Duty Cycle = ");
  // Serial.print(atverterE.getDutyCycle());
  // Serial.print("/1024, VH = ");
  //Serial.print(atverterE.getActualVH());
  // Serial.print("mV, IH = ");
  // Serial.print(atverterE.getIH());
  // Serial.print("mA, VL = ");
  // Serial.print(atverterE.getActualVL());
  // Serial.print("mV, IL = ");
  // Serial.print(atverterE.getIL());
  // Serial.println("mA");
  // atverterE.setLED(LED1G_PIN, ledState);
  // Serial.print("\n\n");
  ledState = !ledState;
}
*/