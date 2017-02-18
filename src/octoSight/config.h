//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_CONFIG_H
#define OCTOSIGHT_CONFIG_H


//output

//constants
const int stepsPerCm = 30;
const int d = 30; //wheel to wheel
const int pi = 3.141592;
const int mDelay = 500;

//wheels
#define leftDir 1
#define leftStep 1
#define rightDir 1
#define rightStep 1

//fan
#define fan 1


//input analog

//IR candle from right to left
#define IR0 1
#define IR1 1
#define IR2 1


//input digital

//ultra sound from
#define US0in 1
#define US0out 1
#define US1in 1
#define US1out 1

//IR line from right to left
#define lineSensor0 0
#define lineSensor1 1
#define lineSensor2 2
#define lineSensor3 3
#define lineSensor4 4

//bumper from right to left
#define bmp0 1
#define bmp1 1

//switch
#define power 1

#endif //OCTOSIGHT_CONFIG_H
