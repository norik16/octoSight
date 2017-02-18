//
// Created by ronald on 17.2.17.
//

#include "ultraSensors.h"

int US0dis;
int US1dis;

int US0time;
int US1time;

void initUltra()
{
  attachInterrupt(digitalPinToInterrupt(US0inPin), US0high, RISING);
  attachInterrupt(digitalPinToInterrupt(US1inPin), US1high, RISING);
  attachInterrupt(digitalPinToInterrupt(US1inPin), US0low, RISING);
}

void US0high()
{
  US0time = micros();
}

void US1high()
{
  US1time = micros();
}

void US0low()
{
  US0dis = (micros() - US0time) / 58;
  digitalWrite(US0outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US0outPin, LOW);
}

void US1low()
{
  US1dis = (micros() - US1time) / 58;
  digitalWrite(US1outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US1outPin, LOW);
}


