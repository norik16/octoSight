//
// Created by ronald on 17.2.17.
//

#include "otherSensors.h"

int line[5];
int lineRaw[5];
int lineMed[5][lineMedian];
int lineLastMed = 0;

int lastWhite = 0;
int lastWhiteAge = lineMedian;
int lastBlack = 0;
int lastBlackAge = lineMedian;


int flame[5];
bool bmp[2];

void initSensors() {
    for(int i = 0; i < 5; i++) line[i] = 0;
}

void runSensors() {
    bmp[0] = digitalRead(bmp0Pin);
    bmp[1] = digitalRead(bmp1Pin);

    lineRaw[0] = analogRead(line0Pin);
    lineRaw[1] = analogRead(line1Pin);
    lineRaw[2] = analogRead(line2Pin);
    lineRaw[3] = analogRead(line3Pin);
    lineRaw[4] = analogRead(line4Pin);

    flame[0] = analogRead(IR0Pin);
    flame[1] = analogRead(IR1Pin);
    flame[2] = analogRead(IR2Pin);
    flame[3] = analogRead(IR3Pin);
    flame[4] = analogRead(IR4Pin);
    int i;
    for (i = 0; i < 5; i++) {
        flame[i] = flameLimit[i] - flame[i];
        if (flame[i] < 0) flame[i] = 0;
    }

    for (i = 0; i < 5; i++) {
        /*if (median(lineMed[i], lineMedian) < whiteThreshold and lineRaw[i] > blackThreshold)
            line[i] = 1;*/
        if (/*max(lastBlack, median(lineMed[i], lineMedian)) - lineRaw[i] > blackWhiteDiff*/ lineRaw[i] < whiteThreshold) {
          line[i] = 1;
          lastWhite = lineRaw[i];
          lastWhiteAge = 0;
        }
        else if (/*min(median(lineMed[i], lineMedian), lastWhite) - lineRaw[i] < -blackWhiteDiff*/ lineRaw[i] > blackThreshold[i]) {
          line[i] = 0;
          lastBlack = lineRaw[i];
          lastBlackAge = 0;
        }
        lastBlackAge++;
        lastWhiteAge++;
        if(lastBlackAge >= lineMedian) lastBlack = 0;
        if(lastWhiteAge >= lineMedian) lastWhite = 10000;
        //else line[i] = 0;
        lineMed[i][lineLastMed] = lineRaw[i];
        lineLastMed = (lineLastMed + 1) % lineMedian;
    }

    runUltra();
    //printSensors();
}

void printSensors() {
    Serial.print("Line:\t");
    Serial.print(line[0]);
    Serial.print("\t");
    Serial.print(line[1]);
    Serial.print("\t");
    Serial.print(line[2]);
    Serial.print("\t");
    Serial.print(line[3]);
    Serial.print("\t");
    Serial.print(line[4]);
    Serial.print("LineRaw:\t");
    Serial.print(lineRaw[0]);
    Serial.print("\t");
    Serial.print(lineRaw[1]);
    Serial.print("\t");
    Serial.print(lineRaw[2]);
    Serial.print("\t");
    Serial.print(lineRaw[3]);
    Serial.print("\t");
    Serial.print(lineRaw[4]);
    Serial.print("\tFlame:\t");
    Serial.print(flame[0]);
    Serial.print("\t");
    Serial.print(flame[1]);
    Serial.print("\t");
    Serial.print(flame[2]);
    Serial.print("\t");
    Serial.print(flame[3]);
    Serial.print("\t");
    Serial.print(flame[4]);
    Serial.print("\tDistance:\t");
    Serial.print(USdis[0]);
    Serial.print("\t");
    Serial.print(USdis[1]);
    Serial.print("\t");
    Serial.print(USdis[2]);
    Serial.print("\t");
    Serial.print(USdis[3]);/*
    Serial.print(" UStime:\t");
    Serial.print(UStime[0]);
    Serial.print("\t");
    Serial.print(UStime[1]);
    Serial.print("\t");
    Serial.print(UStime[2]);
    Serial.print("\t");
    Serial.print(UStime[3]);*/
    Serial.print("\tBumper: ");
    Serial.print(bmp[0]);
    Serial.print(" ");
    Serial.print(bmp[1]);
    Serial.println();
}

