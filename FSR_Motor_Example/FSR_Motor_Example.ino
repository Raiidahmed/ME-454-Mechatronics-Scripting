

int fsrAnalogPin = 0; // FSR is connected to analog 0
int Motorpin1 = 10;  // connect H bridge to pins 9 and 10
int Motorpin2 = 9;
int Ledpin = 11;     // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int Motorspeed;
int PrevValue;
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(Motorpin1, OUTPUT);
  pinMode(Motorpin2, OUTPUT);
}
 
void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
 
  // we'll need to change the range from the analog reading (0-1023) down to the range
  // used by analogWrite (0-255) with map
  
  Motorspeed = map(fsrReading, 0, 800, 0, 255);
  Serial.println(Motorspeed);
  
  digitalWrite(Motorpin2, Motorspeed);
  digitalWrite(Motorpin1, LOW);
  
  
  analogWrite(Ledpin, Motorspeed);
  
  PrevValue = Motorspeed;
 
  delay(100);
}



