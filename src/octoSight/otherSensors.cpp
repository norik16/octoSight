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
  /*Serial.print("Line: ");
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
  Serial.print(flame[4]);*/
  Serial.print(" Distance:\t");
  Serial.print(USdis[0]);
  Serial.print("\t");
  Serial.print(USdis[1]);
  Serial.print("\t");
  Serial.print(USdis[2]);
  Serial.print("\t");
  Serial.print(USdis[3]);
  Serial.print(" UStime:\t");
  Serial.print(UStime[0]);
  Serial.print("\t");
  Serial.print(UStime[1]);
  Serial.print("\t");
  Serial.print(UStime[2]);
  Serial.print("\t");
  Serial.print(UStime[3]);
  Serial.print("\tBumper: ");
  Serial.print(bmp[0]);
  Serial.print(" ");
  Serial.print(bmp[1]);
  Serial.print(" ");
  Serial.print(" US: ");
  Serial.print(US[0]);
  Serial.print(" ");
  Serial.print(US[1]);
  Serial.print(" ");
  Serial.print(US[2]);
  Serial.print(" ");
  Serial.print(US[3]);
  Serial.print(" ");
  Serial.print(US[4]);
  Serial.print(" ");
  Serial.print(US[5]);
  Serial.print(" ");
  Serial.print(US[6]);
  Serial.print(" ");
  Serial.print(US[7]);
  Serial.print(" ");
  Serial.print(digitalRead(US0inPin));
  Serial.print(" ");
  Serial.print(digitalRead(US1inPin));
  Serial.print(" ");
  Serial.print(digitalRead(US2inPin));
  Serial.print(" ");
  Serial.print(digitalRead(US3inPin));
  Serial.println();
}

