#ifndef RACKET_H
#define RACKET_H

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "point.h"
#include "general.h"

struct m_game;

typedef struct m_game Game;

struct m_racket;

typedef struct m_racket Racket;

typedef void (*setRacketUpperRightFunc)(Racket* racket, Point m_upperRight);
typedef void (*setRacketLowerLeftFunc)(Racket* racket, Point m_upperRight);
typedef void (*setRacketColorFunc)(Racket* racket, tU16 m_color);
typedef Point (*getRacketUpperRightFunc)(Racket* racket);
typedef Point (*getRacketLowerLeftFunc)(Racket* racket);
typedef tU16 (*getRacketColorFunc)(Racket* racket);
typedef typeID (*getRacketIdFunc)(Racket* racket);
typedef tU16 (*getRacketWidthFunc)(Racket* racket);
typedef tU16 (*getRacketHeightFunc)(Racket* racket);
typedef tU16 (*getRacketSizeFunc)(Racket* racket);
typedef void (*moveRacketRightFunc)(Racket* racket);
typedef void (*moveRacketLeftFunc)(Racket* racket);

struct m_racket{
    setRacketUpperRightFunc setUpperRight;
    setRacketLowerLeftFunc setLowerLeft;
    setRacketColorFunc setColor;
    getRacketUpperRightFunc getUpperRight;
    getRacketLowerLeftFunc getLowerLeft;
    getRacketColorFunc getColor;
    getRacketIdFunc getId;
    getRacketWidthFunc getWidth;
    getRacketHeightFunc getHeight;
    getRacketSizeFunc getSize;
    moveRacketLeftFunc moveLeft;
    moveRacketRightFunc moveRight;
    Point upperRight;
    Point lowerLeft;
    tU16 color;
    typeID id;
    Game* gamePtr;
};
Racket* newRacket(Point m_upperRight, Point m_lowerLeft, tU16 m_color, Game* m_gamePtr);
Racket* newRacketCenter(Point m_lowCenter, tU16 m_length, tU16 m_color, Game* m_gamePtr);
void deleteRacket(Racket* racket);
void setRacketUpperRight(Racket* racket, Point m_upperRight);
void setRacketLowerLeft(Racket* racket, Point m_lowerLeft);
void setRacketColor(Racket* racket, tU16 m_color);
Point getRacketUpperRight(Racket* racket);
Point getRacketLowerLeft(Racket* racket);
tU16 getRacketColor(Racket* racket);
typeID getRacketId(Racket* racket);
tU16 getRacketWidth(Racket* racket);
tU16 getRacketHeight(Racket* racket);
tU16 getRacketSize(Racket* racket);
tU16 isMovePossibleRight(Racket* racket);
tU16 isMovePossibleLeft(Racket* racket);
void moveRacketRight(Racket* racket);
void moveRacketLeft(Racket* racket);

#endif
