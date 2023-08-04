//Created by Brandon Ng
//Last Update 8/4/2023
//code to control charging current of a lithium ion battery

#include <AtverterE.h>

AtverterE atverter;

int dutyCycle;
uint32_t lowVoltage;        //Battery Voltage
uint32_t actualLowVoltage;  //Actual Output Voltage
int lowCurrent;         //Output Current
int32_t actualLowCurrent;   //Actual Output Current

void setup() {
  // put your setup code here, to run once:
//initialize battery to do nothing when code first booted up
lowCurrent = 0; //positive is into battery, negative is out
atverter.setupPinMode();
atverter.initializePWMTimer();

Serial.begin(9600);
dutyCycle = 768; //chosen because in most cases, the resultant current is low, prevents instant frying
                 // 75% duty cycle matches 12V battery to 16V bus
atverter.setDutyCycle(dutyCycle);
atverter.startPWM();
//AFTER UPLOAD
//OPEN SERIAL MONITOR
//TURN ON POWER SUPPLY
//TURN ON LOAD
//CHECK BATTERY VOLTAGE
//THEN PLUG THE BATTERY IN
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    //update control current if command given from Raspberry Pi
    String command = Serial.readStringUntil('\n');
    lowCurrent = command.toInt();
  }
  
  actualLowCurrent = ((double)(-atverter.getIL()) * 0.95) + 30;
  int32_t currentError = lowCurrent - actualLowCurrent;
  
  //adjust dutyCycle based on if current is too high or too low   
  if (currentError > 0){
    dutyCycle += 1;
  }
  else if (currentError < 0){
    dutyCycle -= 1;
  }
  else{
    dutyCycle = dutyCycle;
  }
  
  dutyCycle = constrain(dutyCycle, 605, 910); //limitation to prevent 5A maximum
  //615 yielded 3.5A discharge, 910 yielded 1.5A charge
  
  //all for testing, feel free to comment out
  //eventually, include proper serial write commands for the server in here
  /*int vh = atverter.getActualVH();
  int vl = atverter.getActualVL();
  int ih = atverter.getIH();
  int il = atverter.getIL();
  Serial.println("High Voltage: " + String(vh));
  Serial.println("Low Voltage: " + String(vl));
  Serial.println("High Current: " + String(ih));
  Serial.println("Low Current: " + String(il));
  Serial.println(dutyCycle); //for testing
  //end of code used for testing*/
  atverter.setDutyCycle(dutyCycle); 
   
}
