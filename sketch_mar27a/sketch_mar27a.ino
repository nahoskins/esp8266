void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    pinMode(14, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(14, HIGH);
  Serial.println("Blink On");
  delay(2000);
  digitalWrite(14 , LOW);
  Serial.println("Blink Off");
  delay(2000);
}
