#ifndef CIRCLE_H
#define CIRCLE_H

#include "Symbols.h"
#include "Point.h"

class Circle
{
public:
    Circle();
    Circle(const Point& center, const tU16& radius);
    ~Circle();
    Circle& setCenter(const Point& center);
    const Point& getCenter() const;
    Circle& setRadius(const tU16& radius);
    const tU16& getRadius() const;
protected:
    Point       center;
    tU16        radius;
};

#endif // CIRCLE_H
