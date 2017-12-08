#ifndef DIRECTION_H
#define DIRECTION_H

#include <assert.h>
#include <stdlib.h>
#include "general.h"
#include "symbols.h"

struct m_direction;

typedef struct m_direction Direction;

typedef void (*setDirection_xFunc)(Direction* direction);
typedef void (*setDirection_yFunc)(Direction* direction);
typedef tS16 (*getDirection_xFunc)(Direction* direction);
typedef tS16 (*getDirection_yFunc)(Direction* direction);

struct m_direction{
    setDirection_xFunc set_x;
    setDirection_yFunc set_y;
    getDirection_xFunc get_x;
    getDirection_yFunc get_y;
    tS16 x;
    tS16 y;
};

Direction* newDirection(tS16 m_x, tS16 m_y);
void deleteDirection(Direction* direction);
void setDirection_x(Direction* direction);
void setDirection_y(Direction* direction);
tS16 getDirection_x(Direction* direction);
tS16 getDirection_y(Direction* direction);

#endif
