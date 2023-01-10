//
// Created by Matthieu Deroir on 16/12/2022.
//

#ifndef FIGHTERS_MAAWOX_H
#define FIGHTERS_MAAWOX_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Maawox: public FighterBot {
private:
    string targetId;
    string gangTargetId;

    Fighter selectTarget(Arena arena);

public:
    Maawox();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_MAAWOX_H

