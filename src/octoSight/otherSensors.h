//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_OTHERSENSORS_H
#define OCTOSIGHT_OTHERSENSORS_H

#include "arduino.h"

#include "config.h"

extern bool line[];

void initSensors();
void runSensors();
void printSensors();

#endif //OCTOSIGHT_OTHERSENSORS_H
