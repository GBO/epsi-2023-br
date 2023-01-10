// GBO Correction
// #ifndef FIGHTERS_GHISLAIN_H
// #define FIGHTERS_GHISLAIN_H
#ifndef FIGHTERS_JOJO_H
#define FIGHTERS_JOJO_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class JoJo: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    JoJo();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_JOJO_H
