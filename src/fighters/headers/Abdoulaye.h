#ifndef FIGHTERS_ABDOULAYE_H
#define FIGHTERS_ABDOULAYE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Abdoulaye: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Abdoulaye();

    virtual Action* choose(Arena arena);

    virtual Action* allie(Arena arena) {}


};

#endif //FIGHTERS_GHISLAIN_H
