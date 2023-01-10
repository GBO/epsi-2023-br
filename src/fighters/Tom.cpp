#include <algorithm>
#include <iostream>
#include <map>


#include "ActionMove.h"
#include "ActionAttack.h"
#include "Tom.h"
#include "ActionRespe.h"

using namespace std;

Tom::Tom() : FighterBot("Tom", 0, 30, 0) {
    this->targetId = "";
}

Fighter Tom::selectTargetLeader(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();
    // si aucune cible n'est retenue, on en choisit une
    if (this->targetId == "") {
        // s'il reste que des Tom dans l'arène
        bool onlyTom = true;
        int gang = 0;
        int gangMember = 0;
        for (Fighter fighter: fighters) {
            if (fighter.getName() != this->getName()) {
                onlyTom = false;
            } else {
                if (fighter.getStatus() == "g" || fighter.getStatus().substr(0,1) == "l") {
                    gang++;
                }
                gangMember++;//nombre de Tom en vie
            }
        }
        if (onlyTom){
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            int targetDistance = INT32_MAX;
            for (Fighter fighter: fighters) {
                if (fighter.getName() != this->getName() && !this->isMe(fighter) && fighter.getLife() > 0) {
                    int distance = abs(fighter.getX() - this->getX()) + abs(fighter.getY() - this->getY());
                    if (distance < targetDistance) {
                        target = fighter;
                        targetDistance = distance;
                        if (targetDistance == 0) {
                            break;
                        }
                    }
                }
            }
            if (gang!=gangMember && targetDistance != 0) { //si le gang n'est pas réuni et qu'il n'y a pas de cible sur la même case
                target = this->getFighter();
            }
            return target;
        }

    } else {
        bool found = false;
        for (Fighter fighter: fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        if (!found) {
            this->targetId = "";
            target = this->selectTargetLeader(arena);
        }
    }
    return target;
}

Fighter Tom::selectTarget(Arena arena, Fighter leader) {
    if (leader.getStatus() != "l") {
        string targetId = leader.getStatus().substr(1, leader.getStatus().size() - 1);
        for (Fighter fighter: arena.get()) {
            if (fighter.getId() == targetId) {
                return fighter;
            }
        }
    }
    return this->getFighter();
}

Fighter Tom::leaderExist(Arena arena) {
    Action *action = nullptr;
    for (Fighter fighter: arena.get()) {
        if (fighter.getName() == this->getName() && fighter.getStatus().substr(0, 1) == "l") {
            this->display("Leader found");
            return fighter;
        }
    }
    this->display("No leader found");
    return this->getFighter();
}

Action *Tom::choose(Arena arena) {
    Action *action = nullptr;
    Fighter target = this->getFighter();
    auto leader = this->leaderExist(arena);
    if (this->getX() == arena.getWidth() - 1 && this->getY() == 0 && this->getStatus().substr(0, 1) != "g" &&
        this->getStatus().substr(0, 1) != "l") {
        if (leader.getId() != this->getId()) {
            this->setStatus("g");
        } else {
            this->setStatus("l");
            action = new ActionRespe(0, 29, 1);
        }
    } else if (this->getStatus().substr(0, 1) != "l" && this->getStatus().substr(0, 1) != "g") {
        action = new ActionMove(arena.getWidth() - 1 - this->getX(),
                                0 - this->getY());
    } else {
        if (leader.getId() == this->getId()) {
            target = this->selectTargetLeader(arena);
            if (target.getId() != this->getId()) {
                this->setStatus("l" + target.getId());
            } else {
                this->setStatus("l");
            }
            if (target.getX() == this->getX() && target.getY() == this->getY()) {
                if (target.getId() != this->getId()) {
                    action = new ActionAttack(target);
                }
            } else {
                action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
            }
        } else {
            target = this->selectTarget(arena, leader);
            if (target.getId() != this->getId()) {
                if (target.getX() == this->getX() && target.getY() == this->getY()) {
                    action = new ActionAttack(target);
                } else {
                    action = new ActionMove(leader.getX() - this->getX(),
                                            leader.getY() - this->getY()); // On se dirige vers le leader
                }
            }
        }
    }
    return action;
}
