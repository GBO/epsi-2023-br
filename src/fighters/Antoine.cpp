#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Antoine.h"
#include "log.h"

using namespace std;

Antoine::Antoine() : FighterBot("Antoine", 15, 0, 15) {
}


Fighter Antoine::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();

    // Pas de cible retenu, on en choisit une !

    // Reste-t-il autre chose que des Ghislain dans l'arene ?
    // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
    for (Fighter fighter: fighters) {
        if (!fighter.isMe(this->getFighter())) {
            if (fighter.getLife() < this->getLife()) {
                target = fighter;
            }
        }
    }
    this->display(" désigne comme cible : ", false);
    target.display();


    return target;
}

Action *Antoine::choose(Arena arena) {
    Action *action = nullptr;
    this->setStatus("content");

    Fighter target = this->selectTarget(arena);


    if (this->isHere(target)) {
        action = new ActionAttack(target);

    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
