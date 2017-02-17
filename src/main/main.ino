//
// Created by ronald on 17.2.17.
//

#include "main.h"
#include "config.h"
#include "otherSensors.h"
#include "ultraSensors.h"

#include "otherSensors.h"
#include "ultraSensors.h"

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
    l > 0 ? digitalWrite(rightDir, HIGH) : digitalWrite(rightDir, LOW);
    l > 0 ? digitalWrite(leftDir, HIGH) : digitalWrite(leftDir, LOW);

    if (l) {
        l = abs(l);

        if (angle > 0) {
            int right = l * stepsPerCm;
            int left = right * (1 - (2*d*pi*angle)/right);

            int rBaseDelay = mDelay;
            int lBaseDelay = mDelay * (right/left);

        } else {
            int left = l * stepsPerCm;
            int right = left * (1 - (2*d*pi*abs(angle))/left);

            int rBaseDelay = mDelay * (left/right);
            int lBaseDelay = mDelay;
        }

        int rDelay = rBaseDelay;
        int lDelay = lBaseDelay;

        bool rHigh = 1;
        bool lHigh = 1;

        while (left and right) {
            actDelay = min(rDelay, lDelay);
            rDelay -= actDelay;
            lDelay -= actDelay;

            if (!rDelay) {
                if (rHigh) {
                    digitalWrite(rightStep, HIGH);
                } else {
                    digitalWrite(rightStep, LOW);
                    right--;
                }
                rDelay = rBaseDelay;
                rHigh = !rHigh;
            }

            if (!lDelay) {
                if (lHigh) {
                    digitalWrite(leftStep, HIGH);
                } else {
                    digitalWrite(leftStep, LOW);
                    left--;
                }
                lDelay = lBaseDelay;
                lHigh = !lHigh;
            }
        }
    } else {
        angle > 0 ? digitalWrite(rightDir, HIGH) : digitalWrite(rightDir, LOW);
        angle > 0 ? digitalWrite(leftDir, LOW) : digitalWrite(leftDir, HIGH);

        int right = 2*pi*d*abs(angle)*stepsPerCm;
        int left = right;
    }
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


