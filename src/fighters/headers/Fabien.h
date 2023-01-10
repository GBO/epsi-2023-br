#ifndef FIGHTERS_FABIEN_H
#define FIGHTERS_FABIEN_H

#include <iostream>
#include "FighterBot.h"

using namespace std;

class Fabien: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena, Fighter mate);
    Fighter selectMate(Arena arena);

public:
    Fabien();
    virtual Action* choose(Arena arena);
};
#endif