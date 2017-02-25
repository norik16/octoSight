//
// Created by ronald on 17.2.17.
//

#include "otherSensors.h"

int line[5];
int flame[5];
bool bmp[2];

void initSensors()
{
  
}

void runSensors()
{
  bmp[0] = digitalRead(bmp0Pin);
  bmp[1] = digitalRead(bmp1Pin);
  
  line[0] = analogRead(line0Pin);
  line[1] = analogRead(line1Pin);
  line[2] = analogRead(line2Pin);
  line[3] = analogRead(line3Pin);
  line[4] = analogRead(line4Pin);

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
  Serial.print("Line: ");
  Serial.print(line[0]);
  Serial.print(" ");
  Serial.print(line[1]);
  Serial.print(" ");
  Serial.print(line[2]);
  Serial.print(" ");
  Serial.print(line[3]);
  Serial.print(" ");
  Serial.print(line[4]);
  Serial.print(" Flame: ");
  Serial.print(flame[0]);
  Serial.print(" ");
  Serial.print(flame[1]);
  Serial.print(" ");
  Serial.print(flame[2]);
  Serial.print(" ");
  Serial.print(flame[3]);
  Serial.print(" ");
  Serial.print(flame[4]);
  Serial.print(" Distance: ");
  Serial.print(USdis[0]);
  Serial.print(" ");
  Serial.print(USdis[1]);
  Serial.print(" ");
  Serial.print(USdis[2]);
  Serial.print(" ");
  Serial.print(USdis[3]);
  Serial.print(" Bumper: ");
  Serial.print(bmp[0]);
  Serial.print(" ");
  Serial.print(bmp[1]);
  Serial.print(" ");
  Serial.println();
}

