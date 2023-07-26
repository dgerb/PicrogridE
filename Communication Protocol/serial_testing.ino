//FOR TESTING ONLY
//use to confirm http and serial communications are working

int state = 40;
int rate = -2;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    Serial.println(String(state));
    Serial.println(String(rate));
  }
}
