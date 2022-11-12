#include <iostream>

#include "FighterBot.h"

using namespace std;

FighterBot::FighterBot(string name, int attack, int defense, int speed) : Fighter(name, attack, defense, speed) {
    this->koRound = 0;
}

int FighterBot::getKoRound() { return this->koRound; }
void FighterBot::setKoRound(int koRound) { this->koRound = koRound; }
