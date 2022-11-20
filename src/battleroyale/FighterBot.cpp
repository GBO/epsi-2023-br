#include <iostream>

#include "FighterBot.h"

using namespace std;

FighterBot::FighterBot(string name, int attack, int defense, int speed) {
    this->name = name;
    this->attack = attack;
    this->defense = defense;
    this->speed = speed;
    this->fighter = nullptr;
    this->koRound = 0;
}
FighterBot::~FighterBot() {
    delete this->fighter;
}

Fighter* FighterBot::init() {
    this->fighter = new Fighter(this->name, this->attack, this->defense, this->speed);
    this->id = this->fighter->getId();
    return this->fighter;
}

Fighter FighterBot::getFighter() { return *(this->fighter); }

int FighterBot::getKoRound() { return this->koRound; }
void FighterBot::setKoRound(int koRound) { this->koRound = koRound; }

/** Méthodes Fighter encapsulées et surtout autorisées */
string FighterBot::getName() { return this->fighter->getName(); }
string FighterBot::getNameId() { return this->fighter->getNameId(); }
string FighterBot::getId() { return this->fighter->getId(); }
string FighterBot::getShortId() { return this->fighter->getShortId(); }
int FighterBot::getAttack() { return this->fighter->getAttack(); }
int FighterBot::getDefense() { return this->fighter->getDefense(); }
int FighterBot::getSpeed() { return this->fighter->getSpeed(); }
int FighterBot::getLife() { return this->fighter->getLife(); }
int FighterBot::getX() { return this->fighter->getX(); }
int FighterBot::getY() { return this->fighter->getY(); }
string FighterBot::getStatus() { return this->fighter->getStatus(); }
void FighterBot::setStatus(string status) { this->fighter->setStatus(status); }
void FighterBot::display() { this->fighter->display(); }
void FighterBot::display(string message) { this->fighter->display(message); }
void FighterBot::display(string message, bool newLine) { this->fighter->display(message, newLine); }
bool FighterBot::isMe(Fighter* fighter) { return this->fighter->isMe(fighter); }
bool FighterBot::isMe(Fighter fighter) { return this->fighter->isMe(fighter); }
bool FighterBot::isMe(FighterBot* fighter) { return this->fighter->isMe(fighter->getFighter()); }
bool FighterBot::isHere(Fighter* fighter) { return this->fighter->isHere(fighter); }
bool FighterBot::isHere(Fighter fighter) { return this->fighter->isHere(fighter); }
bool FighterBot::isHere(FighterBot* fighter) { return this->fighter->isHere(fighter->getFighter()); }
bool FighterBot::isHere(int x, int y) { return this->fighter->isHere(x, y); }
bool FighterBot::isKO() { return this->fighter->isKO(); }
