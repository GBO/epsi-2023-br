#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "QuentinV.h"

using namespace std;

QuentinV::QuentinV() : FighterBot("QuentinV", 0, 30, 0) {
    this->targetId = "";
    this->regroupSet = false;
    this->regroup = false;
    this->quentinBotsXAverage = 0;
    this->quentinBotsYAverage = 0;
}

Fighter QuentinV::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    vector<Fighter> others;
    Fighter target = this->getFighter();

    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        // Reste-t-il autre chose que des Ghislain dans l'arene ?
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlyQuentin = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "QuentinV") {
                onlyQuentin = false;
                others.push_back(fighter);
                break;
            }
        }

        // Choisissons, maintenant. . . 
        if (onlyQuentin) {
            // On choisit n'importe qui d'autre dans l'arène
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            target = others[0];
            for(Fighter other : others) {
                if (target.getX()-this->getX() >= other.getX()-this->getX() && target.getY()-this->getY() >= other.getY()-this->getY()){
                    if (target.getX()-this->getX() == other.getX()-this->getX() && target.getY()-this->getY() == other.getY()-this->getY() && target.getLife() < other.getLife()){
                        target = target;
                    }
                    else{
                        target = other;
                    }
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

void QuentinV::setRegroup(Arena arena) {
    vector<Fighter> fighters = arena.get();
    vector<int> quentinBotsX;
    vector<int> quentinBotsY;
    int xAverage = 0;
    int yAverage = 0;

    for (Fighter fighter : fighters) {
        if (fighter.getName() == "QuentinV") {
            quentinBotsX.push_back(fighter.getX());
            quentinBotsY.push_back(fighter.getY());
        }
    }

    for (int i = 0; i < quentinBotsX.size(); i++){
        xAverage += quentinBotsX[i];
        yAverage += quentinBotsY[i];
    }

    quentinBotsXAverage = xAverage / (quentinBotsX.size()+1);
    quentinBotsYAverage = yAverage / (quentinBotsY.size()+1);
    regroupSet = true;
}

Action* QuentinV::choose(Arena arena) {
    this->getFighter().setStatus("content");

    Action* action = nullptr;

    setRegroup(arena);
    if (this->getX() == quentinBotsXAverage && this->getY() == quentinBotsYAverage){
        regroup = true;
        this->getFighter().setStats(20, 10, 0);
    }
    if (!regroup){
        action = new ActionMove(quentinBotsXAverage - this->getX(), quentinBotsYAverage - this->getY());
        return action;
    }

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
