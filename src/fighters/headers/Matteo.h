#ifndef FIGHTERS_MATTEO_H
#define FIGHTERS_MATTEO_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Matteo: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Matteo();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_MATTEO_H
