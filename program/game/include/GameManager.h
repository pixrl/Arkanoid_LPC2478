#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Symbols.h"
#include "Ball.h"
#include "Block.h"
#include "Racket.h"
#include "Player.h"

//class Racket;
class Ball;

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void moveBall(ballDirection direction);
    void moveBallCheck(ballDirection direction);
    void moveRacket(racketDirection direction);
    void destroyBlock();
    tU16 getWidth() const;
    tU16 getHeight() const;
    tU16 getDistanceFromTheBottomEdge() const;
private:
    Player  player;
    Ball    ball;
    Racket  racket;
    Block   blocks[NUM_OF_BLOCKS];
    tU16    width;                                  // musi być parzyste
    tU16    height;                                 // musi być parzyste
    tU16    bottom;
    tU16    distanceFromTheBottomEdge;
    tU16    distanceFromTheUpperEdge;
    tU16    distanceFromTheLeftEdge;
    tU16    distanceBetweenBlocks;
    tU16    rightEdge;
    tU16    leftEdge;
    tU16    upperEdge;
};

#endif // GAMEMANAGER_H
