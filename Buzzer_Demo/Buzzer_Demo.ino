void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);

}

void loop() {
    if(digitalRead(4) == HIGH){
      Serial.println(digitalRead(4));
      tone(5, 800);
    } else {
      Serial.println(digitalRead(4));
      noTone(5);
    }
}
