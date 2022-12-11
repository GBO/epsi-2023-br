#ifndef BATTLEROYALE_FIGHTERBOT_H
#define BATTLEROYALE_FIGHTERBOT_H

#include <iostream>

#include "Action.h"
#include "ActionRespe.h"
#include "Arena.h"
#include "Fighter.h"

using namespace std;

/** FighterBot abstrait
 * Un FighterBot est composé d'un Fighter pour protéger les opérations
 * possibles sur le Fighter effectif */
class FighterBot {
private:
    /** Stats du Fighter utilisé pour l'init */
    string name;
    int attack;
    int defense;
    int speed;
    int intention;
    /** ID de Bot (commun au Fighter) */
    string id;
    /** Le round de KO */
    int koRound;
    /** Le Fighter sous-jacent : il est caché là pour limité l'accès
     * aux méthodes du Fighter */
    Fighter* fighter;

public:
    /** Constructeur */
    FighterBot(string name, int attack, int defense, int speed, int intention);
    virtual ~FighterBot();

    /** Accesseurs (getters) / mutateurs (setters) */
    int getKoRound();
    void setKoRound(int koRound);

    /** Créer un Fighter avec les stats du FighterBot */
    Fighter getFighter();

    /** Initialise le Bot et retourne le Fighter créé à l'occasion */
    Fighter* init();

    /** Méthode abstraite de choix de l'action */
    virtual Action* choose(Arena arena) = 0;

    /** Méthode abstraite de choix de l'action */
    virtual ActionRespe* levelup();

    /** Méthodes Fighter encapsulées et surtout autorisées */
    string getName();
    string getNameId();
    string getId();
    string getShortId();
    int getAttack();
    int getDefense();
    int getSpeed();
    int getIntention();
    int getLife();
    int getLevel();
    int getAp();
    int getX();
    int getY();
    string getStatus();
    void setStatus(string status);
    void display();
    void display(string message);
    void display(string message, bool newLine);
    bool isHere(int x, int y);
    bool isHere(Fighter fighter);
    bool isHere(Fighter* fighter);
    bool isHere(FighterBot* fighter);
    bool isMe(Fighter* fighter);
    bool isMe(Fighter fighter);
    bool isMe(FighterBot* fighter);
    bool isKO();
};

#endif //BATTLEROYALE_FIGHTERBOT_H
