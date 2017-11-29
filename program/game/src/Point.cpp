#include "Point.h"

Point::Point(){
    this->x = 0;
    this->y = 0;
}
Point::Point(const tU16& x, const tU16& y){
    this->x = x;
    this->y = y;
}
Point::~Point(){
}
Point& Point::setX(const tU16& x) {
    this->x = x;
    return *this;
}
Point& Point::setY(const tU16& y) {
    this->y = y;
    return *this;
}
const tU16& Point::getX() const {
    return x;
}
const tU16& Point::getY() const {
    return y;
}
bool operator== (const Point &point1, const Point &point2){
    return (point1.x == point2.x && 
            point2.y == point2.y);
}
bool operator!= (const Point &point1, const Point &point2){
    return !(point1 == point2);
}
std::ostream& operator<< (std::ostream &out, const Point &point){
    out << "Point(" << point.x << ", " << point.y << ", "<< ")";
    return out;
}