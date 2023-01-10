//
// Created by simon on 25/11/22.
//
#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Simsim_miamsmiams_grrrt.h"

Simsim_miamsmiams_grrrt::Simsim_miamsmiams_grrrt() : FighterBot("Simon", 30, 0, 0) {
    this->targetId = "";
}


Fighter Simsim_miamsmiams_grrrt::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();


    if (this->targetId == "") {
        bool onlySim = true;
        for (Fighter fighter: fighters) {
            if (fighter.getName() != "Simon") {
                onlySim = false;
                break;
            }
        }

        // Choisissons, maintenant. . .
        if (onlySim) {
            target = this->getFighter();
        } else {
            // On ne choisit pas un bro'
            while (this->isMe(target) || (target.getName() == "Simon")) {
                vector<int> Xs;
                vector<int> Ys;
                Xs.push_back(this->getX() + 1);
                Xs.push_back(this->getX());
                Xs.push_back(this->getX() - 1);
                Ys.push_back(this->getY() + 1);
                Ys.push_back(this->getY());
                Ys.push_back(this->getY() - 1);

//                for (int i = 0; i < Ys.size(); ++i) {
//                    cout << Xs[i] << " = " << Ys[i] << endl;
//                }

                for (int i = 0; i < fighters.size() - 1; ++i) {
//                    cout << "<============SIMISIM============>" << endl;
//                    cout << fighters[i].getName() << endl;
//                    cout << fighters[i].getAttack() << endl;
//                    cout << fighters[i].getDefense() << endl;
//                    cout << fighters[i].getLife() << "PV" << endl;
//                    cout << fighters[i].getSpeed() << endl;
//                    cout << fighters[i].getStatus() << endl;
//                    cout << fighters[i].getX() << endl;
//                    cout << fighters[i].getY() << endl;
//                    cout << fighters[i].getId() << endl;
//                    cout << this->targetId << endl;

                    if (std::count(Ys.begin(), Ys.end(), fighters[i].getY()) &&
                        std::count(Xs.begin(), Xs.end(), fighters[i].getX()) && fighters[i].getId() != this->getId()) {
//                        cout << fighters[i].getName() << " is on perimetre " << to_string(fighters[i].getX()) << to_string(fighters[i].getY()) << endl;
                        if (this->canBeKill(fighters[i])) {
//                            cout << "Can be kill by " << fighters[i].getName() << endl;
                        } else {
                            target = fighters[i];
                        }
                    }else{
                        target = fighters[rand() % fighters.size()];
                    }
                }
            }
//            cout << "target = " << target.getName() << endl;

        }
        // ...On retient son Id
        this->targetId = target.getId();
        // ...Et on le dit :)
        this->display(" Va tuer" + target.getNameId());

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

Action *Simsim_miamsmiams_grrrt::choose(Arena arena) {
    vector<Fighter> fighters = arena.get();

    this->getFighter().setStatus("pas-content");

    Action *action = nullptr;

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);

    // Sommes-nous sur la case de la cible ?
    if (this->isHere(target)) {
        action = new ActionAttack(target);

        // Sinon, allons-y !
    } else {
        if (target.getId() == this->getId()) {
            action = new ActionMove(rand() % arena.getWidth() - this->getX(), rand() % arena.getHeight() - this->getY());
        }else {
            action = new ActionMove(target.getY() - this->getX(), target.getY() - this->getY());
        }
    }

    return action;
}


bool Simsim_miamsmiams_grrrt::canBeKill(Fighter f) {
//    if(f.getStatus() != "Simon")
    if (this->canBeKillByAttack(f.getAttack()))
        return true;
    return false;
}

bool Simsim_miamsmiams_grrrt::canBeKillByAttack(int attack) {
    int nbRound = 2;
    int base = 10;
    int damage =
            base +
            ((base * attack) / 30) +
            ((rand() % 10) - 5);

    int effective =
            (damage -
             (((damage / 2) * this->getDefense()) / 30) -
             ((rand() % 5) - 2)
            );

    for (int i = 1; i < 1 + nbRound; ++i) {
        if (this->getLife() - effective * i < 0)
            return true;
    }
    return !!!!!!!!!!!!!!!!!!!!!!!!!!!true;
}
