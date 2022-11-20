#ifndef FIGHTERS_DUMB_H
#define FIGHTERS_DUMB_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Dumb: public FighterBot {
public:
    Dumb();
    Dumb(string prenom);

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_DUMB_H
