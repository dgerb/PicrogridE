/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson

  Output Current Controller for Buck Converter
  

*/

#include <AtverterE.h>

AtverterE atverterE;
int ledState = HIGH;

int dutyCycle;
double lowCurrent; //Output Current
double highCurrent; //Input Current
double currentRatio; // lowCurrent / highCurrent


void setup(void)
{
  atverterE.setupPinMode(); //Get pins setup
  atverterE.initializePWMTimer(); //Setup Timers

  atverterE.initializeInterruptTimer(50, &controlUpdate); //Get interrupts enabled
  Serial.begin(9600);
  atverterE.setDutyCycle(256);
  atverterE.startPWM();

  lowCurrent = 50; //Desired output current eventually find a way to get this value from the user
  highCurrent = atverterE.getIH(); //Input current
  dutyCycle = (lowCurrent / highCurrent) * 1024; //buck duty cycle equation
  //currentRatio = (lowCurrent / highCurrent) * 100;
  //dutyCycle = ((currentRatio - 100) / (currentRatio)) * 1024;
}

void loop(void)
{
}

void controlUpdate(void)
{
  atverterE.setDutyCycle(dutyCycle);
//
//  int actualVL = atverterE.getActualVL();
//
//  if(actualVL < lowVoltage)
//  {
//    dutyCycle += ( ((actualVL - lowVoltage) / actual) * 100);
//  }
//  if(actualVL > lowVoltage)
//  {
//    dutyCycle -= 2;
//  }

  atverterE.setDutyCycle(dutyCycle);
  Serial.println(highCurrent);
  Serial.println(currentRatio);
  Serial.println(dutyCycle);
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
  ledState = !ledState;
}