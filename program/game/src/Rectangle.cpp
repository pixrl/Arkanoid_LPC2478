#include "Rectangle.h"

Rectangle::Rectangle(){
    this->upperRight    = Point(2, 2);
    this->lowerLeft     = Point(0, 0);
}
Rectangle::Rectangle(const Point& upperRight, const Point& lowerLeft){
    this->upperRight    = upperRight;
    this->lowerLeft     = lowerLeft;
}
Rectangle::~Rectangle(){
}
Rectangle& Rectangle::setLowerLeft(const Point& lowerLeft){
    this->lowerLeft = lowerLeft; 
    return *this;
}
Rectangle& Rectangle::setUpperRight(const Point& upperRight){
    this->upperRight = upperRight; 
    return *this;
}
const Point& Rectangle::getLowerLeft() const{
    return lowerLeft;
}
const Point& Rectangle::getUpperRight() const{
    return upperRight;
}