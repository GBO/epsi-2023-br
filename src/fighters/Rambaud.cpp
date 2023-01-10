//
// Created by Victor on 25/11/2022.
//

#include <iostream>

#include "ActionMove.h"
#include "Rambaud.h"

using namespace std;

Rambaud::Rambaud() : FighterBot("Rambaud",20, 10, 0) {
}

Action* Rambaud::choose(Arena arena) {
    Action* action = nullptr;

    this->selectTarget(arena);

    if (this->getX() != 6){
        if (this->getX() > 6){
            action = new ActionMove(- 1,0);
        } else {
            action = new ActionMove(1, 0);
        }
    }

    if (this->getY() != 9){
        if (this->getY() > 9){
            action = new ActionMove(0,- 1);
        } else {
            action = new ActionMove(0,1);
        }
    }

    if (action == nullptr){
        this->display("EPSI - WIZ");
        this->display("EPSI - WIIZ");
        this->display("EPSI - WIIIZ");
        this->display("EPSI - WIIIIZ");
        this->display("EPSI - WIIIIIZ");
        this->display("EPSI - WIIIIIIZ");
        this->display("EPSI - WIIIIIIIZ");
        this->display("EPSI - WIIIIIIIIZ");
        this->display("EPSI - WIIIIIIIIIZ");
        this->display("EPSI - WIIIIIIIIIIZ");
        this->display("EPSI - WIIIIIIIIIIIZ");
    }


    return action;
}

// sa marche juste pas du tout
// pour une raison sombre
// fesse
// ALED
Fighter Rambaud::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();

    for (Fighter fighter : fighters){
        if (fighter.getX() == 6 && fighter.getY() == 9 && fighter.getName() != "Rambaud")
            target = fighter;
    }

    return target;
};

