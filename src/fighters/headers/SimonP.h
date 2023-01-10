#ifndef FIGHTERS_SIMON_H
#define FIGHTERS_SIMON_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class SimonP: public FighterBot {
private:
    string targetId;
    bool regroupSet;
    int XAverage;
    int YAverage;

    Fighter selectTarget(Arena arena);

    void setRegroup(Arena arena);

public:
    SimonP();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_SIMON_H
