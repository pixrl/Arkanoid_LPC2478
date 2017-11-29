#include "GameManager.h"

GameManager::GameManager(){
    this->width   = 240;
    this->height  = 320;
    this->bottom  = 0;
    this->distanceFromTheBottomEdge   = 10;
    this->distanceFromTheUpperEdge    = 6;
    this->distanceFromTheLeftEdge     = 40;
    this->distanceBetweenBlocks       = 2;
    this->rightEdge   = width - 1;
    this->leftEdge    = 12;
    this->upperEdge   = height - 1;
    //this->racket = Racket(width/2 + )
}
GameManager::~GameManager()
{
}
tU16 GameManager::getWidth() const{
    return this->width;
}
tU16 GameManager::getHeight() const{
    return this->height;
}
tU16 GameManager::getDistanceFromTheBottomEdge() const{
    return this->distanceFromTheBottomEdge;
}
void GameManager::moveBall(ballDirection direction){
    moveBallCheck(direction);
    switch(ball.getDirection()){
        case UP_RIGHT:
            ball.moveUpRight();
            break;
        case UP_LEFT:
            ball.moveUpLeft();
            break;
        case DOWN_RIGHT:
            ball.moveDownRight();
            break;
        case DOWN_LEFT:
            ball.moveDownLeft();
            break;
    }
}
void GameManager::moveBallCheck(ballDirection direction){
    //switch(inputGame->ball.direction)
}
void moveRacket();
void destroyBlock();