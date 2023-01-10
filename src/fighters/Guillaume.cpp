#include "Guillaume.h"
#include "ActionAttack.h"
#include "ActionMove.h"
#include "Arena.h"
#include "Fighter.h"
Guillaume::Guillaume() : FighterBot("Moi", 0, 30, 0) {
}

Action* Guillaume::choose(Arena arena) {
    Action* action = nullptr;
    int randX = rand()%3-1;
    int randY = rand()%3-1;
    action = new ActionMove(randX, randY);

    return action;
}