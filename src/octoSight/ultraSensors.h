//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_UTRASENSORS_H
#define OCTOSIGHT_UTRASENSORS_H

#include "arduino.h"

#include "config.h"

extern int US0dis;
extern int US1dis;

void initUltra();
void US0high();
void US0low();
void US1high();
void US1low();

#endif //OCTOSIGHT_UTRASENSORS_H
