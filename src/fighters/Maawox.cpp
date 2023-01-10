////#include <algorithm>
////#include <iostream>
////
////#include "ActionMove.h"
////#include "ActionAttack.h"
////
////using namespace std;
////
////Maawox::Maawox() : FighterBot("Maawox", 10, 10, 10) {
////    this->targetId = "";
////    this->setStatus("Dieu vivant");
////}
////
////Fighter Maawox::selectTarget(Arena arena) {
////    vector<Fighter> fighters = arena.get();
////    Fighter target = *this;
////
////    // Pas de cible retenu, on en choisit une !
////    if (this->targetId == "") {
////        // Reste-t-il autre chose que des Maawox dans l'arene ?
////        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
////        bool onlyMaawox = true;
////        for (Fighter fighter : fighters) {
////            if (fighter.getName() != "Maawox") {
////                onlyMaawox = false;
////                break;
////            }
////        }
////        // Choisissons, maintenant. . .
////        if (onlyMaawox) {
////            // On choisit n'importe qui d'autre dans l'arène
////            while (target.isMe(this)) {
////                target = fighters[rand() % fighters.size()];
////            }
////        } else {
////            // On ne choisit pas un bro'
////            while (target.isMe(this) || (target.getName() == "Maawox")) {
////                target = fighters[rand() % fighters.size()];
////            }
////        }
////        // ...On retient son Id
////        this->targetId = target.getId();
////        // ...Et on le dit :)
////        this->display(" désigne comme cible " + target.getNameId());
////
////        // Sinon, on cherche notre cible dans l'arène
////    } else {
////        bool found = false;
////        for (Fighter fighter : fighters) {
////            if (fighter.getId() == this->targetId) {
////                target = fighter;
////                found = true;
////            }
////        }
////        // Si on ne l'a pas trouvé (il est sorti, visiblement)
////        if (!found) {
////            // ...On l'oublie
////            this->targetId = "";
////            // ...Et on en choisit un nouveau
////            target = this->selectTarget(arena);
////        }
////    }
////    return target;
////}
////
////Action* Maawox::choose(Arena arena) {
////    Action* action = nullptr;
////    // On retrouve notre cible
////    Fighter target = this->selectTarget(arena);
////
////    // Sommes-nous sur la case de la cible ?
////    if (target.isHere(this)) {
////        action = new ActionAttack(target);
////
////        // Sinon, allons-y !
////    } else {
////        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
////    }
////
////    return action;
////}


#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "ActionRespe.h"
#include "Maawox.h"


using namespace std;

Maawox::Maawox() : FighterBot("Maawox", 30, 0, 0) {
    this->targetId = "";
    this->gangTargetId = "";
}

Fighter Maawox::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();

    // Pas de cible retenu, on en choisit une !

    if (this->targetId == "") {
        // Reste-t-il autre chose que des Maawox dans l'arene ?
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlyMaawox = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Maawox") {
                onlyMaawox = false;
                break;
            }
        }

        // Choisissons, maintenant. . .
        if (onlyMaawox) {
            // On choisit n'importe qui d'autre dans l'arène
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            // On ne choisit pas un bro'
            while (this->isMe(target) || (target.getName() == "Maawox")) {
                target = fighters[rand() % fighters.size()];
            }
        }




        // ...On retient son Id
        this->targetId = target.getId();

        // On le met en statut
        this->setStatus(targetId);

        for (Fighter fighter: fighters){
            if (fighter.getName() == "Maawox"){
                this->targetId = fighter.getStatus();
                break;
            }
        }
        for (Fighter fighter: fighters){
            if (fighter.getId() == this->targetId){
                target = fighter;
                break;
            }
        }
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

Action* Maawox::choose(Arena arena) {
    vector<Fighter> fighters = arena.get();

    Action* action = nullptr;

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);


//

        if (this->getLife() <= 5){
        this->getFighter().setStatus("Fuit");
        action = new ActionRespe(0, 30, 0);
        int enemy_x = INT_MAX;
        int enemy_y = INT_MAX;
        for (int i = 0; i < fighters.size(); i++){
            if (fighters[i].getX() - this->getX() < enemy_x - this->getY() && fighters[i].getY() - this->getX() < enemy_y - this->getY()){
                enemy_x = fighters[i].getX();
                enemy_y = fighters[i].getY();
            }
        }
        action = new ActionMove(enemy_x * this->getX(), enemy_y * this->getY());
    }
    // Sommes-nous sur la case de la cible ?
    else if (this->isHere(target)) {
        this->getFighter().setStatus("Attaque");

        action = new ActionAttack(target);
        // Sinon, allons-y !
    } else {
        this->getFighter().setStatus("Se déplace pour attaquer");
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}


