//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_UTRASENSORS_H
#define OCTOSIGHT_UTRASENSORS_H

#include "arduino.h"

#include "config.h"

extern int US1dis;
extern int US2dis;

void initUltra();
void US1high();
void US1low();
void US2high();
void US2low();

#endif //OCTOSIGHT_UTRASENSORS_H
