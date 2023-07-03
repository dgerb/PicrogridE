

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
//Serial.println("Hello from Arduino");
//delay(1000)
if (Serial.available() > 0)
  {
    String message = Serial.readStringUntil('\n');
    Serial.println(message);
  }
}
