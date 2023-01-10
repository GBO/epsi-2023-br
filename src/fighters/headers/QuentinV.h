#ifndef FIGHTERS_QUENTINV_H
#define FIGHTERS_QUENTINV_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class QuentinV: public FighterBot {
private:
    string targetId;
    bool regroupSet;
    bool regroup;
    int quentinBotsXAverage;
    int quentinBotsYAverage;

    Fighter selectTarget(Arena arena);

    void setRegroup(Arena arena);

public:
    QuentinV();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_QUENTINV_H
