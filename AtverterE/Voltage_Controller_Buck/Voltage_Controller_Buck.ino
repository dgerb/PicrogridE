/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson

  Output Voltage Controller for Buck Converter
  

*/

#include <AtverterE.h>

#define WINDOW_SIZE 50

AtverterE atverterE;
int ledState = HIGH;

int dutyCycle;
double lowVoltage; //Output Voltage
double highVoltage; //Input Voltage
double prevHighVoltage = 0;
double voltageRatio; // lowVoltage / highVoltage
double actualLowVoltage; //Actual Output Voltage

int INDEX = 0;
double VALUE = 0;
double SUM = 0;
double READINGS[WINDOW_SIZE];
double AVERAGED = 0;



void setup(void)
{
  atverterE.setupPinMode(); //Get pins setup
  atverterE.initializePWMTimer(); //Setup Timers

  atverterE.initializeInterruptTimer(2, &controlUpdate); //Get interrupts enabled
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
  highVoltage = atverterE.getActualVH();
  actualLowVoltage = atverterE.getActualVL();

  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = actualLowVoltage;
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result


  Serial.print(VALUE);
  Serial.print(",");
  Serial.print(AVERAGED);



  //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  //Implement a moving average filter

  if(abs((int)AVERAGED - (int)lowVoltage) > 100) { //Smooths out the output by keeping same dutycycle unless difference between
    if (abs(highVoltage - prevHighVoltage) > 999)
    {
      dutyCycle = (lowVoltage / highVoltage) * 1024;
      // Serial.println("change detected");
      // Serial.println(highVoltage - prevHighVoltage);
      prevHighVoltage = highVoltage;
    }
    else if((actualLowVoltage < lowVoltage))
    {
      //double percentDiff1 = (lowVoltage - actualLowVoltage) / actualLowVoltage;
      //double newDutyCycle1 = dutyCycle * (percentDiff1 + 1);
      //dutyCycle = (int) newDutyCycle1; // dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);
      //dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);

      dutyCycle += 2;
    }
    else if((actualLowVoltage > lowVoltage))
    {
      //double percentDiff2 = (lowVoltage - actualLowVoltage) / actualLowVoltage;
      //double newDutyCycle2 = dutyCycle * (percentDiff2 + 1);
      //dutyCycle = (int) newDutyCycle2; //dutyCycle * ((actualLowVoltage - lowVoltage) / actualLowVoltage);

      //dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);
      
      
      dutyCycle -= 2;
    }

    atverterE.setDutyCycle(dutyCycle);
    //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  }

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

// int calculateDutyCycle(double lowVolt, double actualLowVolt, double highVolt, double actualHighVolt) {
//   int dutycycle;

  

//   if () {
//   dutycycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);
//   }
//   else {
//     dutycyle = dutyCycle;
//   }

//   return dutycycle;

// }