//
// Created by ronald on 17.2.17.
//

#include <math.h>
//#include <Arduino.h>


#include "octoSight.h"

void setup() {
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
    pinMode(US0outPin, OUTPUT);
    pinMode(US1inPin, INPUT);
    pinMode(US1outPin, OUTPUT);
    pinMode(US2inPin, INPUT);
    pinMode(US2outPin, OUTPUT);
    pinMode(US3inPin, INPUT);
    pinMode(US3outPin, OUTPUT);

    //IR line from right to left
    pinMode(line0Pin, INPUT);
    pinMode(line1Pin, INPUT);
    pinMode(line2Pin, INPUT);
    pinMode(line3Pin, INPUT);
    pinMode(line4Pin, INPUT);

    //bumper from right to left
    pinMode(bmp0Pin, INPUT_PULLUP);
    pinMode(bmp1Pin, INPUT_PULLUP);

    //switch
    pinMode(powerPin, INPUT);

    Serial.begin(9600);

    initSensors();
    initUltra();
}

void go(int l, int angle) {
    int rBaseDelay;
    int lBaseDelay;
    float right;
    float left;

    int rDelay;
    int lDelay;

    long lineDelay = lineBaseDelay;

    bool rHigh = 1;
    bool lHigh = 1;

    if (l) {
        l > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
        l > 0 ? digitalWrite(leftDirPin, HIGH) : digitalWrite(leftDirPin, LOW);

        l = abs(l);

        if (angle > 0) {
            right = l * stepsPerCm;  //
            left = right - d * angleConst * M_PI * angle / 180;

            rBaseDelay = mDelay;
            lBaseDelay = (int) (mDelay * (right / left));

        } else {
            left = l * stepsPerCm;
            right = left - d * angleConst * M_PI * abs(angle) / 180;

            rBaseDelay = (int) (mDelay * (left / right));
            lBaseDelay = mDelay;
        }

    Serial.print(rBaseDelay);
        Serial.print(" ");
        Serial.print(lBaseDelay);
        Serial.print(" ");
       Serial.print(right);
        Serial.print(" ");
        Serial.print(left);
       Serial.println(" ");

    } else {
        angle > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
        angle > 0 ? digitalWrite(leftDirPin, LOW) : digitalWrite(leftDirPin, HIGH);

        right = M_PI * d * angleConst * abs(angle) * stepsPerCm / 180;
        left = right;

        rBaseDelay = mDelay;
        lBaseDelay = mDelay;

      
    }

    rDelay = rBaseDelay;
    lDelay = lBaseDelay;

    while (left >= 0 and right >= 0) {
        int actDelay = min(rDelay, lDelay);
        rDelay -= actDelay;
        lDelay -= actDelay;
        lineDelay -= actDelay;
        /*Serial.print(rHigh);
        Serial.print("\t");
        Serial.print(lHigh);
        Serial.print("\t");
        Serial.print(rDelay);
        Serial.print("\t");
        Serial.print(lDelay);
        Serial.print("\t");
        Serial.print(right);
        Serial.print("\t");
        Serial.print(left);
        Serial.println();*/

        if (rDelay <= 0) {
            if (rHigh) {
                digitalWrite(rightStepPin, HIGH);
            } else {
                digitalWrite(rightStepPin, LOW);
                right--;
            }
            rDelay = rBaseDelay;
            rHigh = !rHigh;
            
      //  Serial.print(right);
   //    Serial.println(" ");
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
            
       // Serial.print(left);
    //   Serial.println(" ");
        }

        if (lineDelay <= 0) {
            runSensors();
            if (line[0] or line[1] or line[2] or line[3] or line[4]) metLine();
            if (flame[0] or flame[1] or flame[2] or flame[3] or flame[4]) solveCandle();
            if (USdis[1] < 110 or USdis[2] < 110) metWall();

            lineDelay = lineBaseDelay;
        }

        delayMicroseconds(actDelay);
    }
}

void go(int l) {
    go(l, 0);
}

//int time;
void loop() {
    runSensors();
    printSensors();

    //go(20, 0);
    //Serial.println("aasdasd");
    //delay(5000);
}

