#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Fabien.h"

using namespace std;

Fabien::Fabien() : FighterBot("Fabien", 15, 14, 1) {
    this->targetId = "";
}

Fighter Fabien::selectTarget(Arena arena, Fighter mate) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();


    for (Fighter fighter: fighters) {
        if (fighter.getNameId() == mate.getStatus()) {
            target = fighter;
        }
    }
    return target;
}


Fighter Fabien::selectMate(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter mate = this->getFighter();

    for (Fighter fighter: fighters) {
        if (fighter.getName() == "Sys") {
            return fighter;
        }
    }

}

Action *Fabien::choose(Arena arena) {

    Action *action = nullptr;
    vector<Fighter> fighters = arena.get();
    // On retrouve notre cible
    Fighter mate = this->selectMate(arena);
    Fighter target = this->selectTarget(arena, mate);
    this->setStatus(target.getNameId());

    if (!this->isHere(mate)) {
        action = new ActionMove(mate.getX() - this->getX(), mate.getY() - this->getY());
    } else if (this->isHere(target)) {
        action = new ActionAttack(target);

    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }


    return action;
}
