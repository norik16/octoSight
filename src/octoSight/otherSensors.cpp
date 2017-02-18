//
// Created by ronald on 17.2.17.
//

#include "otherSensors.h"

bool line[5];

void initSensors()
{
  
}

void runSensors()
{
  line[0] = digitalRead(line0Pin);
  line[1] = digitalRead(line1Pin);
  line[2] = digitalRead(line2Pin);
  line[3] = digitalRead(line3Pin);
  line[4] = digitalRead(line4Pin);
}

void printSensors()
{
  Serial.print(line[0]);
  Serial.print(" ");
  Serial.print(line[1]);
  Serial.print(" ");
  Serial.print(line[2]);
  Serial.print(" ");
  Serial.print(line[3]);
  Serial.print(" ");
  Serial.print(line[4]);
  Serial.println();
}

