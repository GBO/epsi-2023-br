#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Sys.h"

using namespace std;

Sys::Sys() : FighterBot("Sys", 14, 14, 2) {
    this->targetId = "";
}

Fighter Sys::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();


    if (this->targetId == "") {

        bool onlyMe = true;
        for (Fighter fighter: fighters) {
            if (fighter.getName() != "Sys" && fighter.getName() != "Fabien" && fighter.getName() != "Jq") {
                onlyMe = false;
                break;
            }
        }

        // Choisissons, maintenant. . .
        if (onlyMe) {
            // On choisit n'importe qui d'autre dans l'arène
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            // On ne choisit pas un bro'
            while (this->isMe(target) || (target.getName() == "Sys") || (target.getName() == "Fabien") || (target.getName() == "Jq")){
                target = fighters[rand() % fighters.size()];
            }
        }
        // ...On retient son Id
        this->targetId = target.getId();
        // ...Et on le dit :)
        this->display(" désigne comme cible " + target.getNameId());
        // Sinon, on cherche notre cible dans l'arène
    } else {
        bool found = false;
        for (Fighter fighter: fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        // Si on ne l'a pas trouvé (il est sorti, visiblement)
        if (!found) {
            // ...On l'oublie
            this->targetId = "";
            // ...Et on en choisit un nouveau
            target = this->selectTarget(arena);
        }
    }

    return target;
}

Fighter Sys::selectMate(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter mate = this->getFighter();

    for (Fighter fighter: fighters) {
        if ((fighter.getName() == "Fabien" ||fighter.getName() == "Jq") && fighter.getName() != "Sys") {
            mate = fighter;
        }

    }
    return mate;
}

    Action *Sys::choose(Arena arena) {

        Action *action = nullptr;
        vector<Fighter> fighters = arena.get();
        // On retrouve notre cible
        Fighter mate = this->selectMate(arena);
        Fighter target = this->selectTarget(arena);
        this->setStatus(target.getNameId());

        if (!this->isHere(mate) && mate.getX() != this->getX()-1 && mate.getY() != this->getX()+1 && mate.getY() != this->getY()-1 && mate.getY() != this->getY()+1) {
            action = new ActionMove(mate.getX() - this->getX(), mate.getY() - this->getY());
        }
        else if (this->isHere(target)) {
            action = new ActionAttack(target);

        } else{
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        }

        return action;
    }
