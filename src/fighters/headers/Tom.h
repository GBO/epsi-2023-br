#ifndef FIGHTERS_TOM_H
#define FIGHTERS_TOM_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Tom: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena, Fighter leader);
    Fighter selectTargetLeader(Arena arena);

public:
    Tom();

    virtual Action* choose(Arena arena);

    Fighter leaderExist(Arena arena);
};

#endif //FIGHTERS_TOM_H
