//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_CONFIG_H
#define OCTOSIGHT_CONFIG_H



//constants
const float stepsPerCm = 6.4;
const int d = 18.5; //wheel to wheel
const int angleConst = 30; //turning constant
const int pi = 3.141592;

const int mDelay = 3000;
const int lineBaseDelay = 100000;

//TODO: constant to try
const float wheelRatiox = 1.2;

const int flameLimit = 800; //0(FIRE)-1024(DARKNESSS)

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
#define line0Pin A15
#define line1Pin A14
#define line2Pin A13
#define line3Pin A12
#define line4Pin A11

//bumper from right to left
#define bmp0Pin 41
#define bmp1Pin 40

//switch
#define powerPin 1

//ultra sound config
#define UStocm 57
#define USwait 5800 //micros to wait for echo
#define USmedian 3 //nomber of last values to make median of

#endif //OCTOSIGHT_CONFIG_H
