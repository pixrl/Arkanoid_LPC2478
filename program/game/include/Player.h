#ifndef PLAYER_H
#define PLAYER_H

#include "Symbols.h"
#include "function.h"
class Player
{
public:
    Player();
    Player(const char* name);
    ~Player();
    Player& setName(const char* name);
    Player& setScore(const tU16& score);
    const char* getName() const;
    const tU16& getScore() const;
private:
    tU16    score;
    char    name[MAX_NAME_LENGTH];
};

#endif // PLAYER_H
