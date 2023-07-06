const int pwmpin = 9;

void setup() {
  // put your setup code here, to run once:
pinMode(pwmpin, OUTPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0)
  {
    String message = Serial.readStringUntil('\n');
    int pushcode = map(message.toInt(), 0, 63, 0, 255); //create a duty cycle for analogWrite
    int dutyCycle = map(message.toInt(), 0, 63, 0, 100); //create a %duty cycle to send back to Pi
    analogWrite(pwmpin, pushcode);
    Serial.println(String(dutyCycle) + "% duty cycle");
  }
}
