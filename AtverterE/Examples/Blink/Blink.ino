/*
  Blink

  Blinks each AtverterE LED through each color (R, G, Y).

  modified 19 Sep 2022
  by Daniel Gerber
*/

#include <AtverterE.h>

AtverterE atverterE;

int PERIOD = 200; // duration (ms) of half period

// the setup function runs once when you press reset or power the board
void setup() {
  atverterE.setupPinMode();
}

// the loop function runs over and over again forever
void loop() {
  ledTest(LED1R);
  ledTest(LED1G);
  ledTest(LED2R);
  ledTest(LED2G);
  ledTest2(LED1R, LED1G);
  ledTest2(LED2R, LED2G);
}

void ledTest(int led) {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(PERIOD);                       // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(PERIOD);                       // wait for a second
}

void ledTest2(int ledr, int ledg) {
  digitalWrite(ledr, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledg, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(PERIOD);                       // wait for a second
  digitalWrite(ledr, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledg, LOW);    // turn the LED off by making the voltage LOW
  delay(PERIOD);                       // wait for a second
}
