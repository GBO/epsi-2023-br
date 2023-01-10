#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Say_O_Lit.h"
#include "math.h"

using namespace std;

Say_O_Lit::Say_O_Lit() : FighterBot("Say_O_Lit", 20, 10, 0) {}

string Say_O_Lit::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = this->getFighter();
    int myX = this->getX();
    int myY = this->getY();
    int cpt = 0;

//Au début du tour, on détermine la cible la plus proche
    for (Fighter fighter: fighters) {
        int distance = sqrt(pow(fighter.getX() - myX, 2) + pow(fighter.getY() - myY, 2));
        if (cpt == 0) {
            this->targetId = fighter.getId();
            cpt = distance;
        } else if (cpt < distance) {
            cpt = distance;
            this->targetId = fighter.getId();
        } else {}
    }
    return this->targetId;
}

Fighter Say_O_Lit::searchById(string id, Arena arena){
    vector<Fighter> fighters = arena.get();
    Fighter targetFighter = this->getFighter();
    for (Fighter fighter : fighters) {
        if (fighter.getId() == id) {
            targetFighter = fighter;
        }
    }
    return targetFighter;
}

Action* Say_O_Lit::fuir(Arena arena){
    string targetId = selectTarget(arena);
    Fighter fighter = searchById(targetId, arena);
    int x = this->getX() - fighter.getX();
    int y = this->getY() - fighter.getY();
    int xTmp;
    int yTmp;
    int ymin =0;
    int xmin = 0;
    int ymax = arena.getHeight();
    int xmax = arena.getWidth();
    if (x>0){
        xTmp = 1;
        if (this->getX()+1 > xmax){
            x = 0;
        }
    } else{
        xTmp = -1;
        if (this->getX()-1 < xmin){
            x = 0;
        }
    }
    if (y>0){
        yTmp = 1;
        if (this->getY()+1 > ymax){
            y = 0;
        }
    } else{
        yTmp = -1;
        if (this->getY()-1 < ymin){
            y = 0;
        }
    }
    return new ActionMove(x, y);

}

Action *Say_O_Lit::choose(Arena arena) {
    Action *action = nullptr;
    int cpt = 0;
    Fighter target = searchById(selectTarget(arena), arena);
    for (Fighter fighter : arena.get(this->getFighter())) {
        //cpt++;
    }
    for (Fighter fighter : arena.get(this->getFighter())) {
        if (!this->isMe(fighter)) {
            action = new ActionAttack(fighter);
            break;
        }
        //j'ai essayé de faire en sorte que quand il reste une personne il attzque mais ça ne fonctionne pas et je n'ai plus le temps
        if (cpt == 1){
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        }
        else{
            action = fuir(arena);
        }
    }

    return action;
}
