#include <iostream>

#include "ActionRespe.h"

using namespace std;

ActionRespe::ActionRespe(int attack, int defense, int speed, int intention) : Action("Respe", AP_UNIT) {
    this->attack = attack;
    this->defense = defense;
    this->speed = speed;
    this->intention = intention;
}

string ActionRespe::getDisplay() {
    return "Respécialisation en " + to_string(this->attack) + "/" + to_string(this->defense) + "/" + to_string(this->speed) + "/" + to_string(this->intention);
}

bool ActionRespe::isValid() {
    return (this->attack >= 0 && this->defense >= 0 && this->speed >= 0 && this->intention >= 0) &&
        (this->attack + this->defense + this->speed + this->intention) <= (40 + (5 * fighter->getLevel()));
}

void ActionRespe::perform() {
    this->fighter->setStats(this->attack, this->defense, this->speed, this->intention);
}
