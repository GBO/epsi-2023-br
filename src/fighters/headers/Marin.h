#ifndef FIGHTERS_MARIN_H
#define FIGHTERS_MARIN_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Marin: public FighterBot {
public:
    // GBO Correction
    Marin();

    // GBO Correction
    // string targeID();

    // GBO Correction
    // Fighter selectTarget(Arena arena);
    Action* selectTarget(Arena arena);
    // GBO Correction
    virtual Action* choose(Arena arena) {}
};

#endif //FIGHTERS_MARIN_H
