#include <iostream>

#include "Action.h"
#include "log.h"

using namespace std;

Action::Action(string name, int ap) {
    this->name = name;
    this->ap = ap;
}
Action::~Action() { }

string Action::getName() { return this->name; }
int Action::getAp() { return this->ap; }
void Action::setArena(Arena* arena) { this->arena = arena; }
void Action::setFighters(vector<Fighter*> fighters) { this->fighters = fighters; }
void Action::setFighter(Fighter* fighter) { this->fighter = fighter; }

string Action::getDisplay() { return this->getName(); }
void Action::display() { log(this->getDisplay()); }
