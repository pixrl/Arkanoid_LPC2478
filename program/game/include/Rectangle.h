#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Symbols.h"
#include "Point.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(const Point& upperRight, const Point& lowerLeft);
    ~Rectangle();
    Rectangle&      setLowerLeft(const Point& lowerLeft);
    Rectangle&      setUpperRight(const Point& upperRight);
    const Point&    getLowerLeft() const;
    const Point&    getUpperRight() const;
protected:
    Point       upperRight;
    Point       lowerLeft;
};

#endif // RECTANGLE_H