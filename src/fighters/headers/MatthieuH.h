#ifndef FIGHTERS_MATTHIEUH_H
#define FIGHTERS_MATTHIEUH_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class MatthieuH: public FighterBot {
private:
    string targetId;

public:
    MatthieuH();

    virtual Action* choose(Arena arena);
};

#endif
