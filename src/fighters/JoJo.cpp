#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "JoJo.h"
#include <math.h>

using namespace std;

JoJo::JoJo() : FighterBot("JoJo", 15, 0, 15) {
    this->targetId = "";

}

Fighter JoJo::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get(); // liste tous les fighter
    Fighter target = this->getFighter();


    if ((this->targetId == "")) {
        while ((this->isMe(target ) || (target.getLife()/1.5 > this->getLife()))) {
            target = fighters[rand() % fighters.size()];
        }
    }
    this->targetId = target.getId();

    this->display(" désigne comme cible " + target.getNameId());

    bool found = false;
    for (Fighter fighter : fighters) {
        if (fighter.getId() == this->targetId) {
            target = fighter;
            found = true;
        }
    }

    if (!found) {
        this->targetId = "";
        target = this->selectTarget(arena);
    }

    return target;



}
Action* JoJo::choose(Arena arena) {
    this->getFighter().setStatus("content");

    Action *action = nullptr;

    Fighter target = this->selectTarget(arena);


    if (this->isHere(target)) {
        action = new ActionAttack(target);

    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}

