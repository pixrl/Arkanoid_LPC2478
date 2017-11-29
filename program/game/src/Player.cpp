#include "Player.h"
#include <string.h>
Player::Player(){
    strncpy(this->name, "xyz", MAX_NAME_LENGTH);
    this->score = 0;
}
Player::Player(const char* name){
    strncpy(this->name, name, MAX_NAME_LENGTH);
    this->score = 0;
}
Player::~Player(){
}
Player& Player::setName(const char* name){
    strncpy(this->name, name, MAX_NAME_LENGTH); 
    return *this;
}
Player& Player::setScore(const tU16& score){
    this->score = score; 
    return *this;
}
const char* Player::getName() const{
    return name;
}
const tU16& Player::getScore() const{
    return score;
}