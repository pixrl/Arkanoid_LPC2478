#ifndef BALL_H
#define BALL_H

#include <assert.h>
#include "general.h"
#include "symbols.h"
#include "point.h"
#include "direction.h"

struct m_game;

typedef struct m_game Game;

struct m_ball;

typedef struct m_ball Ball;

typedef void (*setBallCenterFunc)(Ball* ball, Point m_center);
typedef void (*setBallRadiusFunc)(Ball* ball, tU16 m_radius);
typedef void (*setBallColorFunc)(Ball* ball, tU16 m_color);
typedef void (*setBallDirectionFunc)(Ball* ball, Direction m_direction);
typedef Point (*getBallCenterFunc)(Ball* ball);
typedef tU16 (*getBallRadiusFunc)(Ball* ball);
typedef tU16 (*getBallColorFunc)(Ball* ball);
typedef Direction (*getBallDirectionFunc)(Ball * ball);
typedef typeID (*getBallIdFunc)(Ball *ball);
typedef void (*moveBallUpRightFunc)(Ball* ball);
typedef void (*moveBallUpLeftFunc)(Ball* ball);
typedef void (*moveBallDownRightFunc)(Ball* ball);
typedef void (*moveBallDownLeftFunc)(Ball* ball);
typedef void (*moveBallFunc)(Ball* ball);

struct m_ball {
	setBallCenterFunc setCenter;
    setBallRadiusFunc setRadius;
    setBallColorFunc setColor;
    setBallDirectionFunc setDirection;
    getBallCenterFunc getCenter;
    getBallRadiusFunc getRadius;
    getBallColorFunc getColor;
    getBallDirectionFunc getDirection;
    getBallIdFunc getId;
    moveBallUpRightFunc moveUpRight;
    moveBallUpLeftFunc moveUpLeft;
    moveBallDownRightFunc moveDownRight;
    moveBallDownLeftFunc moveDownLeft;
    moveBallFunc moveBall;
    Point           center;
    tU16            radius;
    tU16            color;
    Direction   direction;
    typeID    id;
    Game* gamePtr;
};

Ball* newBall(Point m_center, tU16 m_radius, tU16 m_color, Direction m_direction, Game* m_gamePtr);
void deleteBall(Ball *ball);
void setBallCenter(Ball* ball, Point m_center);
void setBallRadius(Ball* ball, tU16 m_radius);
void setBallColor(Ball* ball, tU16 m_color);
void setBallDirection(Ball* ball, Direction m_direction);
Point getBallCenter(Ball* ball);
tU16 getBallRadius(Ball* ball);
tU16 getBallColor(Ball* ball);
Direction getBallDirection(Ball* ball);
typeID getBallId(Ball* ball);
void moveBallUpRight(Ball* ball);
void moveBallUpLeft(Ball* ball);
void moveBallDownRight(Ball* ball);
void moveBallDownLeft(Ball* ball);
void moveBallOnce(Ball* ball);

#endif
