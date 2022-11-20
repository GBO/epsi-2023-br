#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Dumb.h"

using namespace std;

Dumb::Dumb() : FighterBot("Dumb", 10, 10, 10) {
}

Action* Dumb::choose(Arena arena) {
    Action* action = nullptr;
    for (Fighter fighter : arena.get(this->getFighter())) {
        if (!this->isMe(fighter)) {
            action = new ActionAttack(fighter);
            break;
        }
    }
    return action;
}
