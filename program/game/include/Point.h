#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "Symbols.h"

class Point
{
public:
    Point();
    Point(const tU16& x, const tU16& y);
    ~Point();
    Point& setX(const tU16& x);
    Point& setY(const tU16& y);
    const tU16& getX() const;
    const tU16& getY() const;
    friend bool operator== (const Point &p1, const Point &p2);
    friend bool operator!= (const Point &p1, const Point &p2);
    friend std::ostream& operator<< (std::ostream &out, const Point &point);
private:
    tU16    x;
    tU16    y;
};

#endif // POINT_H
