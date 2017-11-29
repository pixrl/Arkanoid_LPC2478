#ifndef BLOCK_H
#define BLOCK_H

#include "Symbols.h"
#include "Point.h"
#include "Rectangle.h"

class GameManager;

class Block : public Rectangle
{
public:
    Block();
    Block(const Point& upperRight, const Point& lowerLeft, const tU16& color);
    ~Block();
    Block& setColor(const tU16& color);
    const tU16& getColor() const;
    const ElementID& getId() const;
private:
    tU16                color;
    const ElementID     id;
    GameManager*        gameManagerPtr;
};

#endif // BLOCK_H
