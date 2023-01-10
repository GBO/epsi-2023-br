//
// Created by simon on 25/11/22.
//

#ifndef EPSI_2023_BR_SIMSIM_MIAMSMIAMS_GRRRT_H
#define EPSI_2023_BR_SIMSIM_MIAMSMIAMS_GRRRT_H

#include "FighterBot.h"

class Simsim_miamsmiams_grrrt: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Simsim_miamsmiams_grrrt();

    virtual Action* choose(Arena arena);
    virtual bool canBeKill(Fighter f);

    virtual bool canBeKillByAttack(int attack);
};

#endif //EPSI_2023_BR_SIMSIM_MIAMSMIAMS_GRRRT_H
