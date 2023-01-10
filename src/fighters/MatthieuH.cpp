#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "MatthieuH.h"

using namespace std;

MatthieuH::MatthieuH() : FighterBot("MatthieuH", 15, 15, 0) {
    this->targetId = "";
}

Action *MatthieuH::choose(Arena arena) {
    Action *action = nullptr;

    vector<Fighter> fighters = arena.get();

    Fighter target = this->getFighter();

    if (fighters.size() == 2) {

        for (int i = 0; i < fighters.size(); ++i) {
            if (!fighters[i].isMe(this->getFighter())) {
                target = fighters[i];

                if (target.isHere(this->getX(), this->getY())) {
                    action = new ActionAttack(target);
                } else {
                    action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());

                }

            }
        }
    } else {

        bool isClose = false;

        for (int i = 0; i < fighters.size(); ++i) {

            if (!fighters[i].isMe(this->getFighter()) && fighters[i].isHere(this->getX(), this->getY())) {
                isClose = true;
            }
        }

        if (isClose) {

            bool emptyPlace = false;

            for (int i = 0; i < fighters.size(); i++) {

                for (int j = -1; j < 2; j++) {

                    for (int k = -1; k < 2; k++) {

                        if (!emptyPlace && !fighters[i].isMe(this->getFighter()) &&
                            !fighters[i].isHere(this->getX() + j, this->getY() + k)) {
                            if (!(this->getX() == 0 && j == -1) && !(this->getX() == 9 && j == 1) &&
                                !(this->getY() == 0 && k == -1) && !(this->getY() == 9 && k == 1)) {
                                action = new ActionMove(j, k);
                                emptyPlace = true;

                            }

                        }

                    }

                }

            }

            if (!emptyPlace) {
                action = new ActionMove(0, 0);
            }

        } else {
            action = new ActionMove(0, 0);
        }

    }


    return action;
}
