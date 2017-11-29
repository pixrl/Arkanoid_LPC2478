#include "Circle.h"

Circle::Circle(){
    this->center = Point(0, 0);
    this->radius = 10;
}
Circle::Circle(const Point& center, const tU16& radius){
    this->center = center;
    this->radius = radius;
}
Circle::~Circle(){
}
Circle& Circle::setCenter(const Point& center){
    this->center = center; 
    return *this;
}
const Point& Circle::getCenter() const{
    return center;
}
Circle& Circle::setRadius(const tU16& radius){
    this->radius = radius; 
    return *this;
}
const tU16& Circle::getRadius() const{
    return radius;
}