//
// Created by ronald on 17.2.17.
//

#include "ultraSensors.h"

//from left to right
int USdis[4];

int UStime[4];

void initUltra()
{
  attachInterrupt(digitalPinToInterrupt(US0inPin), US0high, RISING);
  attachInterrupt(digitalPinToInterrupt(US0inPin), US0low, FALLING);
  attachInterrupt(digitalPinToInterrupt(US1inPin), US1high, RISING);
  attachInterrupt(digitalPinToInterrupt(US1inPin), US1low, FALLING);
  attachInterrupt(digitalPinToInterrupt(US2inPin), US2high, RISING);
  attachInterrupt(digitalPinToInterrupt(US2inPin), US2low, FALLING);
  attachInterrupt(digitalPinToInterrupt(US3inPin), US3high, RISING);
  attachInterrupt(digitalPinToInterrupt(US3inPin), US3low, FALLING);
}

void US0high()
{
  UStime[0] = micros();
}

void US1high()
{
  UStime[1] = micros();
}

void US2high()
{
  UStime[2] = micros();
}

void US3high()
{
  UStime[3] = micros();
}

void US0low()
{
  USdis[0] = (micros() - UStime[0]) / 58;
  digitalWrite(US0outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US0outPin, LOW);
}

void US1low()
{
  USdis[1] = (micros() - UStime[1]) / 58;
  digitalWrite(US1outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US1outPin, LOW);
}

void US2low()
{
  USdis[2] = (micros() - UStime[2]) / 58;
  digitalWrite(US2outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US2outPin, LOW);
}

void US3low()
{
  USdis[3] = (micros() - UStime[3]) / 58;
  digitalWrite(US3outPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US3outPin, LOW);
}
