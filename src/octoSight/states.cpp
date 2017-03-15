//
// Created by ronald on 18.2.17.
//

#include "math.h"
#include "states.h"
#include "Arduino.h"


int corners = 0;

int terminate() {
    if(state != FINDCANDLE and state != SOLVECANDLE and state != ADJUSTCANDLE and (flame[0] or flame[1] or flame[2] or flame [3] or flame[4])) return FINDCANDLE;
    switch(state) {
        case FINDCANDLE:
            
            break;
        case METWALL:
            
            break;
        case METLINE:
            //if(line[1] and line[3]) return GOALONGLINE;
            break;
        case GOALONGLINE:
            
            break;
        case SOLVECANDLE:
            if(line[0] or line[1] or line[2] or line[3] or line[4]) return KILL;
            break;
        case GOAHEAD:
            if(line[0] or line[1] or line[2] or line[3] or line[4]) return METLINE;
            break;
        case KILL:

            break;
        case ADJUSTCANDLE:

            break;
        case GOBACK:

            break;
    }
    return 0;
}

int goAlongLine() {
    Serial.println("Going along line");
    go(0, 180);
    go(50, -90);
    return GOAHEAD;
}

int goAhead() {
    Serial.println("Going ahead");
    return go(500);
}

int metLine() {
    Serial.println("Met line");
    int right = 0;
    int left = 0;
    while((!line[1] or !line[3]))
    {
        runSensors();
        if(line[1] or line[2] or line[3] or line [0] and line[4]) {
            right = 0, left = 0;
            if(line[0]) right -= 2;
            if(line[4]) left -= 2;
            if(line[2]) right += 1, left += 1;
            if(!line[3]) left += 1;
            if(!line[1]) right += 1;
        }
        else if(line[0] or line[4]){
            right = 0, left = 0;
            if(line[0]) left += 2;
            else right += 2;
        }
//        printSensors();
//        Serial.print(left);
//        Serial.print("\t");
//        Serial.println(right);
        go((left + right)/180.0*1, (-right + left) / (2*M_PI)*1);
    }
    return GOALONGLINE;
}

int findCandle() {
    Serial.println("Finding candle");
    int left = 0, right = 0;
    if (flame[0] or flame[1])
    {
        right = 2, left = -2;
    }
    else if(flame[3] or flame[4])
    {
        left = 2, right = -2;
    }
    runSensors();
    while(!flame[2])
    {
        go((left + right) / 180.0 * 1, (-right + left) / (2 * M_PI) * 1);
        runSensors();
    }
    return SOLVECANDLE;
}

int solveCandle() {
    Serial.println("Solving candle");
    int terminate;
    while(flame[2])
    {
        terminate = go(1);
        if(terminate) return terminate;
    }
    if(!flame[2]) return ADJUSTCANDLE;
}

int kill() {
    Serial.println("Killing candle");
    digitalWrite(fanPin, HIGH);
    delay(50);
    for(int i = 0; i < 20; i++) {
        go(0, 1);
        delay(1);
    }
    for(int i = 0; i < 40; i++) {
        go(0, -1);
        delay(1);
    }
    digitalWrite(fanPin, LOW);
    go(0, 20);
    return GOBACK;
}

int metWall() {
    Serial.println("Met wall");
}

int adjustCandle() {
    Serial.println("Adjust candle");
    int end;
    for(int i = 0; i < 10; i++)
    {
        end = go(0, (i % 2) ? pow(2, i) : -pow(2,i));
        if(end) return end;
    }
    return GOBACK;
}

int goBack()
{
    Serial.println("Going back");
    go(0, -140);
    go(20);
    return GOAHEAD;
}

/*
void goAlongLine() {
    Serial.println("Going along line");
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

void metLine() {
    Serial.println("Met line");
    int pairs = 0;
    int angle = 0;

    for (int a = 0; a < 4; a++) {
        for (int b = a + 1; b < 5; b++) {
            if (line[a] and line[b]) {
                angle = angleToLine(a, b);
                pairs++;
            }
        }
    }

    angle = angle / pairs;

    findCandle();
}

void findCandle() {
    Serial.println("Finding candle");
    go(0, 360);
    go(360);
    goAlongLine();
}

//solves a Candle once it is in reach of the sensors
void solveCandle() {
    Serial.println("Solving candle");
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

    long lineDelay = lineBaseDelay;

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

void metWall() {
    Serial.println("Met wall");
    /////////////////////////////////////////////////////////////////////////////////////
    // find angle to miss the obstacle

    digitalWrite(rightDirPin, HIGH);
    digitalWrite(leftDirPin, LOW);

    bool foundWall = 1;

    bool rHigh = 1;
    bool lHigh = 1;

    long lineDelay = lineBaseDelay;

    while (foundWall) {
        int actDelay = mDelay;
        lineDelay -= actDelay;

        if (rHigh) {
            digitalWrite(rightStepPin, HIGH);
        } else {
            digitalWrite(rightStepPin, LOW);
        }
        rHigh = !rHigh;


        if (lHigh) {
            digitalWrite(leftStepPin, HIGH);
        } else {
            digitalWrite(leftStepPin, LOW);
        }
        lHigh = !lHigh;


        if (lineDelay <= 0) {
            runSensors();

            //if (line[0] or line[1] or line[2] or line[3] or line[4]) metLine();
            if (flame[0] or flame[1] or flame[2] or flame[3] or flame[4]) solveCandle();
            if (USdis[1] > wallLimit + 10) foundWall = 0;

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

    lineDelay = lineBaseDelay;

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

            if (USdis[1] < wallLimit) metWall();
            if (USdis[2] < 40) rBaseDelay = mDelay * wheelRatio, lBaseDelay = mDelay;
            if (USdis[3] < 100) foundWall = 1;

            lineDelay = lineBaseDelay;
        }

        delayMicroseconds(actDelay);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // along the wall

    rHigh = 1;
    lHigh = 1;

    lineDelay = lineBaseDelay;

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
