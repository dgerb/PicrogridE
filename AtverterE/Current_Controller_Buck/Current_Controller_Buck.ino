#include <AtverterE.h>

AtverterE atverterE;
int ledState = HIGH;

int dutyCycle;
double lowVoltage;   //Output Voltage
double highVoltage;  //Input Voltage
double lowCurrentSet;
double lowCurrentActual;
double averagingFilter;
int counter = 0;
double filterOutput;


void setup(void) {
  atverterE.setupPinMode();
  atverterE.initializePWMTimer();

  lowVoltage = 1000;
  lowCurrentSet = 400;
  highVoltage = atverterE.getActualVH();
  //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  dutyCycle = (lowVoltage / highVoltage) * 1024;

  atverterE.initializeInterruptTimer(50, &controlUpdate);
  Serial.begin(9600);
  atverterE.setDutyCycle(dutyCycle);
  atverterE.startPWM();


}

void loop(void) {
}

void controlUpdate(void) {
  lowCurrentActual = abs(atverterE.getIL());

  if (counter < 50) {
    averagingFilter += lowCurrentActual;
  } else {
    averagingFilter = lowCurrentActual;
    counter = 0;
  }
  counter++;
  filterOutput = averagingFilter / counter;


  if (filterOutput > lowCurrentSet) {
    //lowVoltage -= 10;
    dutyCycle -= 1;

  }
  if (filterOutput < lowCurrentSet) {
    lowVoltage += 10;
    dutyCycle += 1;
  }

  highVoltage = atverterE.getActualVH();
  //dutyCycle = (lowVoltage / highVoltage) * 1024;


  atverterE.setDutyCycle(dutyCycle);
  Serial.println(highVoltage);
  Serial.println(lowVoltage);
  Serial.println(filterOutput);
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

/*
#include <AtverterE.h>

AtverterE atverterE;
int ledState = HIGH;





  int dutyCycle;
  double lowVoltage; //Output Voltage
  double highVoltage; //Input Voltage
  double voltageRatio;
  double lowCurrentSet;
  double lowCurrentActual;
  double averagingFilter;
  int counter = 0;
  double filterOutput;


void setup(void)
{
  atverterE.setupPinMode();
  atverterE.initializePWMTimer();


  atverterE.initializeInterruptTimer(50, &controlUpdate);
  Serial.begin(9600);
  atverterE.setDutyCycle(256);
  atverterE.startPWM();

  lowVoltage = 1000;
  lowCurrentSet = 400;
  highVoltage = atverterE.getActualVH();
  //dutyCycle = (lowVoltage / highVoltage) * 1024; //buck duty cycle equation
  dutyCycle = (lowVoltage / highVoltage) * 1024;
}

void loop(void)
{
}

void controlUpdate(void)
{


  lowCurrentActual = -atverterE.getIL();


  if(counter < 10)
  {
    averagingFilter += lowCurrentActual;
  }
  else
  {
    averagingFilter = lowCurrentActual;
    counter = 0;
  }
  counter++;
  filterOutput = averagingFilter / counter;


  if(filterOutput > lowCurrentSet)
  {
    lowVoltage -= 10;
  }
  if(filterOutput < lowCurrentSet)
  {
    lowVoltage += 10;
  }

  highVoltage = atverterE.getActualVH();
  dutyCycle = (lowVoltage / highVoltage) * 1024;


  atverterE.setDutyCycle(dutyCycle);
  Serial.println(highVoltage);
  Serial.println(lowVoltage);
  Serial.println(filterOutput);
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
*/