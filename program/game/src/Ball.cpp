#include "Ball.h"
#include "GameManager.h"
#include "Racket.h"

Ball::Ball() : Circle(), id(ID_BALL){
    this->direction = UP_LEFT;
    this->color = BLACK;
}
Ball::Ball(const tU16& radius, const tU16& color, GameManager* m_gameManagerPtr, Racket* racketPtr)
    : Circle(Point(m_gameManagerPtr->getWidth(), m_gameManagerPtr->getDistanceFromTheBottomEdge() + racketPtr->getLength_y() + radius), radius)
    , id(ID_BALL){
    this->direction = UP_LEFT;      // ewentualnie potem zrobić randomowo
    this->color = color;
    this->gameManagerPtr = m_gameManagerPtr;
    this->racketPtr = racketPtr;
}
Ball::Ball(const Point& center, const tU16& radius, const ballDirection& direction, const tU16& color) 
    : Circle(center, radius)
    , id(ID_BALL){
    this->direction = direction;
    this->color = color;
    this->gameManagerPtr = nullptr;
    this->racketPtr = nullptr;
}
Ball::~Ball(){
}
Ball& Ball::setColor(const tU16& color){
    this->color = color;
    return *this;
}
Ball& Ball::setDirection(const ballDirection& direction){
    this->direction = direction;
    return *this;
}
const tU16& Ball::getColor() const{
    return color;
}
const ballDirection& Ball::getDirection() const{
    return direction;
}
const ElementID& Ball::getId() const{
    return id;
}
void Ball::moveUpRight(){
    this->center.setX(this->center.getX() + 1);
    this->center.setY(this->center.getY() + 1);
}
void Ball::moveUpLeft(){
    this->center.setX(this->center.getX() - 1);
    this->center.setY(this->center.getY() + 1);
}
void Ball::moveDownRight(){
    this->center.setX(this->center.getX() + 1);
    this->center.setY(this->center.getY() - 1);
}
void Ball::moveDownLeft(){
    this->center.setX(this->center.getX() - 1);
    this->center.setY(this->center.getY() - 1);
}