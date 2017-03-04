//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_CONFIG_H
#define OCTOSIGHT_CONFIG_H

//#include "Arduino.h"

//constants
const float stepsPerCm = 6.4;
const int d = 18.5; //wheel to wheel
const int angleConst = 30; //turning constant
const int pi = 3.141592;

const int mDelay = 3000;
const long int lineBaseDelay = 100000;

//TODO: constant to try
const float wheelRatio = 1.2;

const int flameLimit = 800; //0(FIRE)-1024(DARKNESSS)

//line detection config
const int lineAvgLng = 6; //number of last values to make average of
const int whiteThreshold = 100; //the lower, the whiter
const int blackThreshold = 200; //the higher, the darker
#define lineMedian 6 //number of last values to make median of


//ultra sound config
#define UStocm 57
#define USwaitlow 50000 //micros to wait for echo
#define USwaithigh 500000 //micros to wait for echo
#define USmedian 9 //number of last values to make median of


//output

//wheels
#define leftDirPin 52
#define leftStepPin 53
#define rightDirPin 50
#define rightStepPin 51

//fan
#define fanPin 1


//input analog

//IR candle from right to left
#define IR0Pin A4
#define IR1Pin A3
#define IR2Pin A2
#define IR3Pin A1
#define IR4Pin A0


//input digital

//ultra sound from right to left
#define US0inPin 18
#define US0outPin 14
#define US1inPin 19
#define US1outPin 15
#define US2inPin 20
#define US2outPin 16
#define US3inPin 21
#define US3outPin 17

//IR line from right to left
#define line0Pin A12
#define line1Pin A15
#define line2Pin A11
#define line3Pin A10
#define line4Pin A9

//bumper from right to left
#define bmp0Pin 41
#define bmp1Pin 40

//switch
#define powerPin 1

#endif //OCTOSIGHT_CONFIG_H
