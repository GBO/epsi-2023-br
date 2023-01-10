#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Matteo.h"

using namespace std;

Matteo::Matteo() : FighterBot("Matteo", 10, 20, 0) {
    this->targetId = "";
}

Fighter Matteo::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();

    // On choisit une cible
    if (this->targetId == "") {
        //S'il reste seulement des Matteo
        bool onlyMatteo = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Matteo") {
                onlyMatteo = false;
                break;
            }
        }

        //On choisit n'importe quelle autre cible dans l'arène
        if (onlyMatteo) {
            while (this->isMe(target)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            //Si ça tombe sur un Matteo on choisit une autre cible
            while (this->isMe(target) || (target.getName() == "Matteo")) {
                target = fighters[rand() % fighters.size()];
            }
        }
        //Récupération et affichage de son ID
        this->targetId = target.getId();
        this->display(" désigne comme cible : ", false);
        target.display();

        //Sinon, on cherche notre cible dans l'arène
    } else {
        bool found = false;
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        //Si on ne l'a pas trouvé (il est sorti, visiblement)
        if (!found) {
            // ...On l'oublie
            this->targetId = "";
            // ...Et on en choisit un nouveau
            target = this->selectTarget(arena);
        }
    }

    return target;
}

Action* Matteo::choose(Arena arena) {
    Action* action = nullptr;
    this->setStatus("content");

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);

    /* Les protections fonctionnent, mais pour s'en convaincre, on peut dé commenter :
    // Protection anti heal !
    this->getFighter().suffer(-1000);
    // Protection anti TP !
    this->getFighter().moveTo(target.getX(), target.getY());
    // Protection anti Respe sauvage
    this->getFighter().setStats(30, 0, 0);
    */

    // Sommes-nous sur la case de la cible ?
    if (this->isHere(target)) {
        action = new ActionAttack(target);

        // Sinon, allons-y !
    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
