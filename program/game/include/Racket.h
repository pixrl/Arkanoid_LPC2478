#ifndef RACKET_H
#define RACKET_H

#include "Symbols.h"
#include "Point.h"
#include "Rectangle.h"
class GameManager;

class Racket : public Rectangle
{
public:
    Racket();
    Racket(const Point& upperRight, const Point& lowerLeft, const tU16& color);
    Racket(const tU16& length_x, const tU16& length_y, const tU16& color, GameManager* gameManagerPtr);
    ~Racket();
    Racket&             setColor(const tU16& color);
    const tU16&         getColor() const;
    const ElementID&    getId() const;
    void                moveRight();
    void                moveLeft();
    Racket&             setLength_x(const tU16& length_x);
    Racket&             setLength_y(const tU16& length_y);
    const tU16&         getLength_x() const;
    const tU16&         getLength_y() const;
private:
    GameManager*    gameManagerPtr;
    tU16            color;
    tU16            length_x;
    tU16            length_y;
    const ElementID id;
};

#endif // RACKET_H
