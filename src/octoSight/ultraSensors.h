//
// Created by ronald on 17.2.17.
//

#ifndef OCTOSIGHT_UTRASENSORS_H
#define OCTOSIGHT_UTRASENSORS_H

#include "Arduino.h"

#include "config.h"

extern int USdis[4];

void initUltra();
void US0high();
void US0low();
void US1high();
void US1low();
void US2high();
void US2low();
void US3high();
void US3low();

#endif //OCTOSIGHT_UTRASENSORS_H
