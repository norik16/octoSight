//
// Created by ronald on 18.2.17.
//

#ifndef MAIN_STATES_H
#define MAIN_STATES_H


#include "states.h"
#include "octoSight.h"
#include "helperFunctions.h"
#include "otherSensors.h"
#include "ultraSensors.h"
#include "config.h"

int terminate();

int goAlongLine();
int goAhead();
int metLine();
int metWall();
int metWallSolve();

int findCandle();
int solveCandle();
int adjustCandle();
int kill();
int goBack();



#endif //MAIN_STATES_H
