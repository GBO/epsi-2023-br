// GBO Correction
// #ifndef FIGHTERS_GHISLAIN_H
// #define FIGHTERS_GHISLAIN_H
#ifndef FIGHTERS_ROSALINE_H
#define FIGHTERS_ROSALINE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Rosalyne: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Rosalyne();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_ROSALINE_H
