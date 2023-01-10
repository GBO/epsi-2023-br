#ifndef FIGHTERS_JQ_H
#define FIGHTERS_JQ_H

#include <iostream>
#include "FighterBot.h"

using namespace std;

class Jq: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena, Fighter mate);
    Fighter selectMate(Arena arena);

public:
    Jq();
    virtual Action* choose(Arena arena);
};
#endif