  //
// Created by ronald on 17.2.17.
//

#include <math.h>
//#include <Arduino.h>

#include "octoSight.h"

int state;

void setup() {
    //set pins as output

    //steppers
    pinMode(leftDirPin, OUTPUT);
    pinMode(leftStepPin, OUTPUT);
    pinMode(rightDirPin, OUTPUT);
    pinMode(rightStepPin, OUTPUT);

    //normal motors
    pinMode(leftPower, OUTPUT);
    pinMode(rightPower, OUTPUT);
    pinMode(leftDir, OUTPUT);
    pinMode(rightDir, OUTPUT);

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

//    printSensors();
    for(int i = 0; i < lineMedian; i++) runSensors();
//    printSensors();
    for(int i = 0; i < 5; i++) line[i] = 0;
//    printSensors();
    digitalWrite(fanPin, LOW);

    state = GOAHEAD;
}

  int go(float l, float angle) {
    int finished;
    float right;
    float left;

      int lSpeed;
      int rSpeed;

      long time;

//    long lineDelay = lineBaseDelay;

    left = l - d * angleConst * M_PI * angle / 180;
    right = l + d * angleConst * M_PI * angle / 180;

    right > 0 ? digitalWrite(rightDir, LOW) : digitalWrite(rightDir, HIGH);
    left > 0 ? digitalWrite(leftDir, LOW) : digitalWrite(leftDir, HIGH);


    right = abs(right);
    left = abs(left);

      if(right > left)
      {
          rSpeed = speedMod;
          lSpeed = speedMod * leftSpeedMod * left / right;
      }
      else
      {
          rSpeed = speedMod * right / left;
          lSpeed = speedMod * leftSpeedMod;
      }

      time = right / rSpeed * timeMod;

      long bTime = millis();

      analogWrite(leftPower, lSpeed);
      analogWrite(rightPower, rSpeed);
    while (bTime + time >= millis()) {

//        if (lineDelay <= 0) {
            runSensors();
            finished = terminate();
            if(finished)
            {
              //Serial.println("termnating");
                analogWrite(leftPower, 0);
                analogWrite(rightPower, 0);
              return finished;
            }

//            lineDelay = lineBaseDelay;
//        }
    }
      analogWrite(leftPower, 0);
      analogWrite(rightPower, 0);
      return 0;
}

//int go(float l, float angle) {
//    long rBaseDelay;
//    long lBaseDelay;
//    int finished;
//    float right;
//    float left;
//
//    long rDelay;
//    long lDelay;
//
//    long lineDelay = lineBaseDelay;
//
//    bool rHigh = 1;
//    bool lHigh = 1;
//
//    left = l * stepsPerCm - stepsPerCm * d * angleConst * M_PI * angle / 180;
//    right = l * stepsPerCm + stepsPerCm * d * angleConst * M_PI * angle / 180;
//
//    right > 0 ? digitalWrite(rightDirPin, HIGH) : digitalWrite(rightDirPin, LOW);
//    left > 0 ? digitalWrite(leftDirPin, HIGH) : digitalWrite(leftDirPin, LOW);
//
//    right = abs(right);
//    left = abs(left);
//
//    rBaseDelay = mDelay;
//    lBaseDelay = mDelay;
//    if(left and right)
//    {
//        if(right < left) rBaseDelay *= (left / right);
//        if(left < right) lBaseDelay *= (right / left);
//    }
//    else if(!left) lBaseDelay *= 1000000;
//    else if(!right)rBaseDelay *= 1000000;
//
////    Serial.println(left);
////    Serial.println(right);
////    Serial.println(lBaseDelay);
////    Serial.println(rBaseDelay);
////
////    Serial.println("going");
//
//    rDelay = rBaseDelay;
//    lDelay = lBaseDelay;
//
//    while (left > 0 or right > 0) {
//        int actDelay = min(rDelay, lDelay);
//        rDelay -= actDelay;
//        lDelay -= actDelay;
//        lineDelay -= actDelay;
//
//        if (rDelay <= 0) {
//            if (rHigh) {
//                digitalWrite(rightStepPin, HIGH);
//            } else {
//                digitalWrite(rightStepPin, LOW);
//                right--;
//            }
//            rDelay = rBaseDelay;
//            rHigh = !rHigh;
//        }
//
//        if (lDelay <= 0) {
//            if (lHigh) {
//                digitalWrite(leftStepPin, HIGH);
//            } else {
//                digitalWrite(leftStepPin, LOW);
//                left--;
//            }
//            lDelay = lBaseDelay;
//            lHigh = !lHigh;
//        }
//
//        if (lineDelay <= 0) {
//            runSensors();
//            finished = terminate();
//            if(finished)
//            {
//              //Serial.println("termnating");
//              return finished;
//            }
//
//            lineDelay = lineBaseDelay;
//        }
//
//        delayMicroseconds(actDelay);
//    }
//}

int go(int l) {
    return go(l, 0);
}

int time;
void loop() {
    switch(state)
    {
        case FINDCANDLE:
            state = findCandle();
            break;
        case METWALL:
            state = metWall();
            break;
        case METLINE:
            state = metLine();
            break;
        case GOALONGLINE:
            state = goAlongLine();
            break;
        case SOLVECANDLE:
            state = solveCandle();
            break;
        case GOAHEAD:
            state = goAhead();
            break;
        case KILL:
            state = kill();
            break;
        case ADJUSTCANDLE:
            state = adjustCandle();
            break;
        case GOBACK:
            state = goBack();
            break;
        case METWALLSOLVE:
            state = metWallSolve();
            break;
        default:
            state = GOAHEAD;
            break;
    }
//    go(20);
//    delay(1000);

    //findCandle();
//    runSensors();
//    printSensors();

////    go((1 + 2)/180.0*5, (-1 + 2) / (2*M_PI)*1);
//    analogWrite(leftPower, 255);
//    analogWrite(rightPower, 255);
//    delay(500);
//    digitalWrite(leftDir, HIGH);
//    digitalWrite(rightDir, HIGH);
//    go(0, 180);
//    delay(5000);
//    go(50, 90);
//    delay(5000);

    //go(20, 0);
    //Serial.println("aasdasd");
    //delay(5000);
//      digitalWrite(leftDir, LOW);
//      digitalWrite(rightDir, LOW);
//      analogWrite(leftPower, 0);
//      analogWrite(rightPower, 0);
//      delay(1000);
//      analogWrite(leftPower, 50);
//      analogWrite(rightPower, 50);
//      delay(2000);
//      analogWrite(leftPower, 150);
//      analogWrite(rightPower, 150);
//      delay(2000);
//      analogWrite(leftPower, 255);
//      analogWrite(rightPower, 255);
//      delay(4000);
//      digitalWrite(leftDir, HIGH);
//      digitalWrite(rightDir, HIGH);
//      analogWrite(leftPower, 0);
//      analogWrite(rightPower, 0);
//      delay(1000);
//      analogWrite(leftPower, 50);
//      analogWrite(rightPower, 50);
//      delay(2000);
//      analogWrite(leftPower, 150);
//      analogWrite(rightPower, 150);
//      delay(2000);
//      analogWrite(leftPower, 255);
//      analogWrite(rightPower, 255);
//      delay(4000);
}

