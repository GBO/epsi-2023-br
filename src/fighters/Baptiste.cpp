//
// Created by Baptiste.L on 01/12/2022.
//

#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Baptiste.h"

using namespace std;
// c'est un bot classique(surtout très bête) qui attaque les bots qui ont le moins de vie, mais attaque en priorité les autres

Baptiste::Baptiste() : FighterBot("Baptiste", 15, 15, 0) {
    this->targetId="";
    this->display("EPSIWIS"); //Spread the EpsiWis
    this->setStatus("cool cool cool"); // Pour pas attaquer Viko
}

Fighter Baptiste::selectTarget(Arena arena) {
    //Récupération des combattants autour de moi
    vector<Fighter> fighters = arena.get(this->getX()-1, this->getY()-1, this->getX()+1, this->getY()+1);
    // GBO Correction de type (version de l'API pas à jour visiblement)
    // Fighter target = *this;
    Fighter target = this->getFighter();

    if (fighters.size() == 0 ){
        this->display("Zebi y'a personne");
        fighters.clear();
        fighters = arena.get();
    }

    //On vérifie si des fighters autres que moi et avec moins de vie que moi sont présents
    if (this->targetId == "") {
        bool onlyHiru = true;
        for (Fighter fighter: fighters) {
            if (fighter.getName() != "Baptiste" && fighter.getLife() < this->getLife() && fighter.getStatus() != "cool cool cool") {
                onlyHiru = false;
                target = fighter;
                break;
            } else if (fighter.getName() != "Baptiste"){
                onlyHiru = false;
                target = fighter;
                break;
            }

        }
        if (onlyHiru) //Si il reste que des moi bon bah GG à tous
        {
            // GBO Correction
            // while (target.isMe(this)) {
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
                this->display("Vrai Homme se tape lui même");
                this->targetId = target.getId();

                return target;
            }
        } else {
            // GBO Correction
            // while (target.isMe(this) || (target.getName() == "Baptiste")) {
            while (this->isMe(target) || (target.getName() == "Baptiste")) {
                target = fighters[rand() % fighters.size()];
            }
        }
        this->targetId = target.getId();
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
            target = this->selectTarget(arena);
        }
    }
    return target;
}

//Maintenant on va taper
Action* Baptiste::choose(Arena arena) {
    Action* action = nullptr;

    Fighter target = this->selectTarget(arena);

    // GBO Correction
    // if (target.isHere(this)) {
    if (this->isHere(target)) {
        action = new ActionAttack(target);
    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}

