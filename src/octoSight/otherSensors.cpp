//
// Created by ronald on 17.2.17.
//

#include "otherSensors.h"

bool line[5];
bool flame[5];

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

  flame[0] = analogRead(IR0Pin);
  flame[1] = analogRead(IR1Pin);
  flame[2] = analogRead(IR2Pin);
  flame[3] = analogRead(IR3Pin);
  flame[4] = analogRead(IR4Pin);

  for(int i = 0; i < 5; i++)
  {
    flame[i] = flameLimit - flame[i];
    if(flame[i] < 0) flame[i] = 0;
  }
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

