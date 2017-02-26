//
// Created by ronald on 17.2.17.
//

#include "ultraSensors.h"

int US[8];

//from left to right
int USdis[4];
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
  US0();
  US1();
  US2();
  US3();
  for (int i = 0; i < 4; i++) USdis[i] = 10000;
}

void US0()
{
  if (UShigh[0])
  {
    USdis[0] = (micros() - UStime[0]) / 58;
    digitalWrite(US0outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US0outPin, LOW);
    US[4]++;
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
    USdis[1] = (micros() - UStime[1]) / 58;
    digitalWrite(US1outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US1outPin, LOW);
    US[5]++;
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
    USdis[2] = (micros() - UStime[2]) / 58;
    digitalWrite(US1outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US1outPin, LOW);
    US[6]++;
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
    USdis[3] = (micros() - UStime[3]) / 58;
    digitalWrite(US3outPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(US3outPin, LOW);
    US[7]++;
  }
  else
  {
    UStime[3] = micros();
    US[3]++;
  }
  UShigh[3] = !UShigh[3];
}
