#ifndef FIGHTERS_THOMAS_H
#define FIGHTERS_THOMAS_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Guillaume: public FighterBot {
public:
    Guillaume();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_THOMAS_H
