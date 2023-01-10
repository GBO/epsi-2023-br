#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "ActionRespe.h"
#include "Viko.h"

using namespace std;

Viko::Viko() : FighterBot("Viko", 20, 10, 0) {
    this->targetId = "";
}

Fighter Viko::selectTarget(Arena arena) {

    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();
    Action* action = nullptr;

    if (this->targetId == "") {

        bool isFriend = true;
        bool littleAttack = true;
        for (Fighter fighter : fighters) {
            if (fighter.getAttack() > 25) {
                littleAttack = false;
                break;
            } else if (fighter.getStatus() != "cool cool cool") {
                isFriend = false;
                break;
            }
        }

        if (littleAttack && isFriend) {
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            if (isFriend) {
                while (this->isMe(target)) {
                    target = fighters[rand() % fighters.size()];
                }
            } else {
                while (this->isMe(target) || (target.getStatus() == "cool cool cool")) {
                    target = fighters[rand() % fighters.size()];
                }
            }
        }
        this->targetId = target.getId();

    } else {
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
    }

    return target;
}

Action* Viko::choose(Arena arena) {
    Action* action = nullptr;
    this->setStatus("cool cool cool");
    this->display(": EPSI WIIIIIIIIIIIIIIIIIS !");
    this->display(": EPSI WIIIIIIIIIIIIIIIIIS !");
    this->display(": EPSI WIIIIIIIIIIIIIIIIIS !");
    this->display(": EPSI WIIIIIIIIIIIIIIIIIS !");
    this->display(": EPSI WIIIIIIIIIIIIIIIIIS !");

    Fighter target = this->selectTarget(arena);


    if (this->isHere(target)) {
        action = new ActionAttack(target);
    } else {
        if (target.getStatus() == "cool cool cool" && this->getDefense() != 25) {
            action = new ActionRespe(5,25,0);
        } else if (target.getStatus() != "cool cool cool" && this->getDefense() != 10) {
            action = new ActionRespe(20, 10, 0);
        } else {
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        }
    }

    return action;
}
