//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_CONFIG_H
#define OCTOSIGHT_CONFIG_H



//constants
const int stepsPerCm = 5;
const int d = 30; //wheel to wheel
const int pi = 3.141592;

const int mDelay = 2000;
const int lineBaseDelay = 100000;


//output

//wheels
#define leftDirPin 50
#define leftStepPin 51
#define rightDirPin 52
#define rightStepPin 53

//fan
#define fanPin 1


//input analog

//IR candle from right to left
#define IR0Pin 1
#define IR1Pin 1
#define IR2Pin 1
#define IR3Pin 1
#define IR4Pin 1


//input digital

//ultra sound from
#define US0inPin 1
#define US0outPin 1
#define US1inPin 1
#define US1outPin 1

//IR line from right to left
#define line0Pin 1
#define line1Pin 1
#define line2Pin 1
#define line3Pin 1
#define line4Pin 1

//bumper from right to left
#define bmp0Pin 1
#define bmp1Pin 1

//switch
#define powerPin 1

#endif //OCTOSIGHT_CONFIG_H
