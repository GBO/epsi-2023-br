#ifndef FIGHTERS_VIKO_H
#define FIGHTERS_VIKO_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Viko: public FighterBot {
private:
    string targetId;
    Fighter selectTarget(Arena arena);

public:
    Viko();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_VIKO_H
