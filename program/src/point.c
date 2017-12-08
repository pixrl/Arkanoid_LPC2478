#include "point.h"
Point* newPoint(tU16 m_x, tU16 m_y){
    Point* point = (Point*)malloc(sizeof(struct m_point));
    point->set_x = setPoint_x;
    point->set_y = setPoint_y;
    point->get_x = getPoint_x;
    point->get_y = getPoint_y;
    point->x = m_x;
    point->y = m_y;
    return point;
}
void deletePoint(Point *point){
    free(point);
}
void setPoint_x(Point* point, tU16 m_x){
    point->x = m_x;
}
void setPoint_y(Point* point, tU16 m_y){
    point->y = m_y;
}
tU16 getPoint_x(Point* point){
    return point->x;
}
tU16 getPoint_y(Point* point){
    return point->y;
}