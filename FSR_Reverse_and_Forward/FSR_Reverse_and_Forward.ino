#include <Stepper.h>
const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 10,9);
Stepper myStepperN(stepsPerRevolution, 9,10);

int fsrAnalogPin = 0; // FSR is connected to analog 0
int Motorpin1 = 10;  // connect H bridge to pins 9 and 10
int Motorpin2 = 9;
int Ledpin = 11;     // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int fsrReading2; 
int Motorspeed;
int PrevValue;
int Derivative;
int i = 0;


 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(Motorpin1, OUTPUT);
  pinMode(Motorpin2, OUTPUT);
  myStepper.setSpeed(60);
}
 
void loop(void) {
  
  fsrReading = analogRead(fsrAnalogPin);
  delay(10);
  fsrReading2 = analogRead(fsrAnalogPin);
  Derivative = (fsrReading2-fsrReading)/.01;

  if(fsrReading>800){
    Derivative = 0;
  }

  if(Derivative > 0){
    if(i < 25){
      Serial.println("Grip");
      i = i + 1;
      delay(1);
    }
    Serial.println(i);
  } else if(Derivative < 0){
    if(i > 0){
      Serial.println("Release");
      i = i - 1;
    }
    Serial.println(i);
  } else {
    Serial.println("Stay");
  }
  if(i > 25){
    i = 25; 
  } else if (i < 0){
    i = 0;
  } 
}

//Possibly set speed to derivative and run motor until a certain amount of steps is reached
//Can move a stepper by 1/20 of a rotation and stop it once it reaches a maximum
//Will need to add some zero switches   
