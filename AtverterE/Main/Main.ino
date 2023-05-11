/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Main code runner
  
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
uint32_t actualHighVoltage;  //Actual Output Voltage

int INDEX = 0;
uint32_t VALUE = 0;
uint32_t SUM = 0;
uint32_t READINGS[WINDOW_SIZE];
uint32_t AVERAGED = 0;


char message[20];
int messagePosition = 0;
String state = "buck";
double setPoint;


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
  serialControl();
}



void controlUpdate(void) {
  if(state == "boost")
  {
    boostControl(setPoint);
  }

  if(state == "buck")
  {
    buckControl(setPoint);
  }
  
}






void buckControl(double lowVoltage)
{
   actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104; // Atverter2

  if ((abs((int32_t)AVERAGED - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)/* && (abs((int32_t)actualLowVoltage - (int32_t)lowVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)*/) {
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

  atverterE.setDutyCycle(dutyCycle);
  ledState = !ledState;
}

void boostControl(double highVoltage)
{
  actualHighVoltage = ((double)atverterE.getActualVH() * 0.92) + 20; // Atverter2

  if ((abs((int32_t)AVERAGED - (int32_t)highVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)) {
    if ((actualHighVoltage < highVoltage)) {
      dutyCycle += 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
    }

    else if ((actualHighVoltage > highVoltage)) {
      dutyCycle -= 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
    }
  }

  
  SUM = SUM - READINGS[INDEX];        // Remove the oldest entry from the sum
  VALUE = actualHighVoltage;           // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;            // Add the newest reading to the window
  SUM = SUM + VALUE;                  // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;       // Divide the sum of the window by the window size for the result
  
  atverterE.setDutyCycle(250);
  ledState = !ledState;

  
}











void serialControl(void)
{


  String messageSTR;


   while(Serial.available() > 0) {
      // read the incoming byte:
      char serialIn = Serial.read();
      if((serialIn != '\n') && (messagePosition < 7))
      {
        message[messagePosition] = serialIn;
        messagePosition++;
      }
      else
      {
        message[messagePosition] = '\0';
        messagePosition = 0;
        messageSTR = String(message);
      }
     }

   //  if(messageSTR != "")
    // {
    //  Serial.println(messageSTR);
      //Serial.println(messageSTR.substring(0, 6));
   //   }



    
    if((messageSTR == "Request"))
    {
        Serial.print("VL ");
        Serial.println(atverterE.getActualVL());

        Serial.print("VH ");
        Serial.println(atverterE.getActualVH());
        
        Serial.print("PWM ");
        Serial.println(atverterE.getDutyCycle());

        Serial.print("STATE ");
        Serial.println(state);
        

        Serial.print("SETPOINT ");
        Serial.println(setPoint);

//        Serial.println("ACK acknowledged");
        messageSTR = "done";
    }

    else if(messageSTR.substring(0, 7) == "toBoost")
    {
        state = "boost";
        Serial.println(messageSTR);

    }
    else if(messageSTR.substring(0, 7) == "tooBuck")
    {
      state = "buck";
      Serial.println(messageSTR);
    }
    else if(isAllDigits(messageSTR))
    {
      setPoint = messageSTR.toDouble();
      //Serial.println("ACK acknowledged");
      Serial.print(messageSTR);
      Serial.println("mV");
    }
    else{
      Serial.flush();
      
      }
    

}


boolean isAllDigits(String str)
{
  boolean allDigits = true;

  if(str.length() == 0)
  {
    allDigits = false;
  }
  
  for(int i = 0; i < str.length(); i++)
  {
    if(!isDigit(str.charAt(i)))
    {
      allDigits = false;
    }
  }
  return allDigits;
}
