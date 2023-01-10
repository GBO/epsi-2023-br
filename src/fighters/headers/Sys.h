#ifndef FIGHTERS_SYS_H
#define FIGHTERS_SYS_H

#include <iostream>
#include "FighterBot.h"

using namespace std;

class Sys: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);
    Fighter selectMate(Arena arena);

public:
    Sys();
    virtual Action* choose(Arena arena);
};
#endif