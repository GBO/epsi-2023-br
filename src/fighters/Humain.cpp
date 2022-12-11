#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Humain.h"
#include "log.h"

using namespace std;

Humain::Humain() : FighterBot("Humain", 10, 10, 10, 10) {
}

Action* Humain::choose(Arena arena) {
    Action* action = nullptr;
    int choice;

    this->display(" action ?");
    logln("1. Move");
    logln("2. Attack");
    cin >> choice;

    if (choice == 1) {
        int x;
        int y;
        logln("Direction x puis y ?");
        cin >> x;
        cin >> y;
        action = new ActionMove(x, y);

    } else if (choice == 2) {
        logln("Qui ?");
        for (Fighter fighter : arena.get(this->getFighter())) {
            fighter.display(" " + fighter.getId());
        }
        string id;
        cin >> id;
        for (Fighter fighter : arena.get(this->getFighter())) {
            if (fighter.getId() == id) {
                action = new ActionAttack(fighter);
                break;
            }
        }
    }

    return action;
}
