#ifndef BALL_H
#define BALL_H

#include "Symbols.h"
#include "Point.h"
#include "Circle.h"

class GameManager;

class Racket;

enum ballDirection{
    UP_RIGHT,
    UP_LEFT,
    DOWN_LEFT,
    DOWN_RIGHT
};

class Ball : public Circle
{
public:
    Ball();
    Ball(const tU16& radius, const tU16& color, GameManager* m_gameManagerPtr, Racket* racketPtr);
    Ball(const Point& center, const tU16& radius, const ballDirection& direction, const tU16& color);
    ~Ball();
    Point                   center;
    Ball&                   setColor(const tU16& color);
    Ball&                   setDirection(const ballDirection& direction);
    const tU16&             getColor() const;
    const ballDirection&    getDirection() const;
    const ElementID&        getId() const;
    void                    moveUpRight();
    void                    moveUpLeft();
    void                    moveDownRight();
    void                    moveDownLeft();
private:
    GameManager*    gameManagerPtr;
    Racket*         racketPtr;
    tU16            color;
    ballDirection       direction;
    const ElementID id;
};

#endif // BALL_H
