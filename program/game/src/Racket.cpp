#include "Racket.h"
#include "GameManager.h"
Racket::Racket() : Rectangle(), id(ID_RACKET){
    this->color = BLACK;
}
Racket::Racket(const Point& upperRight, const Point& lowerLeft, const tU16& color) 
    : Rectangle(upperRight, lowerLeft)
    , id(ID_RACKET){
    this->upperRight    = upperRight;
    this->lowerLeft     = lowerLeft;
    this->length_x      = upperRight.getX() - lowerLeft.getX();
    this->length_y      = upperRight.getY() - lowerLeft.getY();
    this->color         = color;
    this->gameManagerPtr = nullptr;
}
Racket::Racket(const tU16& length_x, const tU16& length_y, const tU16& color, GameManager* m_gameManagerPtr) 
    : Rectangle(Point(m_gameManagerPtr->getWidth()/2 + length_x/2, m_gameManagerPtr->getDistanceFromTheBottomEdge() + length_y), 
                Point(m_gameManagerPtr->getWidth()/2 - length_x/2, m_gameManagerPtr->getDistanceFromTheBottomEdge()))
    , id(ID_RACKET){
    this->length_x = length_x;
    this->length_y = length_y;
    this->color = color;
    this->gameManagerPtr = m_gameManagerPtr;
}
Racket::~Racket(){
}
Racket&             Racket::setColor(const tU16& color){
    this->color = color; 
    return *this;
}
const tU16&         Racket::getColor() const{
    return this->color;
}
const ElementID&    Racket::getId() const{
    return this->id;
}
void                Racket::moveRight(){
    this->upperRight.setX(this->upperRight.getX() + 1);
    this->lowerLeft.setX(this->lowerLeft.getX() + 1);
}
void                Racket::moveLeft(){
    this->upperRight.setX(this->upperRight.getX() - 1);
    this->lowerLeft.setX(this->lowerLeft.getX() - 1);
}
Racket&             Racket::setLength_x(const tU16& length_x){
    this->length_x = length_x; 
    return *this;
}
Racket&             Racket::setLength_y(const tU16& length_y){
    this->length_y = length_y; 
    return *this;
    }
const tU16&         Racket::getLength_x() const{
    return length_x;
}
const tU16&         Racket::getLength_y() const{
    return length_y;
}