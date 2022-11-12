#ifndef FIGHTERS_GHISLAIN_H
#define FIGHTERS_GHISLAIN_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Ghislain: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Ghislain();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GHISLAIN_H
