//Created by Brandon Ng
//8/2/2023

#include <AtverterE.h>

AtverterE atverter;

int dutyCycle;
uint32_t lowVoltage;        //Battery Voltage
uint32_t actualLowVoltage;  //Actual Output Voltage
int32_t lowCurrent;         //Output Current
int32_t actualLowCurrent;   //Actual Output Current

void setup() {
  // put your setup code here, to run once:
lowCurrent = 500; //positive is into battery, negative is out

atverter.setupPinMode();
atverter.initializePWMTimer();
atverter.initializeInterruptTimer(1, &controlUpdate);

Serial.begin(9600);
dutyCycle = 768; //chosen because in most cases, the resultant current is low, prevents instant frying
                 // 75% duty cycle matches 12V battery to 16V bus
atverter.setDutyCycle(dutyCycle);
atverter.startPWM();
//AFTER UPLOAD
//OPEN SERIAL MONITOR
//TURN ON LOAD
//TURN ON POWER SUPPLY
//CHECK BATTERY VOLTAGE
//THEN PLUG THE BATTERY IN
}

void loop() {
  // put your main code here, to run repeatedly:
}

void immediateCharge(){
  while (lowVoltage <= 12000){
    dutyCycle = 818;
    atverter.setDutyCycle(dutyCycle);
    lowVoltage = atverter.getActualVL(); 
  }  
}

void immediateDischarge(){
  while (lowVoltage >= 12200){
    dutyCycle = 614;
    atverter.setDutyCycle(dutyCycle);
    lowVoltage = atverter.getActualVL(); 
  }  
}
void controlUpdate(void) {
  //check if the battery is reaching critical levels and run alternate functions to fix this
  /*lowVoltage = atverter.getActualVL();
  if (lowVoltage <= 11500){
    immediateCharge();
  }
  else if (lowVoltage >= 12700){
    immediateDischarge();
  } */

  
  actualLowCurrent = ((double)(-atverter.getIL()) * 0.95) + 30;
  int32_t currentError = lowCurrent - actualLowCurrent;
  
     
  if (currentError > 0){
    dutyCycle += 1;
  }
  else if (currentError < 0){
    dutyCycle -= 1;
  }
  else{
    dutyCycle = dutyCycle;
  }
  dutyCycle = constrain(dutyCycle, 630, 900); //general limitation to prevent 5A maximum
  //630 yielded 2.5 from the jump, 900 about -1.2
  //all for testing, feel free to comment out
  int vh = atverter.getActualVH();
  int vl = atverter.getActualVL();
  int ih = atverter.getIH();
  int il = atverter.getIL();
  Serial.println("High Voltage: " + String(vh));
  Serial.println("Low Voltage: " + String(vl));
  Serial.println("High Current: " + String(ih));
  Serial.println("Low Current: " + String(il));
  Serial.println(dutyCycle); //for testing
  //end of code used for testing
  atverter.setDutyCycle(dutyCycle);  
}
