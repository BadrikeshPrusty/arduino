#ifndef MAIN_H
#define MAIN_H

#include "ds1307.h"

#define START 0
#define STOP  1
#define START_STOP_KEY 2

DS1307 ds1307;

char time_str[35];

#endif
