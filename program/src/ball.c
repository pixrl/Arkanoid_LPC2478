#include "ball.h"

Ball* newBall(Point m_center, tU16 m_radius, tU16 m_color, Direction m_customDirection, Game* m_gamePtr){
    Ball *ball = (Ball*)malloc(sizeof(struct m_ball));
    ball->setCenter = setBallCenter;
    ball->setRadius = setBallRadius;
    ball->setColor = setBallColor;
    ball->setDirection = setBallDirection;
    ball->getCenter = getBallCenter;
    ball->getDirection = getBallDirection;
    ball->getColor = getBallColor;
    ball->getRadius = getBallRadius;
    ball->getId = getBallId;
    ball->moveUpRight = moveBallUpRight;
    ball->moveUpLeft = moveBallUpLeft;
    ball->moveDownRight = moveBallDownRight;
    ball->moveDownLeft = moveBallDownLeft;
    ball->moveBall = moveBallOnce;
    ball->center = m_center;
    ball->color = m_color;
    ball->direction = m_customDirection;
    ball->radius = m_radius;
    ball->id = ID_BALL;
    ball->gamePtr = m_gamePtr;
    return ball;
}
void deleteBall(Ball *ball){
    free(ball);
}
void setBallCenter(Ball* ball, Point m_center){
    ball->center = m_center;
}
void setBallRadius(Ball* ball, tU16 m_radius){
    ball->radius = m_radius;
}
void setBallColor(Ball* ball, tU16 m_color){
    ball->color = m_color;
}
void setBallDirection(Ball* ball, Direction m_direction){
    ball->direction = m_direction;
}
Point getBallCenter(Ball* ball){
    return ball->center;
}
tU16 getBallRadius(Ball* ball){
    return ball->radius;
}
tU16 getBallColor(Ball* ball){
    return ball->color;
}
Direction getBallDirection(Ball* ball){
    return ball->direction;
}
typeID getBallId(Ball* ball){
    return ball->id;
}
void moveBallUpRight(Ball* ball){
    ball->center.x += 1;
    ball->center.y += 1;
}
void moveBallUpLeft(Ball* ball){
    ball->center.x -= 1;
    ball->center.y += 1;
}
void moveBallDownRight(Ball* ball){
    ball->center.x += 1;
    ball->center.y -= 1;
}
void moveBallDownLeft(Ball* ball){
    ball->center.x -= 1;
    ball->center.y -= 1;
}
void moveBallOnce(Ball* ball){
    ball->center.x += ball->direction.x;
    ball->center.y += ball->direction.y;
}