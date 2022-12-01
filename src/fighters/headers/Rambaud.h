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

    virtual Action* choose(Arena arena);
};

#endif //EPSI_2023_BR_RAMBAUD_H
