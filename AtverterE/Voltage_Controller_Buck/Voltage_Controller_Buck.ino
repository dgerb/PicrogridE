/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson

  Output Voltage Controller for Buck Converter
  

*/

#include <AtverterE.h>

AtverterE atverterE;
int ledState = HIGH;

  int dutyCycle;
  double lowVoltage; //Output Voltage
  double highVoltage; //Input Voltage
  double voltageRatio; // lowVoltage / highVoltage


void setup(void)
{
  atverterE.setupPinMode(); //Get pins setup
  atverterE.initializePWMTimer(); //Setup Timers

  atverterE.initializeInterruptTimer(50, &controlUpdate); //Get interrupts enabled
  Serial.begin(9600);
  atverterE.setDutyCycle(256);
  atverterE.startPWM();

  lowVoltage = 5000; //Desired output voltage eventually find a way to get this value from the user
  highVoltage = atverterE.getActualVH(); //Input voltage that is recovered from the 
  dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  //voltageRatio = (lowVoltage / highVoltage) * 100;
  //dutyCycle = ((voltageRatio - 100) / (voltageRatio)) * 1024;
  //does daniel have these equations built into his code already????
  //no
  //does the topology of this converter switch depending on function??
  //seems like no
  //how fast can the arduino run??
  //
  //
  //What is a better way to account for losses
  //
  //
  //Switching Frequency? HOw did I change/find the switching frequency
  //
  //
  //Does Daniel care about the device working in DCM mode or is just CCM ok?
  //
  //
  //What is the point of all of the different ways for calculating Voltage
  //
  //

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
  Serial.println(highVoltage);
  Serial.println(voltageRatio);
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