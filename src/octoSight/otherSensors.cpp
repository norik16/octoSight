//
// Created by ronald on 17.2.17.
//

#include "otherSensors.h"

int line[5];
int lineRaw[5];
int lineMed[5][lineMedian];
int lineLastMed = 0;

int flame[5];
bool bmp[2];

void initSensors() {

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

    for (int i = 0; i < 5; i++) {
        flame[i] = flameLimit - flame[i];
        if (flame[i] < 0) flame[i] = 0;
    }

    for (int i = 0; i < 5; i++) {
        if (median(lineMed[i], sizeof(lineMed[i])/sizeof(lineMed[i][0])) < whiteThreshold and lineRaw[i] > blackThreshold)
            line[i] = 1;
        lineMed[i][lineLastMed] = lineRaw[i];
        lineLastMed = (lineLastMed + 1) % sizeof(lineMed[i])/sizeof(lineMed[i][0]);
    }

    runUltra();
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
    Serial.print(USdis[3]);
    Serial.print(" UStime:\t");
    Serial.print(UStime[0]);
    Serial.print("\t");
    Serial.print(UStime[1]);
    Serial.print("\t");
    Serial.print(UStime[2]);
    Serial.print("\t");
    Serial.print(UStime[3]);
    Serial.print("\tBumper: ");
    Serial.print(bmp[0]);
    Serial.print(" ");
    Serial.print(bmp[1]);
    Serial.print(" ");
}

