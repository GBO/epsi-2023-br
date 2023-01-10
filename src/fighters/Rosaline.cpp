#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
// GBO Correction
// #include "Rosalyne.h"
#include "Rosaline.h"

using namespace std;

Rosalyne::Rosalyne() : FighterBot("Rosalyne", 15, 15, 0) {
    this->targetId = "";
    this->setStatus("content");
}

Fighter Rosalyne::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    // GBO Correction de type (version de l'API pas à jour visiblement)
    // Fighter target = *this;
    Fighter target = this->getFighter();

    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        // Reste-t-il autre chose que des Rosalyne dans l'arene ?
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlyGhislain = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Rosalyne") {
                onlyGhislain = false;
                break;
            }
        }

        // Choisissons, maintenant. . . 
        // GBO Correction
        // if (Rosalyne) {
        if (true) {
            // On choisit n'importe qui d'autre dans l'arène
            // GBO Correction
            // while (target.isMe(this)) {
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            // On ne choisit pas un bro'
            // GBO Correction
            // while (target.isMe(this) || (target.getName() == "Rosalyne")) {
            while (this->isMe(target) || (target.getName() == "Rosalyne")) {
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

Action* Rosalyne::choose(Arena arena) {
    Action* action = nullptr;

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);

    // Sommes-nous sur la case de la cible ?
    // GBO Correction
    // if (target.isHere(this)) {
    if (this->isHere(target)) {
        action = new ActionAttack(target);

    // Sinon, allons-y !
    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
