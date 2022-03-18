void setup() {
  for (int i=0;i<17;i++) {
    pinMode(i,INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i=0;i<17;i++) {
    Serial.print(digitalRead(i));
  }
  Serial.println();
}
