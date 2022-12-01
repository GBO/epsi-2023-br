#include <iostream>

#include "ActionMove.h"

using namespace std;

ActionMove::ActionMove(int x, int y) : Action("Move") {
    // Raccourci ici : on trasforme les valeurs en -1, 0 ou 1
    if (x > 0) {
        this->x = 1;
    } else if (x < 0) {
        this->x = -1;
    } else {
        this->x = 0;
    }
    if (y > 0) {
        this->y = 1;
    } else if (y < 0) {
        this->y = -1;
    } else {
        this->y = 0;
    }
}

string ActionMove::getDisplay() {
    return "Déplacement " + to_string(this->x) + "x" + to_string(this->y);
}

bool ActionMove::isValid() {
    // On calcule la position hypothétique
    int fighterx = this->fighter->getX() + this->x;
    int fightery = this->fighter->getY() + this->y;
    // On retourne true si elle bien dans l'arène
    return 
        fighterx >= 0 &&
        fighterx < this->arena->getWidth() && 
        fightery >= 0 &&
        fightery < this->arena->getHeight();
}

void ActionMove::perform() {
    // Les x & y étant etre -1 & 1, ça nous simplifie le moveTo :)
    this->fighter->moveTo(this->fighter->getX() + this->x, this->fighter->getY() + this->y);
}
