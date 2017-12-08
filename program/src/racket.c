#include "racket.h"
#include "game.h"

Racket* newRacket(Point m_upperRight, Point m_lowerLeft, tU16 m_color, Game* m_gamePtr){
    assert(m_upperRight.x > m_lowerLeft.x && m_upperRight.y > m_lowerLeft.y);
    assert(m_color < 0xFFFF);
    Racket* racket = (Racket*)malloc(sizeof(struct m_racket));
    racket->setUpperRight = setRacketUpperRight;
    racket->setLowerLeft = setRacketLowerLeft;
    racket->setColor = setRacketColor;
    racket->getUpperRight = getRacketUpperRight;
    racket->getLowerLeft = getRacketLowerLeft;
    racket->getColor = getRacketColor;
    racket->getId = getRacketId;
    racket->getWidth = getRacketWidth;
    racket->getHeight = getRacketHeight;
    racket->getSize = getRacketSize;
    racket->moveLeft = moveRacketLeft;
    racket->moveRight = moveRacketRight;
    racket->upperRight = m_upperRight;
    racket->lowerLeft = m_lowerLeft;
    racket->color = m_color;
    racket->id = ID_RACKET;
    racket->gamePtr = m_gamePtr;
    return racket;
}
void deleteRacket(Racket* racket){
    free(racket);
    racket = NULL;
}
void setRacketUpperRight(Racket* racket, Point m_upperRight){
    assert(m_upperRight.x > racket->lowerLeft.x && m_upperRight.y > racket->lowerLeft.y);
    racket->upperRight.x = m_upperRight.x;
    racket->upperRight.y = m_upperRight.y;
}
void setRacketLowerLeft(Racket* racket, Point m_lowerLeft){
    assert(racket->upperRight.x > m_lowerLeft.x && racket->upperRight.y > m_lowerLeft.y);
    racket->lowerLeft.x = m_lowerLeft.x;
    racket->lowerLeft.y = m_lowerLeft.y;
}
void setRacketColor(Racket* racket, tU16 m_color){
    assert(m_color < 0xFFFF);
    racket->color = m_color;
}
Point getRacketUpperRight(Racket* racket){
    return racket->upperRight;
}
Point getRacketLowerLeft(Racket* racket){
    return racket->lowerLeft;
}
tU16 getRacketColor(Racket* racket){
    return racket->color;
}
typeID getRacketId(Racket* racket){
    return racket->id;
}
tU16 getRacketWidth(Racket* racket){
    return (racket->upperRight.x - racket->lowerLeft.x);
}
tU16 getRacketHeight(Racket* racket){
    return (racket->upperRight.y - racket->lowerLeft.y);
}
tU16 getRacketSize(Racket* racket){
    return (racket->getWidth(racket) * racket->getHeight(racket));
}
tU16 isMovePossible(Racket* racket){
    if(racket->gamePtr->getEdge(racket->gamePtr, left) <= racket->getLowerLeft(racket).x 
    && racket->getUpperRight(racket).x <= racket->gamePtr->getEdge(racket->gamePtr, right))
        return 1;
    else
        return 0;
}
void moveRacketRight(Racket* racket){
    if(!isMovePossible(racket))
        return;
    racket->upperRight.x    += 1;
    racket->lowerLeft.x     += 1;
}
void moveRacketLeft(Racket* racket){
    if(!isMovePossible(racket))
        return;
    racket->upperRight.x    -= 1;
    racket->lowerLeft.x     -= 1;
}
