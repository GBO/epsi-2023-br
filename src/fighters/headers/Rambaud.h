//
// Created by Victor on 25/11/2022.
//

#ifndef EPSI_2023_BR_RAMBAUD_H
#define EPSI_2023_BR_RAMBAUD_H


#include "FighterBot.h"

using namespace std;

class Rambaud : public FighterBot {
public:
    Rambaud();

    Action* choose(Arena arena);
    Fighter selectTarget(Arena arena);
};

#endif //EPSI_2023_BR_RAMBAUD_H
