/* 
  Created: 1/25/2023
  By: Elijah Gordon and Joshua Hutchinson
  Main code runner
  
*/

#include <AtverterE.h>

#define INTERRUPT_TIME 1

#define INPUT_VOLTAGE_JUMP 999
#define OUTPUT_BOOST_VOLTAGE_STEADY_STATE 499
#define OUTPUT_BUCK_VOLTAGE_STEADY_STATE 499
#define WINDOW_SIZE 50


AtverterE atverterE;

int ledState = HIGH;

double dutyCycle = 512;
double lowVoltage;
double highVoltage;
double actualLowVoltage;
double actualHighVoltage;


int INDEX = 0;
uint32_t VALUE = 0;
uint32_t SUM = 0;
uint32_t READINGS[WINDOW_SIZE];
uint32_t AVERAGED = 0;


//double integralControl = 0.0;
int32_t prevVoltageError = 0;


char message[20];
int messagePosition = 0;
String state;
double setPoint = 5000;


void setup(void) {

  //lowVoltage = 5000;  //Desired output voltage eventually find a way to get this value from the user
  //highVoltage = atverterE.getActualVH();          //Input voltage that is recovered from the
  //dutyCycle = (lowVoltage * 1024 / highVoltage);  // * 1024; //buck duty cycle equation

  atverterE.setupPinMode();        //Get pins setup
  atverterE.initializePWMTimer();  //Setup Timers

  atverterE.initializeInterruptTimer(1, &controlUpdate);  //Get interrupts enabled
  Serial.begin(9600);

  //atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();
}

void loop(void) {
  serialControl();
}



void controlUpdate(void) {
  if (state == "boost") {
    boostControl(setPoint);
  }

  if (state == "buck") {
    buckControl(setPoint);
  }
  if (state == "current") {
    currentControl(setPoint);
  }
}


void buckControl(double lowVoltage) {

  if (lowVoltage < 1000) {
    lowVoltage = 1000;
  }

  // Control gain variables
  //Atverter 1
  //const double kp = 0.2;   // Proportional Control: kp * error
  //const double ki = 0.01;  // Integral Control: summation of (ki * error * sample_time)
  //const double kd = 0.0;   // Derivative Control:

  //Atverter 2
  const double kp = 0.2;   // Proportional Control: kp * error
  const double ki = 0.01;  // Integral Control: summation of (ki * error * sample_time)
  const double kd = 0.0;   // Derivative Control:


  //double actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36;  // Atverter1
  double actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104;  // Atverter2




  // Static variables used in the
  static double integralControl = 0.0;
  //static double dutyCycle = (lowVoltage * 1024 / atverterE.getActualVL());

  double voltageError = actualLowVoltage - lowVoltage;  // Instantaneous error of the desired output versus actual output voltage

  if (abs(voltageError) > OUTPUT_BUCK_VOLTAGE_STEADY_STATE) {
    // Allows for us to convert from voltage error to dutycycle error
    double proportionalControl = -(kp * (voltageError / lowVoltage));  // Proportional control: -kp * percent error

    integralControl += -(ki * (voltageError / lowVoltage));  // Integral control: -ki * (dutycycle) * percent error * sample_time

    dutyCycle *= 1 + (proportionalControl + integralControl /* + derivativeControl*/);
  }
  dutyCycle = constrain(dutyCycle, 10, 1014);
  atverterE.setDutyCycle((int)dutyCycle);


  /*
  //actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104;  // Atverter2
  actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36;  // Atverter1

  if ((abs((int32_t)AVERAGED - (int32_t)lowVoltage) > OUTPUT_BOOST_VOLTAGE_STEADY_STATE)) {
    if ((actualLowVoltage < lowVoltage)) {

      if (dutyCycle == 1024) {
        dutyCycle -= 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      } else {
        dutyCycle += 1;
      }
    }

    else if ((actualLowVoltage > lowVoltage)) {
      if (dutyCycle == 0) {
        dutyCycle += 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      } else {
        dutyCycle -= 1;
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

  atverterE.setDutyCycle(dutyCycle);
  ledState = !ledState;
  */
}

