//
// Created by ronald on 18.2.17.
//

#ifndef MAIN_STATES_H
#define MAIN_STATES_H


#include "states.h"
#include "octoSight.h"
#include "helperFunctions.h"
#include "otherSensors.h"

extern bool line[];
extern bool flame[];

void goAmongLine();
void metLine();

void findCandle();
void solveCandle();


#endif //MAIN_STATES_H
