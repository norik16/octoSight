//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_CONFIG_H
#define OCTOSIGHT_CONFIG_H

//#include "Arduino.h"

//constants
const float stepsPerCm = 27;
const int d = 18.5; //wheel to wheel
const float angleConst = 0.55; //turning constant
const int pi = 3.141592;

const int mDelay = 700;
const long int lineBaseDelay = 500;

//TODO: constant to try
const float wheelRatio = 1.2;


const float leftSpeedMod = 1;
const float timeMod = 8000;
const int speedMod = 255;

const int flameLimit[5] = {700, 500, 800, 650, 650}; //0(FIRE)-1024(DARKNESSS)

#define wallLimit 50

//line detection config
#define lineMedian 9 //number of last values to make median of
const int lineAvgLng = lineMedian; //number of last values to make average of
const int whiteThreshold = 80; //the lower, the whiter
const int blackThreshold[5] = {200, 200, 200, 200, 200}; //the higher, the darker
const int blackWhiteDiff = 150; //the higher, the darker


//ultra sound config
#define UStocm 57
#define USwaitlow 50000 //micros to wait for echo
#define USwaithigh 500000 //micros to wait for echo
#define USmedian 9 //number of last values to make median of


//states
#define FINDCANDLE 1
#define METWALL 2
#define METLINE 3
#define GOALONGLINE 4
#define SOLVECANDLE 5
#define GOAHEAD 6
#define KILL 7
#define ADJUSTCANDLE 8
#define GOBACK 9
#define METWALLSOLVE 10

//output

//steppers
#define leftDirPin 52
#define leftStepPin 53
#define rightDirPin 50
#define rightStepPin 51

//normal motors
#define leftPower 10
#define rightPower 11
#define leftDir 9
#define rightDir 13

//fan
#define fanPin 8

//input analog

//IR candle from right to left
#define IR0Pin A4
#define IR1Pin A2
#define IR2Pin A3
#define IR3Pin A6
#define IR4Pin A0

//input digital

//ultra sound from right to left
#define US0inPin 19
#define US0outPin 14
#define US1inPin 20
#define US1outPin 15
#define US2inPin 18
#define US2outPin 16
#define US3inPin 3
#define US3outPin 17

//IR line from right to left
#define line0Pin A14
#define line1Pin A15
#define line2Pin A13
#define line3Pin A8
#define line4Pin A11

//bumper from right to left
#define bmp0Pin 41
#define bmp1Pin 40

//switch
#define powerPin 1

#endif //OCTOSIGHT_CONFIG_H
