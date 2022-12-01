//
// Created by Victor on 25/11/2022.
//

#include <iostream>

#include "ActionMove.h"
#include "Rambaud.h"

using namespace std;

Rambaud::Rambaud() : FighterBot("Rambaud", 20, 10, 0) {
}

Action* Rambaud::choose(Arena arena) {
    Action* action = nullptr;
    this->getFighter().moveTo(5,5);
    return action;
}