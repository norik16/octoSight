//
// Created by ronald on 18.2.17.
//

#include "helperFunctions.h"

struct coords {
    int x, y;
};

coords lineC[5] = { //from right to left
        {6,  0},
        {3,  3},
        {0,  6},
        {-3, 3},
        {-6, 0}};

float angleToLine(int a, int b) {
    float k = (lineC[a].y - lineC[b].y) / (lineC[a].x - lineC[b].x);

    return asin(k / sqrt(pow(k, 2) - pow(lineC[a].x - lineC[b].x, 2))) * 180 / M_PI;
}

int median(int *field, int len) {
    int tmpField[USmedian];
    for (int i = 0; i < len; i++) {
        tmpField[i] = field[i];
    }
    
    int h, x = len / 2;

    while (len--) {
        for (int j = 0; j < len; j++) {
            if (tmpField[j] > tmpField[j + 1]) {
                h = tmpField[j];
                tmpField[j] = tmpField[j + 1];
                tmpField[j + 1] = h;
            }
        }
    }

    return tmpField[x];
}