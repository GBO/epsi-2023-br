#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Ghislain2.h"

using namespace std;

Ghislain2::Ghislain2() : FighterBot("Ghislain2", 15, 15, 0) { }

string Ghislain2::survey(Arena arena) {
    string targetId;
    for (Fighter fighter : arena.get()) {
        // Il faut penser à s'auto exclure du sondage (c'est ici une copie des Fighter non à jour
        // des opérations que je suis en train de faire).
        if (!this->isMe(fighter) && fighter.getName() == "Ghislain2") {
            // Choisir le premier Bot à avoir un status positionné sur un Fighter encore dans l'arène
            if (fighter.getStatus() != "" && arena.getById(fighter.getStatus()).size() > 0) {
                targetId = fighter.getStatus();
                break;
            }
        }
    }
    return targetId;
}

string Ghislain2::chooseTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();

    // Reste-t-il autre chose que des Ghislain dans l'arene ?
    // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
    bool onlyGhislain = true;
    for (Fighter fighter : fighters) {
        if (fighter.getName() != "Ghislain2") {
            onlyGhislain = false;
            break;
        }
    }

    // Choisissons, maintenant. . . 
    if (onlyGhislain) {
        // On choisit n'importe qui d'autre dans l'arène
        while (this->isMe(target)) {
            target = fighters[rand() % fighters.size()];
        }
    } else {
        // On ne choisit pas un bro'
        while (this->isMe(target) || (target.getName() == "Ghislain2")) {
            target = fighters[rand() % fighters.size()];
        }
    }

    this->display(" désigne comme cible " + target.getNameId());
    return target.getId();
}

string Ghislain2::validateTarget(Arena arena, string id) {
    string targetId;
    // La cible existe-t-elle toujours (pas KO) ?
    if (arena.getById(id).size() > 0) {
        targetId = id;
    } else {
        // Sinon pas de target valide
        targetId = "";
    }
    return targetId;
}



Action* Ghislain2::choose(Arena arena) {
    string targetId = "";

    // J'ai déjà une cible
    if (this->getStatus() != "") {
        // Elle est toujours valide ?
        targetId = this->validateTarget(arena, this->getStatus());
    }

    // Si toujours pas de cible
    if (targetId == "") {
        // On lance un sondage auprès des autres Bot
        // Elle est toujours valide ?
        targetId = this->validateTarget(arena, this->survey(arena));
    }

    // Si toujours pas de cible
    if (targetId == "") {
        // J'en choisi une !
        targetId = this->chooseTarget(arena);
        this->setStatus(targetId);
    }

    // Quoiqu'il arrive on met à jour notre status
    this->setStatus(targetId);

    // On récupère le fighter associé à notre ID cible
    Fighter target = arena.getById(targetId)[0];

    Action* action = nullptr;

    // Sommes-nous sur la case de la cible ?
    if (this->isHere(target)) {
        action = new ActionAttack(target);

    // Sinon, allons-y !
    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
