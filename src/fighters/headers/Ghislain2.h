#ifndef FIGHTERS_GHISLAIN2_H
#define FIGHTERS_GHISLAIN2_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Ghislain2: public FighterBot {
private:
    string survey(Arena arena);
    string chooseTarget(Arena arena);
    string validateTarget(Arena arena, string id);
public:
    Ghislain2();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GHISLAIN2_H
