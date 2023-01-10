#ifndef FIGHTERS_QUENTIN_H
#define FIGHTERS_QUENTIN_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Quentin: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

    bool changeStatsHere = true;
    bool changeStatsThere = true;

public:
    Quentin();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_Quentin_H
