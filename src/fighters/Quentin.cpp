#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionRespe.h"
#include "ActionAttack.h"
#include "Quentin.h"

using namespace std;

Quentin::Quentin() : FighterBot("Quentin", 10, 10, 10) {
    this->targetId = "";
}

Fighter Quentin::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();

    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        // Reste-t-il autre chose que des Quentin dans l'arene ?
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlyQuentin = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Quentin") {
                onlyQuentin = false;
                break;
            }
        }

        // Choisissons, maintenant. . . 
        if (onlyQuentin) {
            // On choisit n'importe qui d'autre dans l'arène
            while (this->isMe(target)) {
                if (rand() % fighters.size() != (target.getName() == "Quentin")){
                    target = fighters[0];
                } else {
                    target = fighters[1];
                }
            }
        } else {
            // On ne choisit pas un Minecraftien
            while (this->isMe(target) || (target.getName() == "Quentin")) {
                target = fighters[rand() % fighters.size()];
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

Action* Quentin::choose(Arena arena) {
    Action* action = nullptr;
    this->setStatus("content");
    

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);
    
    /* Les protections fonctionnent, mais pour s'en convaincre, on peut décommenter :
    // Protection anti heal !
    this->getFighter().suffer(-1000);
    // Protection anti TP !
    this->getFighter().moveTo(target.getX(), target.getY());
    // Protection anti Respe sauvage
    this->getFighter().setStats(30, 0, 0);
    */

    // Sommes-nous sur la case de la cible ?
    if (this->isHere(target)) {
        if (this->changeStatsHere == true) {
            // On change nos stats
            this->changeStatsHere = false;
            action =new ActionRespe(15, 15, 0);
            
        }else{
            action = new ActionAttack(target);
            this->changeStatsThere = true;
        }
        

    // Sinon, allons-y !
    } else {
        if (this->changeStatsThere == true) {
            // On change nos stats
            this->changeStatsThere = false;
            action = new ActionRespe(0, 10, 20);
            
        }else{
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
            this->changeStatsHere = true;
        }
    }

    return action;
}
