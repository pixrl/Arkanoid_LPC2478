#include "Block.h"
#include "GameManager.h"

Block::Block() : Rectangle(), id(ID_BLOCK){
    this->color = BLACK;
}
Block::Block(const Point& upperRight, const Point& lowerLeft, const tU16& color) : Rectangle(upperRight, lowerLeft), id(ID_BLOCK){
    this->color = color;
    this->gameManagerPtr = nullptr;
}
Block::~Block(){
}
Block& Block::setColor(const tU16& color){
    this->color = color; 
    return *this;
}
const tU16& Block::getColor() const{
    return color;
}
const ElementID& Block::getId() const{
    return id;
}