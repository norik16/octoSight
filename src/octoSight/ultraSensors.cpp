//
// Created by ronald on 17.2.17.
//

#include "ultraSensors.h"

//from left to right
int USdis[4];

int US1dis;
int US2dis;

int US1time;
int US2time;

void initUltra()
{
  attachInterrupt(digitalPinToInterrupt(US1inPin), US1high, RISING);
  attachInterrupt(digitalPinToInterrupt(US2inPin), US2high, RISING);
  attachInterrupt(digitalPinToInterrupt(US2inPin), US1low, RISING);
}

void US1high()
{
  US1time = micros();
}

void US2high()
{
  US2time = micros();
}

void US1low()
{
  USdis[1] = (micros() - US1time) / 58;
  digitalWrite(US1outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US1outPin, LOW);
}

void US2low()
{
  USdis[2] = (micros() - US2time) / 58;
  digitalWrite(US2outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US2outPin, LOW);
}


