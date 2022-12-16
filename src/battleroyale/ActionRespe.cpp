#include <iostream>

#include "ActionRespe.h"

using namespace std;

ActionRespe::ActionRespe(int attack, int defense, int speed) : Action("Respe") {
    this->attack = attack;
    this->defense = defense;
    this->speed = speed;
}

string ActionRespe::getDisplay() {
    return "Respécialisation en " + to_string(this->attack) + "/" + to_string(this->defense) + "/" + to_string(this->speed);
}

bool ActionRespe::isValid() {
    return (this->attack + this->defense + this->speed) <= (30 + (5 * fighter->getLevel()));
}

void ActionRespe::perform() {
    this->fighter->setStats(this->attack, this->defense, this->speed);
}
