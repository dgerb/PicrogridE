/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Output Voltage Controller for Buck Converter
  
*/

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
  highVoltage = atverterE.getActualVH();          //Input voltage that is recovered from the
  dutyCycle = (lowVoltage * 1024 / highVoltage);  // * 1024; //buck duty cycle equation

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(1, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();

  // lowVoltage = 12000; //Desired output voltage eventually find a way to get this value from the user
  // highVoltage = atverterE.getActualVH(); //Input voltage that is recovered from the
  // dutyCycle = (lowVoltage * 1024 / highVoltage);// * 1024; //buck duty cycle equation
  //voltageRatio = (lowVoltage / highVoltage) * 100;
  //dutyCycle = ((voltageRatio - 100) / (voltageRatio)) * 1024;
}

void loop(void) {
}

void controlUpdate(void) {
  highVoltage = (double)atverterE.getActualVH() * 0.9681 +  ;
  actualLowVoltage = atverterE.getActualVL();


  if (abs((int32_t)highVoltage - (int32_t)prevHighVoltage) > INPUT_VOLTAGE_JUMP) {
    dutyCycle = (lowVoltage * 1024 / highVoltage);  // * 1024;
    // Serial.println("change detected");
    // Serial.println(highVoltage - prevHighVoltage);
    //SUM = READINGS[INDEX];
    prevHighVoltage = highVoltage;
  } else if ((abs((int32_t)AVERAGED - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE) && (abs((int32_t)actualLowVoltage - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)) {
    Serial.print("\n\n");
    Serial.print("TRIGGERED");
    Serial.print(", ");
    Serial.print(actualLowVoltage);
    Serial.print(", ");
    Serial.print(AVERAGED);
    Serial.print(", ");
    Serial.print(abs((int32_t)AVERAGED - (int32_t)lowVoltage));
    Serial.print(", ");
    Serial.print(abs((int32_t)actualLowVoltage - (int32_t)lowVoltage));
    Serial.print("\n\n");


    if ((actualLowVoltage < lowVoltage)) {
      if ((lowVoltage - actualLowVoltage) > OUTPUT_VOLTAGE_JUMP)  // If voltage is way off then jump to correct value
      {
        //dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1); //Calculates duty cycle given the error found by differing output voltages
        // Serial.println("Jumped DutyCycle: ");
        // Serial.print(dutyCycle * ((((double)lowVoltage - (double)actualLowVoltage) / (double)actualLowVoltage) + 1));
        // Serial.print("\n\n");
        dutyCycle = dutyCycle * ((((double)lowVoltage - (double)actualLowVoltage) / (double)actualLowVoltage) + 1);
        //SUM = READINGS[INDEX];  //Reset Moving average filter
      } else {
        dutyCycle += 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      }
    }

    else if ((actualLowVoltage > lowVoltage)) {
      if ((actualLowVoltage - lowVoltage) > OUTPUT_VOLTAGE_JUMP)  // If voltage is way off then jump to correct value
      {
        // dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1); //Calculates duty cycle given the error found by differing output voltages
        // Serial.println("Jumped DutyCycle: ");
        // Serial.print(dutyCycle * ((((double)lowVoltage - (double)actualLowVoltage) / (double)actualLowVoltage) + 1));
        // Serial.print("\n\n");

        dutyCycle = dutyCycle * ((((double)lowVoltage - (double)actualLowVoltage) / (double)actualLowVoltage) + 1);
        //SUM = READINGS[INDEX];  //Reset Moving average filter
      } else {
        dutyCycle -= 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      }
    }
  }

  // Use the moving average filter
    SUM = SUM - READINGS[INDEX];        // Remove the oldest entry from the sum
    VALUE = actualLowVoltage;           // Collect the actual low voltage value
    READINGS[INDEX] = VALUE;            // Add the newest reading to the window
    SUM = SUM + VALUE;                  // Add the newest reading to the sum
    INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
    AVERAGED = SUM / WINDOW_SIZE;       // Divide the sum of the window by the window size for the result

  Serial.print("\n\n");
  Serial.print(VALUE);
  Serial.print(",");
  Serial.print(SUM);
  Serial.print(",");
  Serial.print(AVERAGED);
  Serial.print("\n\n");

  /*
  actualLowVoltage = atverterE.getActualVL();

  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = actualLowVoltage;          // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result


  Serial.print(VALUE);
  Serial.print(",");
  Serial.print(AVERAGED);
  Serial.print("\n");



  //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  //Implement a moving average filter

  if(abs((int)AVERAGED - (int)lowVoltage) > 100) { //Smooths out the output by keeping same dutycycle unless difference between
    
    Serial.print(AVERAGED);
    Serial.print(", ");
    Serial.print(lowVoltage);
    Serial.print("\n");
    Serial.print("Average - lowVoltage = ");
    Serial.print(abs((int)AVERAGED - (int)lowVoltage));
    
    if (abs(highVoltage - prevHighVoltage) > 999)
    {
      dutyCycle = (lowVoltage * 1024 / highVoltage);// * 1024;
      // Serial.println("change detected");
      // Serial.println(highVoltage - prevHighVoltage);
      //SUM = 0;
      prevHighVoltage = highVoltage;
    }
    else if((actualLowVoltage < lowVoltage))
    {
      //double percentDiff1 = (lowVoltage - actualLowVoltage) / actualLowVoltage;
      //double newDutyCycle1 = dutyCycle * (percentDiff1 + 1);
      //dutyCycle = (int) newDutyCycle1; // dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);
      //dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);

      dutyCycle += 1;
    }
    else if((actualLowVoltage > lowVoltage))
    {
      //double percentDiff2 = (lowVoltage - actualLowVoltage) / actualLowVoltage;
      //double newDutyCycle2 = dutyCycle * (percentDiff2 + 1);
      //dutyCycle = (int) newDutyCycle2; //dutyCycle * ((actualLowVoltage - lowVoltage) / actualLowVoltage);

      //dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);
      
      
      dutyCycle -= 1;
    }

    atverterE.setDutyCycle(dutyCycle);
    //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  }
*/
  //dutyCycle = (lowVoltage * 1024 / highVoltage);
  atverterE.setDutyCycle(dutyCycle);
  //Serial.println(highVoltage);
  // //Serial.println(voltageRatio);
  //Serial.println(dutyCycle);
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

/*
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
  Serial.print("\n");



  //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  //Implement a moving average filter

  if(abs((int)AVERAGED - (int)lowVoltage) > 100) { //Smooths out the output by keeping same dutycycle unless difference between
    Serial.print(AVERAGED);
    Serial.print(", ");
    Serial.print(lowVoltage);
    Serial.print("\n");
    Serial.print("Average - lowVoltage = ");
    Serial.print(abs(AVERAGED - lowVoltage));
    if (abs(highVoltage - prevHighVoltage) > 999)
    {
      dutyCycle = (lowVoltage * 1024 / highVoltage);// * 1024;
      // Serial.println("change detected");
      // Serial.println(highVoltage - prevHighVoltage);
      //SUM = 0;
      prevHighVoltage = highVoltage;
    }
    else if((actualLowVoltage < lowVoltage))
    {
      //double percentDiff1 = (lowVoltage - actualLowVoltage) / actualLowVoltage;
      //double newDutyCycle1 = dutyCycle * (percentDiff1 + 1);
      //dutyCycle = (int) newDutyCycle1; // dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);
      //dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);

      dutyCycle += 1;
    }
    else if((actualLowVoltage > lowVoltage))
    {
      //double percentDiff2 = (lowVoltage - actualLowVoltage) / actualLowVoltage;
      //double newDutyCycle2 = dutyCycle * (percentDiff2 + 1);
      //dutyCycle = (int) newDutyCycle2; //dutyCycle * ((actualLowVoltage - lowVoltage) / actualLowVoltage);

      //dutyCycle = dutyCycle * (((lowVoltage - actualLowVoltage) / actualLowVoltage) + 1);
      
      
      dutyCycle -= 1;
    }

    atverterE.setDutyCycle(dutyCycle);
    //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  }

  //atverterE.setDutyCycle(dutyCycle);
  Serial.println(highVoltage);
  //Serial.println(voltageRatio);
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
*/