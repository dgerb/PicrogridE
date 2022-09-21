/*
  PWMTest

  Turns on PWM and sweeps duty cycle between 33% and 66%.
  Reports voltages and currents to serial terminal (baud rate 9600).

  created September 20 2022 by Daniel Gerber
  modified September 21 2022 by Daniel Gerber
*/

#include <AtverterE.h>

AtverterE atverterE;
int ledState = HIGH;

void setup(void)
{
  atverterE.setupPinMode();
  atverterE.initializePWMTimer();
  atverterE.initializeInterruptTimer(300, &controlUpdate);
  Serial.begin(9600);
  atverterE.setDutyCycle(256);
  atverterE.startPWM();
}

void loop(void)
{
}

void controlUpdate(void)
{
  int dutyCycle = atverterE.getDutyCycle();
  dutyCycle = dutyCycle + 8;
  if (dutyCycle > 674)
    dutyCycle = 350;
  atverterE.setDutyCycle(dutyCycle);
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
