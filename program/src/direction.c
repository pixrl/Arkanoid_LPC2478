#include "direction.h"

Direction* newDirection(tS16 m_x, tS16 m_y){
    assert(m_x == 1 || m_x == -1);
    assert(m_y == 1 || m_y == -1);
    Direction* direction = (Direction*)malloc(sizeof(struct m_direction));
    direction->set_x = setDirection_x;
    direction->set_y = setDirection_y;
    direction->get_x = getDirection_x;
    direction->get_y = getDirection_y;
    direction->x = m_x;
    direction->y = m_y;
    return direction;
}
void deleteDirection(Direction* direction){
    free(direction);
}
void setDirection_x(Direction* direction){
    direction->x *= -1;
}
void setDirection_y(Direction* direction){
    direction->y *= -1;
}
tS16 getDirection_x(Direction* direction){
    return direction->x;
}
tS16 getDirection_y(Direction* direction){
    return direction->y;
}