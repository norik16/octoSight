//
// Created by ronald on 17.2.17.
//

#include "ultraSensors.h"

int US[8];

//from left to right
int USdis[4];
int USdisx[4][USmedian];
bool UShigh[4];

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
  for (int i = 0; i < 4; i++) USdis[i] = 10000;
  for (int i = 0; i < 4 * USmedian; i++) USdisx[i%4][i/4] = 10000;
}

void runUltra()
{
  if(!UShigh[0] && micros() - UStime[0] > USwait)
  {
    UShigh[0] = 1;
    US0();
  }
  if(!UShigh[1] && micros() - UStime[1] > USwait)
  {
    UShigh[1] = 1;
    US1();
  }
  if(!UShigh[2] && micros() - UStime[2] > USwait)
  {
    UShigh[2] = 1;
    US2();
  }
  if(!UShigh[3] && micros() - UStime[3] > USwait)
  {
    UShigh[3] = 1;
    US3();
  }
}

void US0()
{
  if (UShigh[0])
  {
    for(int i = 1; i < USmedian; i++) USdisx[0][i-1] = USdisx[0][i];
    USdisx[0][USmedian-1] = (micros() - UStime[0]) / UStocm;
    USdis[0] = median(USdisx[0], USmedian);
    digitalWrite(US0outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US0outPin, LOW);
    US[4]++;
    UStime[0] = micros();
  }
  else
  {
    UStime[0] = micros();
    US[0]++;
  }
  UShigh[0] = !UShigh[0];
}

void US1()
{
  if (UShigh[1])
  {
    USdis[1] = (micros() - UStime[1]) / UStocm;
    digitalWrite(US1outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US1outPin, LOW);
    US[5]++;
    UStime[1] = micros();
  }
  else
  {
    UStime[1] = micros();
    US[1]++;
  }
  UShigh[1] = !UShigh[1];
}

void US2()
{
  if (UShigh[2])
  {
    USdis[2] = (micros() - UStime[2]) / UStocm;
    digitalWrite(US1outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US1outPin, LOW);
    US[6]++;
    UStime[2] = micros();
  }
  else
  {
    UStime[2] = micros();
    US[2]++;
  }
  UShigh[2] = !UShigh[0];
}

void US3()
{
  if (UShigh[3])
  {
    USdis[3] = (micros() - UStime[3]) / UStocm;
    digitalWrite(US3outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US3outPin, LOW);
    US[7]++;
    UStime[3] = micros();
  }
  else
  {
    UStime[3] = micros();
    US[3]++;
  }
  UShigh[3] = !UShigh[3];
}
