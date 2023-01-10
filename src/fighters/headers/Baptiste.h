//
// Created by Baptiste.L on 01/12/2022.
//
#ifndef FIGHTER_BR_BAPTISTE_H
#define FIGHTER_BR_BAPTISTE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Baptiste: public FighterBot{
private:
    string targetId;
    Fighter selectTarget(Arena arena);

public:
    Baptiste();

    virtual Action* choose(Arena arena);
};

#endif //EPSI_2023_BR_HIRU_H
