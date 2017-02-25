//
// Created by ronald on 18.2.17.
//

#include "math.h"
#include "states.h"
/*
int * USdis;
float wheelRatio;

int corners = 0;

void goAlongLine()
{
    corners++;
    if (corners < 6) {
        go(0, 180);
        go(50, -90);
    } else {
        go(0, 135);
        go(360);
    }
    go(360);
}

void metLine()
{
    int pairs = 0;
    int angle = 0;

    for (int a = 0; a < 4; a++) {
        for (int b = a+1; b < 5; b++) {
            if (line[a] and line[b]) {
                angle = angleToLine(a, b);
                pairs++;
            }
        }
    }

    angle = angle/pairs;

    findCandle();
}

void findCandle()
{
    go(0, 360);
    goAlongLine();
}

//solves a Candle once it is in reach of the sensors
void solveCandle()
{
    int angle = 0;
    runSensors();
    if (flame[0] > 0) angle = -75;
    if (flame[1] > 0) angle = -25;
    if (flame[2] > 0) angle = 0;
    if (flame[3] > 0) angle = 25;
    if (flame[4] > 0) angle = 75;

    go(0, angle);

    bool foundLine = 0;

    int rBaseDelay = mDelay;
    int lBaseDelay = mDelay;

    int rDelay = mDelay;
    int lDelay = mDelay;

    int lineDelay = lineBaseDelay;

    bool rHigh = 1;
    bool lHigh = 1;

    while (!foundLine) {

        int actDelay = min(rDelay, lDelay);
        rDelay -= actDelay;
        lDelay -= actDelay;
        lineDelay -= actDelay;

        if (rDelay <= 0) {
            if (rHigh) {
                digitalWrite(rightStepPin, HIGH);
            } else {
                digitalWrite(rightStepPin, LOW);
            }
            rDelay = rBaseDelay;
            rHigh = !rHigh;
        }

        if (lDelay <= 0) {
            if (lHigh) {
                digitalWrite(leftStepPin, HIGH);
            } else {
                digitalWrite(leftStepPin, LOW);
            }
            lDelay = lBaseDelay;
            lHigh = !lHigh;
        }

        if (lineDelay <= 0) {
            runSensors();

            if (line[0] or line[1] or line[2] or line[3] or line[4]) foundLine = 1;
            if (flame[1] > 0) rBaseDelay = mDelay * wheelRatio, lBaseDelay = mDelay;
            if (flame[3] > 0) rBaseDelay = mDelay, lBaseDelay = mDelay * wheelRatio;
            if (flame[2] > 0) rBaseDelay = mDelay, lBaseDelay = mDelay;

            if (USdis[1] < 40) rBaseDelay = mDelay, lBaseDelay = mDelay * wheelRatio;
            if (USdis[2] < 40) rBaseDelay = mDelay * wheelRatio, lBaseDelay = mDelay;

            lineDelay = lineBaseDelay;
        }

        delayMicroseconds(actDelay);
    }

    digitalWrite(fanPin, HIGH);

    runSensors();
    while (flame[1] or flame[2] or flame[3]) {
        delayMicroseconds(500000);
        go(0, 10);
        go(0, -20);
        go(0, 10);
        runSensors();
    }
    digitalWrite(fanPin, LOW);

    go(0, 180);
    go(360);
}

void metWall()
{

    /////////////////////////////////////////////////////////////////////////////////////
    // find angle to miss the obstacle

    digitalWrite(rightDirPin, HIGH);
    digitalWrite(leftDirPin, LOW);

    bool foundWall = 1;

    bool rHigh = 1;
    bool lHigh = 1;

    int lineDelay = lineBaseDelay;

    while (foundWall) {
        int actDelay = mDelay;
        lineDelay -= actDelay;

        if (rHigh) {
            digitalWrite(rightStepPin, HIGH);
        } else {
            digitalWrite(rightStepPin, LOW);
            right--;
        }
        rDelay = rBaseDelay;
        rHigh = !rHigh;


        if (lHigh) {
            digitalWrite(leftStepPin, HIGH);
        } else {
            digitalWrite(leftStepPin, LOW);
            left--;
        }
        lDelay = lBaseDelay;
        lHigh = !lHigh;


        if (lineDelay <= 0) {
            runSensors();

            if (line[0] or line[1] or line[2] or line[3] or line[4]) metLine();
            if (flame[0] or flame[1] or flame[2] or flame[3] or flame[4]) solveCandle();
            if (USdis[2] > 500) foundWall = 0;

            lineDelay = lineBaseDelay;
        }

        delayMicroseconds(actDelay);
    }

    //TODO: find right const
    //go(0, -6);


    /////////////////////////////////////////////////////////////////////////////////////
    // approach the wall

    int rBaseDelay = mDelay;
    int lBaseDelay = mDelay;

    int rDelay = mDelay;
    int lDelay = mDelay;

    int lineDelay = lineBaseDelay;

    rHigh = 1;
    lHigh = 1;

    digitalWrite(rightDirPin, HIGH);
    digitalWrite(leftDirPin, HIGH);

    while (!foundWall) {

        int actDelay = min(rDelay, lDelay);
        rDelay -= actDelay;
        lDelay -= actDelay;
        lineDelay -= actDelay;

        if (rDelay <= 0) {
            if (rHigh) {
                digitalWrite(rightStepPin, HIGH);
            } else {
                digitalWrite(rightStepPin, LOW);
            }
            rDelay = rBaseDelay;
            rHigh = !rHigh;
        }

        if (lDelay <= 0) {
            if (lHigh) {
                digitalWrite(leftStepPin, HIGH);
            } else {
                digitalWrite(leftStepPin, LOW);
            }
            lDelay = lBaseDelay;
            lHigh = !lHigh;
        }

        if (lineDelay <= 0) {
            runSensors();

            if (line[0] or line[1] or line[2] or line[3] or line[4]) metLine();
            if (flame[0] or flame[1] or flame[2] or flame[3] or flame[4]) solveCandle();

            if (USdis[1] < 110) metWall();
            if (USdis[2] < 40) rBaseDelay = mDelay * wheelRatio, lBaseDelay = mDelay;
            if (USdis[3] < 500) foundWall = 1;

            lineDelay = lineBaseDelay;
        }

        delayMicroseconds(actDelay);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // along the wall

    rHigh = 1;
    lHigh = 1;

    digitalWrite(rightDirPin, HIGH);
    digitalWrite(leftDirPin, HIGH);

    while (foundWall) {

        int actDelay = min(rDelay, lDelay);
        rDelay -= actDelay;
        lDelay -= actDelay;
        lineDelay -= actDelay;

        if (rDelay <= 0) {
            if (rHigh) {
                digitalWrite(rightStepPin, HIGH);
            } else {
                digitalWrite(rightStepPin, LOW);
            }
            rDelay = rBaseDelay;
            rHigh = !rHigh;
        }

        if (lDelay <= 0) {
            if (lHigh) {
                digitalWrite(leftStepPin, HIGH);
            } else {
                digitalWrite(leftStepPin, LOW);
            }
            lDelay = lBaseDelay;
            lHigh = !lHigh;
        }

        if (lineDelay <= 0) {
            runSensors();

            if (line[0] or line[1] or line[2] or line[3] or line[4]) metLine();
            if (flame[0] or flame[1] or flame[2] or flame[3] or flame[4]) solveCandle();
            if (USdis[1] < 150) metWall(); //found another wall on left
            if (USdis[2] < 40) metWall();
            if (USdis[3] < 50) rBaseDelay = mDelay, lBaseDelay = mDelay * wheelRatio;
            else if (USdis[3] > 500) foundWall = 0;
            else if (USdis[3] > 60) rBaseDelay = mDelay * wheelRatio, lBaseDelay = mDelay;
            else rBaseDelay = mDelay, lBaseDelay = mDelay;

            lineDelay = lineBaseDelay;
        }

        delayMicroseconds(actDelay);
    }

    go(360);
}*/
