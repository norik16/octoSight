//
// Created by ronald on 17.2.17.
//

#include <math.h>
//#include <arduino.h>

#include "octoSight.h"
#include "config.h"

#include "otherSensors.h"
#include "ultraSensors.h"
#include "states.h"

void setup()
{
    //set pins as output
    
    //wheels
    pinMode(leftDirPin, OUTPUT);
    pinMode(leftStepPin, OUTPUT);
    pinMode(rightDirPin, OUTPUT);
    pinMode(rightStepPin, OUTPUT);
    
    //fan
    pinMode(fanPin, OUTPUT);
    
    
    //input analog
    
    //IR candle from right to left
    pinMode(IR0Pin, INPUT);
    pinMode(IR1Pin, INPUT);
    pinMode(IR2Pin, INPUT);
    
    
    //input digital
    
    //ultra sound from
    pinMode(US0inPin, INPUT);
    pinMode(US0outPin, INPUT);
    pinMode(US1inPin, INPUT);
    pinMode(US1outPin, INPUT);
    
    //IR line from right to left
    pinMode(line0Pin, INPUT);
    pinMode(line1Pin, INPUT);
    pinMode(line2Pin, INPUT);
    pinMode(line3Pin, INPUT);
    pinMode(line4Pin, INPUT);
    
    //bumper from right to left
    pinMode(bmp0Pin, INPUT);
    pinMode(bmp1Pin, INPUT);
    
    //switch
    pinMode(powerPin, INPUT);

    Serial.begin(9600);

    initSensors();
    initUltra();
}

void go(int l, int angle)
{
    l > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
    l > 0 ? digitalWrite(leftDirPin, HIGH) : digitalWrite(leftDirPin, LOW);

    if (l) {
        l = abs(l);
        int rBaseDelay;
        int lBaseDelay;
        int right;
        int left;

        if (angle > 0) {
            right = l * stepsPerCm;
            left = right * (1 - (2*d*pi*angle)/right);

            rBaseDelay = mDelay;
            lBaseDelay = mDelay * (right/left);

        } else {
            left = l * stepsPerCm;
            right = left * (1 - (2*d*pi*abs(angle))/left);

            rBaseDelay = mDelay * (left/right);
            lBaseDelay = mDelay;
        }

        int rDelay = rBaseDelay;
        int lDelay = lBaseDelay;

        int lineDelay = lineBaseDelay;

        bool rHigh = 1;
        bool lHigh = 1;

        Serial.print(rDelay);
        Serial.print(" ");
        Serial.print(lDelay);
        Serial.println(" ");

        while (left >= 0 and right >= 0) {
            int actDelay = min(rDelay, lDelay);
            rDelay -= actDelay;
            lDelay -= actDelay;
            lineDelay -= actDelay;

            if (rDelay <= 0) {
                if (rHigh) {
                    digitalWrite(rightStepPin, HIGH);
                } else {
                    digitalWrite(rightStepPin, LOW);
                    right--;
                }
                rDelay = rBaseDelay;
                rHigh = !rHigh;
            }

            if (lDelay <= 0) {
                if (lHigh) {
                    digitalWrite(leftStepPin, HIGH);
                } else {
                    digitalWrite(leftStepPin, LOW);
                    left--;
                }
                lDelay = lBaseDelay;
                lHigh = !lHigh;
            }

            if (lineDelay <= 0) {
                runSensors();
                if (line[0] or line[1] or line[2] or line[3] or line[4]) {
                    metLine();
                }
            }

            delayMicroseconds(actDelay);
        }
    } else {
        angle > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
        angle > 0 ? digitalWrite(leftDirPin, LOW) : digitalWrite(leftDirPin, HIGH);

        int right = 2*pi*d*abs(angle)*stepsPerCm;
        int left = right;
    }
}

void go(int l)
{
    go(l, 0);
}

void loop()
{
  //runSensors();
  //printSensors();

  go(50);
  delay(5000);
}


