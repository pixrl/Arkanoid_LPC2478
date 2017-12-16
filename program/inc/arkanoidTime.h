#ifndef ARKANOIDTIME_H
#define ARKANOIDTIME_H

#include "general.h"

void timeWrapping(unsigned long *value, unsigned long wrapValue);
void setHour(volatile unsigned long *rtcValue, tU16 ifIncrease);
void setMinuteOrSecond(volatile unsigned long *rtcValue, tU16 ifIncrease);

#endif
