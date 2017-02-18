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
  line0 = digitalRead(line0Pin);
  line1 = digitalRead(line1Pin);
  line2 = digitalRead(line2Pin);
  line3 = digitalRead(line3Pin);
  line4 = digitalRead(line4Pin);
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

