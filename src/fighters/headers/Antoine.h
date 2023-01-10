#ifndef FIGHTERS_ANTOINE_H
#define FIGHTERS_ANTOINE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Antoine: public FighterBot {
private:

    Fighter selectTarget(Arena arena);

public:
    Antoine();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GHISLAIN_H
