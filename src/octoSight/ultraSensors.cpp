//
// Created by ronald on 17.2.17.
//

#include "ultraSensors.h"

int US[8];

//from left to right
int USdis[4];
int USdisOld[4][USmedian];
bool UShigh[4];

int ultraLastMed[4];

unsigned long UStime[4];

void initUltra()
{
  attachInterrupt(digitalPinToInterrupt(US0inPin), US0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(US1inPin), US1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(US2inPin), US2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(US3inPin), US3, CHANGE);
  for (int i = 0; i < 8; i++) US[i] = 0;
  for (int i = 0; i < 4; i++) UShigh[i] = 1;
  for (int i = 0; i < 4; i++) UStime[i] = 0;
  US0();
  US1();
  US2();
  US3();
  for (int i = 0; i < 4; i++) USdis[i] = 10000;
  for (int i = 0; i < 4 * USmedian; i++) USdisOld[i%4][i/4] = 10000;
}

void runUltra() {
    if (!UShigh[0] && micros() - UStime[0] > USwaitlow || UShigh[0] && micros() - UStime[0] > USwaithigh) {
        UShigh[0] = 1;
        US0();
    }
    if (!UShigh[1] && micros() - UStime[1] > USwaitlow || UShigh[1] && micros() - UStime[1] > USwaithigh) {
        UShigh[1] = 1;
        US1();
    }
    if (!UShigh[2] && micros() - UStime[2] > USwaitlow || UShigh[2] && micros() - UStime[2] > USwaithigh) {
        UShigh[2] = 1;
        US2();
    }
    if (!UShigh[3] && micros() - UStime[3] > USwaitlow || UShigh[3] && micros() - UStime[3] > USwaithigh) {
        UShigh[3] = 1;
        US3();
    }
}

void US0() {
    if (UShigh[0]) {
        if((micros() - UStime[0]) / UStocm < 1000) {
            USdisOld[0][ultraLastMed[0]] = (micros() - UStime[0]) / UStocm;
            ultraLastMed[0] = ultraLastMed[0] < USmedian - 1 ? ultraLastMed[0] + 1 : 0;
            USdis[0] = median(USdisOld[0], USmedian);
        }
        digitalWrite(US0outPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(US0outPin, LOW);
        US[4]++;
        UStime[0] = micros();
    } else {
        UStime[0] = micros();
        US[0]++;
    }
    UShigh[0] = !UShigh[0];
}

void US1() {
    if (UShigh[1]) {
        if((micros() - UStime[1]) / UStocm < 1000) {
            USdisOld[1][ultraLastMed[1]] = (micros() - UStime[1]) / UStocm;
            ultraLastMed[1] = ultraLastMed[1] < USmedian - 1 ? ultraLastMed[1] + 1 : 0;
            USdis[1] = median(USdisOld[1], USmedian);
        }
        digitalWrite(US1outPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(US1outPin, LOW);
        US[5]++;
        UStime[1] = micros();
    } else {
        UStime[1] = micros();
        US[1]++;
    }
    UShigh[1] = !UShigh[1];
}

void US2() {
    if (UShigh[2]) {
        if((micros() - UStime[2]) / UStocm < 1000) {
            USdisOld[2][ultraLastMed[2]] = (micros() - UStime[2]) / UStocm;
            ultraLastMed[2] = ultraLastMed[2] < USmedian - 1 ? ultraLastMed[2] + 1 : 0;
            USdis[2] = median(USdisOld[2], USmedian);
        }
        digitalWrite(US2outPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(US2outPin, LOW);
        US[5]++;
        UStime[2] = micros();
    } else {
        UStime[2] = micros();
        US[2]++;
    }
    UShigh[2] = !UShigh[2];
}

void US3() {
    if (UShigh[3]) {
        if((micros() - UStime[3]) / UStocm < 1000) {
            USdisOld[3][ultraLastMed[3]] = (micros() - UStime[3]) / UStocm;
            ultraLastMed[3] = ultraLastMed[3] < USmedian - 1 ? ultraLastMed[3] + 1 : 0;
            USdis[3] = median(USdisOld[3], USmedian);
        }
        digitalWrite(US3outPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(US3outPin, LOW);
        US[7]++;
        UStime[3] = micros();
    } else {
        UStime[3] = micros();
        US[3]++;
    }
    UShigh[3] = !UShigh[3];
}
