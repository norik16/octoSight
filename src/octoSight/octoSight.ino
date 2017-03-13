  //
// Created by ronald on 17.2.17.
//

#include <math.h>
//#include <Arduino.h>

#include "octoSight.h"

int state;

void setup() {
    //set pins as output

    //wheels
    pinMode(leftDirPin, OUTPUT);
    pinMode(leftStepPin, OUTPUT);
    pinMode(rightDirPin, OUTPUT);
    pinMode(rightStepPin, OUTPUT);

    //fan
    pinMode(fanPin, OUTPUT);
    digitalWrite(fanPin, LOW);


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

    for(int i = 0; i < lineMedian; i++) runSensors();
    for(int i = 0; i < 5; i++) line[i] = 0;

    state = GOALONGLINE;
}

int go(int l, int angle) {
    long rBaseDelay;
    long lBaseDelay;
    int finished;
    float right;
    float left;

    long rDelay;
    long lDelay;

    long lineDelay = lineBaseDelay;

    bool rHigh = 1;
    bool lHigh = 1;

//    if (l) {
//        l > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
//        l > 0 ? digitalWrite(leftDirPin, HIGH) : digitalWrite(leftDirPin, LOW);

    if (angle > 0) {
        right = l * stepsPerCm;
        left = right - d * angleConst * M_PI * angle / 180;

        rBaseDelay = mDelay;
        lBaseDelay = abs((int) (mDelay * (left and right ? (right / left) : 1000000)));

    } else {
        left = l * stepsPerCm;
        right = left - d * angleConst * M_PI * abs(angle) / 180;

        rBaseDelay = abs((int) (mDelay * (right and left ? (left / right) : 1000000)));
        lBaseDelay = mDelay;
    }
    right > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
    left > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);

    Serial.println(left);
    Serial.println(right);
    Serial.println(lBaseDelay);
    Serial.println(rBaseDelay);

    right = abs(right);
    left = abs(left);
    
//    }
//    else {
//        angle > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
//        angle > 0 ? digitalWrite(leftDirPin, LOW) : digitalWrite(leftDirPin, HIGH);
//
//        right = M_PI * d * angleConst * abs(angle) * stepsPerCm / 180;
//        left = right;
//
//        rBaseDelay = mDelay;
//        lBaseDelay = mDelay;
//    }
    Serial.println("going");

    rDelay = rBaseDelay;
    lDelay = lBaseDelay;

    while (left >= 0 or right >= 0) {
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
            finished = terminate();
            if(finished)
            {
              //Serial.println("termnating");
              return finished;
            }

            lineDelay = lineBaseDelay;
        }

        delayMicroseconds(actDelay);
    }
}

int go(int l) {
    return go(l, 0);
}

//int time;
void loop() {
//    switch(state)
//    {
//        case FINDCANDLE:
//            state = findCandle();
//            break;
//        case METWALL:
//            state = metWall();
//            break;
//        case METLINE:
//            state = metLine();
//            break;
//        case GOALONGLINE:
//            state = goAlongLine();
//            break;
//        case SOLVECANDLE:
//            state = solveCandle();
//            break;
//        case GOAHEAD:
//            state = goAhead();
//            break;
//        default:
//            state = 0;
//            break;
//    }
//    go(20);
//    delay(1000);

    //findCandle();
    //runSensors();
    //printSensors();

    //go(20, 0);
    //Serial.println("aasdasd");
    //delay(5000);
}

