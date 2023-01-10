#ifndef FIGHTERS_SAY_O_LIT_H
#define FIGHTERS_SAY_O_LIT_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Say_O_Lit: public FighterBot {
private:
    string targetId;

    string selectTarget(Arena arena);

    Fighter searchById(string id, Arena arena);

    Action* fuir(Arena arena);
public:
    Say_O_Lit();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_DUMB_H