//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_MAIN_HH_H
#define OCTOSIGHT_MAIN_HH_H

#include "config.h"
#include "otherSensors.h"
#include "ultraSensors.h"
#include "states.h"

//l in cm (possitive forward), angle in degrees (mathematical direction)
void go(int l, int angle);

//go straight
void go(int l);


#endif //OCTOSIGHT_MAIN_HH_H
