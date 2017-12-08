#ifndef POINT_H
#define POINT_H

#include "symbols.h"
#include "general.h"
#include <stdlib.h>

struct m_point;

typedef struct m_point Point;

typedef void (*setPoint_xFunc)(Point* point, tU16 m_x);
typedef void (*setPoint_yFunc)(Point* point, tU16 m_y);
typedef tU16 (*getPoint_xFunc)(Point* point);
typedef tU16 (*getPoint_yFunc)(Point* point);

struct m_point {
    setPoint_xFunc set_x;
    setPoint_yFunc set_y;
    getPoint_xFunc get_x;
    getPoint_yFunc get_y;
	tU16		x;
	tU16		y;
};

Point* newPoint(tU16 m_x, tU16 m_y);
void deletePoint(Point *point);
void setPoint_x(Point* point, tU16 m_x);
void setPoint_y(Point* point, tU16 m_y);
tU16 getPoint_x(Point* point);
tU16 getPoint_y(Point* point);
#endif