void boostControl(double highVoltage) {
  // Depending on which Atverter you are using
  actualHighVoltage = ((double)atverterE.getActualVH() * 1.02) - 92;  // Atverter1
  //actualLowVoltage = ((double)atverterE.getActualVL() * 1.03) + 36; // Atverter1
  //actualLowVoltage = ((double)atverterE.getActualVL() * 0.92) + 104; // Atverter2
  //actualHighVoltage = ((double)atverterE.getActualVH() * 0.92) + 20;  // Atverter2

  if (highVoltage < 1000) {
    highVoltage = 1000;
  }


  // Control gain variables
  //Atverter 1
  const double kp = 0.1;  // Proportional Control: kp * error
  const double ki = 0.0;  // Integral Control: summation of (ki * error * sample_time)
  const double kd = 0.0;  // Derivative Control:

  //Atverter 2
  // const double kp = 0.3;  // Proportional Control: kp * error
  // const double ki = 0.0;  // Integral Control: summation of (ki * error * sample_time)
  // const double kd = 0.0;  // Derivative Control:

  // Static variables used in the
  static double integralControl = 0.0;
  //static uint16_t dutyCycle = (highVoltage - atverterE.getActualVL()) * 1024 / highVoltage;

  int32_t voltageError = actualHighVoltage - highVoltage;  // Instantaneous error of the desired output versus actual output voltage

  if (abs(voltageError) > OUTPUT_BOOST_VOLTAGE_STEADY_STATE) {
    // Allows for us to convert from voltage error to dutycycle error
    // Negative sign used since boost converter is inversely proportional to dutycycle
    double proportionalControl = (kp * ((double)voltageError / (double)highVoltage));  // Proportional control: -kp * percent error

    integralControl += (ki * ((double)voltageError / (double)highVoltage));  // Integral control: -ki * (dutycycle) * percent error * sample_time

    //double derivativeControl = -(kd * ((double)(voltageError - prevVoltageError) / (double)INTERRUPT_TIME));  // Derivative control: -kd * (error - prev_error) / sample_time
    //prevVoltageError = voltageError;
    dutyCycle *= 1 + (proportionalControl + integralControl);
  }
  //dutyCycle = constrain(dutyCycle, 10, 1014);
  atverterE.setDutyCycle(constrain(dutyCycle, 10, 1014));


  /*
  actualHighVoltage = ((double)atverterE.getActualVH() * 1.02) - 92; // Atverter1
  //actualHighVoltage = ((double)atverterE.getActualVH() * 0.92) + 20;  // Atverter2
  //Serial.println("running boost");
  if ((abs(AVERAGED - highVoltage) > OUTPUT_VOLTAGE_STEADY_STATE)) {

    if ((AVERAGED <= highVoltage) && (dutyCycle > 10)) {
      dutyCycle -= 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
                       // Serial.println("-");
    }

    else if ((AVERAGED > highVoltage) && (dutyCycle < 1014)) {
      dutyCycle += 1;  // If the output voltage is close to desired output then slowly move towards the more desired value
      //Serial.println("+");
    }
  }

  if ((AVERAGED > 1000000)) {
    AVERAGED = 0;
  }

  SUM = SUM - READINGS[INDEX];        // Remove the oldest entry from the sum
  VALUE = actualHighVoltage;          // Collect the actual low voltage value
  READINGS[INDEX] = VALUE;            // Add the newest reading to the window
  SUM = SUM + VALUE;                  // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE;  // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;       // Divide the sum of the window by the window size for the result

  atverterE.setDutyCycle(dutyCycle);
  ledState = !ledState;
  */
}

void currentControl(double lowCurrent) {
  //highVoltage = atverterE.getActualVH();
  //actualLowVoltage = atverterE.getActualVL();
  //double actualLowCurrent = ((double)(-atverterE.getIL()) * 1.05) + 29;  //Atverter1 // Negative since hall effect sensor put in backwards
  //actualLowCurrent = ((double)(-atverterE.getIL()) * 0.93) + 10;  //Atverter2
  double actualLowCurrent = ((double)(-atverterE.getIL()) * 0.95) + 30; // Atverter3


  // Static variables used in the
  const double kp = 0.1;  // Proportional Control: kp * error
  const double ki = 0.001;  // Integral Control: summation of (ki * error * sample_time)
  const double kd = 0.0;  // Derivative Control:


  // Static variables used in the
  static double integralControl = 0.0;

  int32_t currentError = actualLowCurrent - lowCurrent;  // Instantaneous error of the desired output versus actual output voltage

  // Allows for us to convert from voltage error to dutycycle error
  // Negative sign used since boost converter is inversely proportional to dutycycle
  double proportionalControl = -(kp * ((double)currentError / (double)lowCurrent));  // Proportional control: -kp * percent error

  integralControl += -(ki * ((double)currentError / (double)lowCurrent));  // Integral control: -ki * (dutycycle) * percent error * sample_time


  //double derivativeControl = (kd * ((double)(voltageError - prevVoltageError) / (double)INTERRUPT_TIME));  // Derivative control: -kd * (error - prev_error) / sample_time
  //derivativeControl = constrain(derivativeControl, -0.5, 0.5);

  dutyCycle += (double)dutyCycle * (proportionalControl + integralControl /* + derivativeControl*/);


  dutyCycle = constrain(dutyCycle, 10, 1014);

  atverterE.setDutyCycle(dutyCycle);
}


void serialControl(void) {


  String messageSTR;


  while (Serial.available() > 0) {
    // read the incoming byte:
    char serialIn = Serial.read();
    if ((serialIn != '\n') && (messagePosition < 7)) {
      message[messagePosition] = serialIn;
      messagePosition++;
    } else {
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




  if ((messageSTR == "Request")) {
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

    Serial.print("lvCurrent ");
    Serial.println(atverterE.getIL());

    Serial.print("hvCurrent ");
    Serial.println(atverterE.getIH());

    //Serial.println(AVERAGED);

    messageSTR = "done";
  }

  else if (messageSTR.substring(0, 7) == "toBoost") {
    state = "boost";
    Serial.println(messageSTR);
    setPoint = 10000;
  } else if (messageSTR.substring(0, 7) == "tooBuck") {
    state = "buck";
    Serial.println(messageSTR);
    setPoint = 5000;  //Default value

  } else if (isAllDigits(messageSTR)) {
    setPoint = messageSTR.toDouble();
    Serial.print(messageSTR);
    Serial.println("mV");
  }

  else if (messageSTR.substring(0, 7) == "current") {
    state = "current";
    Serial.println(messageSTR);
    setPoint = 500;
  } else {
    Serial.flush();
  }
}


boolean isAllDigits(String str) {
  boolean allDigits = true;

  if (str.length() == 0) {
    allDigits = false;
  }

  for (int i = 0; i < str.length(); i++) {
    if (!isDigit(str.charAt(i))) {
      allDigits = false;
    }
  }
  return allDigits;
}
