    /***********************************************************************
 * Exp7_2_DriveDistance -- RedBot Experiment 7.2
 * 
 * In an earlier experiment, we used a combination of speed and time to
 * drive a certain distance. Using the encoders, we can me much more accurate.
 * In this example, we will show you how to setup your robot to drive a certain
 * distance regardless of the motorPower.
 * 
 * This sketch was written by SparkFun Electronics, with lots of help from 
 * the Arduino community. This code is completely free for any use.
 * 
 * 8 Oct 2013 M. Hord
 * Revised, 31 Oct 2014 B. Huang 
 ***********************************************************************/
#include <RedBot.h>

RedBotMotors motors;

RedBotEncoder encoder = RedBotEncoder(A2, 10);

int buttonPin = 12;
int countsPerRev = 192;   // 4 pairs of N-S x 48:1 gearbox = 192 ticks per wheel rev

float wheelDiam = 2.56;  // diam = 65mm / 25.4 mm/in
float wheelCirc = PI*wheelDiam;  // Redbot wheel circumference = pi*D
int RPM; //allocate RPM of motor
int pos = 69; //choose 30 for this value to start with 25%
volatile long count; // count
volatile long count_last; // count

// ******** Variables for Timing *********************
unsigned long t1=0; //Hold initial loop time
unsigned long t0=0; //Hold end loop time
unsigned long t2=0; //hold end motor time
unsigned long st=250; //Hold sampling time


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  t1 = millis();
  if ((t1 - t0) >= st){
    count = encoder.getTicks(LEFT);
    RPM = (count - count_last)*(1000/st)*60/192; //Calculate RPM
    Serial.print(t1); //Print t1
    Serial.print(","); //comma for .csv
    Serial.println(RPM); //Print RPM 

    count_last = count;
    t0 = millis();
  }

  if (t1 - t2 >= 100 && RPM < 150){ //Change motor speed. Can limit at 140 RPM to keep to 25% or 433 for 75%
      pos += 1;
      motors.drive(pos); //Write Speed
      t2 = millis(); //Take second time
    } //end if
}

  /*if (t1 - t2 >= 100 && RPM < 433){ //Change motor speed. Can limit at 140 RPM to keep to 25% or 433 for 75%
   pos += 1;
   analogWrite(motorPin, pos); //Write Speed
    t2 = millis(); //Take second time
  } //end if
}

void driveDistance(float distance, int motorPower)
{
  long lCount = 0;
  long int rCount = 0;
  float numRev;
  // debug
  Serial.print("driveDistance() ");
  Serial.print(distance);
  Serial.print(" inches at ");
  Serial.print(motorPower);
  Serial.println(" power.");

  numRev = (float) distance / wheelCirc;
  Serial.println(numRev, 3);
  encoder.clearEnc(BOTH);  // clear the encoder count
  motors.drive(motorPower);

  while (lCount < (numRev*countsPerRev)){
    // while the left encoder is less than the target count -- debug print 
    // the encoder values and wait -- this is a holding loop.
    lCount = encoder.getTicks(LEFT);
    rCount = encoder.getTicks(RIGHT);
    Serial.print(lCount);
    Serial.print("\t");
    Serial.print(rCount);
    Serial.print("\t");
    Serial.println(numRev*countsPerRev);
  }
  // now apply "brakes" to stop the motors.
  motors.brake();
}*/
