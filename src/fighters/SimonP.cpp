#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "SimonP.h"

using namespace std;

SimonP::SimonP() : FighterBot("SimonP", 20, 10, 0) {
    this->targetId = "";
    this->regroupSet = false;
    this->XAverage = 0;
    this->YAverage = 0;
}

Fighter SimonP::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    vector<Fighter> others;
    Fighter target = this->getFighter();

    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        // Reste-t-il autre chose que des Ghislain dans l'arene ?
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlySimon = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "SimonP") {
                onlySimon = false;
                others.push_back(fighter);
                break;
            }
        }

        // Choisissons, maintenant. . .
        if (onlySimon) {
            // On choisit n'importe qui d'autre dans l'arène
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            target = others[0];
            for(Fighter other : others) {
                if (target.getX()-this->getX() >= other.getX()-this->getX() && target.getY()-this->getY() >= other.getY()-this->getY()){
                    target = other;
                }
            }
        }
        // ...On retient son Id
        this->targetId = target.getId();
        // ...Et on le dit :)
        this->display(" désigne comme cible : ", false);
        target.display();

        // Sinon, on cherche notre cible dans l'arène
    } else {
        bool found = false;
        for (Fighter fighter : fighters) {
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

void SimonP::setRegroup(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter me = this->getFighter();
    vector<Fighter> simon;
    vector<int> simonX;
    vector<int> simonY;

    for (Fighter fighter : fighters) {
        if (fighter.getName() == "SimonP") {
            simon.push_back(fighter);
            simonX.push_back(fighter.getX());
            simonY.push_back(fighter.getY());
        }
    }

    for (int i = 0; i > simon.size(); i++){
        XAverage += simonX[i];
        YAverage += simonY[i];
    }

    XAverage = XAverage / simon.size();
    YAverage = YAverage / simon.size();

    regroupSet = true;
}

Action* SimonP::choose(Arena arena) {
    this->getFighter().setStatus("content");

    Action* action = nullptr;

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);
    // Sommes-nous sur la case de la cible ?
    if (this->isHere(target)) {
        action = new ActionAttack(target);
        // Sinon, allons-y !
    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}