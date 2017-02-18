//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_OTHERSENSORS_H
#define OCTOSIGHT_OTHERSENSORS_H

#include "arduino.h"

#include "config.h"

#include "otherSensors.h"
#include "ultraSensors.h"
#include "states.h"

extern bool line[];
extern bool flame[];

void initSensors();
void runSensors();
void printSensors();

#endif //OCTOSIGHT_OTHERSENSORS_H
