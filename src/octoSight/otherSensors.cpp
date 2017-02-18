//
// Created by ronald on 17.2.17.
//

#include "otherSensors.h"

bool line0;
bool line1;
bool line2;
bool line3;
bool line4;

void initSensors()
{
  
}

void runSensors()
{
  line0 = digitalRead(lineSensor0);
  line1 = digitalRead(lineSensor1);
  line2 = digitalRead(lineSensor2);
  line3 = digitalRead(lineSensor3);
  line4 = digitalRead(lineSensor4);
}

void printSensors()
{
  Serial.print(line0);
  Serial.print(" ");
  Serial.print(line1);
  Serial.print(" ");
  Serial.print(line2);
  Serial.print(" ");
  Serial.print(line3);
  Serial.print(" ");
  Serial.print(line4);
  Serial.println();
}

