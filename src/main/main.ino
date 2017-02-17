
/* 
 Stepper Motor Control - speed control
 
 This program drives a unipolar or bipolar stepper motor. 
 The motor is attached to digital pins 8 - 11 of the Arduino.
 A potentiometer is connected to analog input 0.
 
 The motor will rotate in a clockwise direction. The higher the potentiometer value,
 the faster the motor speed. Because setSpeed() sets the delay between steps, 
 you may notice the motor is less responsive to changes in the sensor value at
 low speeds.
 
 Created 30 Nov. 2009
 Modified 28 Oct 2010
 by Tom Igoe;
 
 */

#include "main.h"
#include "config.h"
#include "otherSensors.h"
#include "ultraSensors.h"

#include "otherSensors.h"
#include "ultraSensors.h"

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

int stepCount = 0;  // number of steps the motor has taken

void setup()
{
    //set pins as output
    
    //wheels
    pinMode(leftDir, OUTPUT);
    pinMode(leftStep, OUTPUT);
    pinMode(rightDir, OUTPUT);
    pinMode(rightStep, OUTPUT);
    
    //fan
    pinMode(fan, OUTPUT);
    
    
    //input analog
    
    //IR candle from right to left
    pinMode(IR0, INPUT);
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    
    
    //input digital
    
    //ultra sound from
    pinMode(US0in, INPUT);
    pinMode(US0out, INPUT);
    pinMode(US1in, INPUT);
    pinMode(US1out, INPUT);
    
    //IR line from right to left
    pinMode(lineSensor0, INPUT);
    pinMode(lineSensor1, INPUT);
    pinMode(lineSensor2, INPUT);
    pinMode(lineSensor3, INPUT);
    pinMode(lineSensor4, INPUT);
    
    //bumper from right to left
    pinMode(bmp0, INPUT);
    pinMode(bmp1, INPUT);
    
    //switch
    pinMode(power, INPUT);

}

void go(int l, int angle)
{
    if (l > 0) {
        digitalWrite(leftDir, HIGH);
        digitalWrite(rightDir, HIGH);

        int right = 0;

        int left = 0;

        for(int x = 0; x < l * stepsPerCm * max(); x++) {
            digitalWrite(leftStep, HIGH);
            digitalWrite(rightStep, HIGH);
            delayMicroseconds(500);
            digitalWrite(leftStep, LOW);
            digitalWrite(rightStep, LOW);
            delayMicroseconds(500);
        }
    } else if (l < 0) {
        digitalWrite(leftDir, LOW);
        digitalWrite(rightDir, LOW);
    } else {

    }
    l > 0 ? digitalWrite(leftDir, HIGH) : digitalWrite(leftDir, LOW);
    l > 0 ? digitalWrite(leftDir, HIGH) : digitalWrite(leftDir, LOW);

}

void loop()
{
  // read the sensor value:
  int sensorReading = analogRead(A0);
  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  // set the motor speed:
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution/100);
  } 
}


