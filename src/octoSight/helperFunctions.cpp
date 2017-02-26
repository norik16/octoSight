//
// Created by ronald on 18.2.17.
//

#include "helperFunctions.h"

struct coords {
    int x, y;
};

coords lineC[5] = { //from right to left
        {6, 0},
        {3, 3},
        {0, 6},
        {-3, 3},
        {-6, 0}};

float angleToLine(int a, int b)
{
    float k = (lineC[a].y - lineC[b].y)/(lineC[a].x - lineC[b].x);

    return asin(k/sqrt(pow(k, 2) - pow(lineC[a].x - lineC[b].x, 2)))*180/M_PI;
}

int median(int * field, int len)
{
  int h, x = len/2;
  while(len--)
  {
    for(int j = 0; j < len-1; j++)
    {
      if(field[j] > field[j+1])
      {
        h = field[j];
        field[j] = field[j+1];
        field[j+1] = h;
      }
    }
  }
  return field[x];
}

