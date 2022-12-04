#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>


#include "Fighter.h"
#include "log.h"

using namespace std;

Fighter::Fighter(string name, int attack, int defense, int speed) {
    this->name = name;
    // Calcul d'ID discutable basé sur l'adresse de l'instance...
    // Les 3 lignes en dessous ne servent qu'à convertir le pointeur this en chaine de caractère ^_^'
    // J'suis pas hyper fier de moi...
    ostringstream pointer_to_string;
    pointer_to_string << this;
    this->id = pointer_to_string.str();
    // Une version courte de l'ID qui peut être utilisée pour l'affichage par exemple
    // On utilise la méthode substr pour ne conserver que les derniers caratères de l'ID
    this->shortId = this->id.substr(this->id.size()-4);

    // Vie
    this->life = 100;

    // Position à 0 par défaut
    this->x = 0;
    this->y = 0;
    // Status
    this->status = "";

    // Stats à 0 par défaut
    this->attack = 0;
    this->defense = 0;
    this->speed = 0;
    // Puis respé
    this->setStats(attack, defense, speed);
}

/** Destructeur vide par defaut */
Fighter::~Fighter() { }

void Fighter::setStats(int attack, int defense, int speed) {
    // Controle de valeurs valides
    if (attack >= 0 && defense >= 0 && speed >= 0 && (attack + defense + speed <= 30)) {
        this->attack = attack;
        this->defense = defense;
        this->speed = speed;
    } else {
        // Sinon fallback aux valeurs par défaut
        this->attack = 10;
        this->defense = 10;
        this->speed = 10;
    }
    this->display(" a initialisé ses stats : ", false);
    log(this->attack, RED);
    log("/");
    log(this->defense, GREEN);
    log("/");
    logln(this->speed, BLUE);
}

/** Accesseurs */
string Fighter::getName() { return this->name; }
string Fighter::getNameId() { return this->name + this->shortId; }
string Fighter::getId() { return this->id; }
string Fighter::getShortId() { return this->shortId; }
int Fighter::getAttack() { return this->attack; }
int Fighter::getDefense() { return this->defense; }
int Fighter::getSpeed() { return this->speed; }
int Fighter::getLife() { return this->life; }
int Fighter::getX() { return this->x; }
int Fighter::getY() { return this->y; }
string Fighter::getStatus() { return this->status; }
void Fighter::setStatus(string status) {
    if (this->status != status) {
        this->status = status;
        // this->display(" change de status : '" + status + "'");
        this->display("", false);
        log(" change de status : ");
        logln(status, GREEN);
    }
}

void Fighter::display() { this->display("", true); }
void Fighter::display(string message) { this->display(message, true); }
void Fighter::display(string message, bool newLine) {
    log(this->name, BLUE);
    log(this->shortId);
    // Stats
    //log(" (");
    //log(this->attack, RED);
    //log("/");
    //log(this->defense, GREEN);
    //log("/");
    //log(this->speed, BLUE);
    //log(")");
    // Position
    //log(" (");
    //log(this->x);
    //log("x");
    //log(this->y);
    //log(")");
    // Niveau de vie
    log("[");
    log(this->life, GREEN);
    log("]");
    // Status
    //log(" [");
    //log(this->status, GREEN);
    //log("]");
    log(message);
    if (newLine) {
        logln("");
    }
}

bool Fighter::isMe(Fighter* fighter) { return this->isMe(*fighter); }
bool Fighter::isMe(Fighter fighter) { return this->id == fighter.getId(); }

bool Fighter::isHere(Fighter* fighter) { return this->isHere(*fighter); }
bool Fighter::isHere(Fighter fighter) { return this->isHere(fighter.getX(), fighter.getY()); }
bool Fighter::isHere(int x, int y) {
    return (this->x == x && this->y == y);
}

void Fighter::moveTo(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Fighter::isKO() {
    return this->life <= 0;
}

/**
 * Attaquer un autre Fighter.
 * Les dégâts sont calculés comme suit :
 *   Dégâts de base (10)
 *   Bonus d'attaque en fonction de la stat :
 *      à 30 points on double l'attaque,
 *      à 0 rien
 *      Donc DegatDeBase x StatsAttack / 30
 *   Aléa (-5/5)
 */
void Fighter::assault(Fighter* target) {
    int base = 10;
    int damage =
        // Base
        base +
        // Bonus attaque
        ((base * this->attack) / 30) +
        // Alea
        ((rand() % 10) - 5);

    target->suffer(damage);
}

/**
 * Subir des dégâts.
 * Les dégâts sont diminués en fonction de la défense et calculés comme suit :
 *   Dégâts reçus (damage)
 *   Bonus de défense en fonction de la stat :
 *      à 30 points on divise les dégâts par 2
 *      à 0 rien
 *      Donc DégâtsReçus - ((DégâtsReçus / 2) x StatsDefense / 30)
 *   Aléa (-2/3)
 */
void Fighter::suffer(int damage) {
    if (damage > 0) {
        int effective = 
            // Dégâts reçus
            (damage -
            // Bonus stats defense
            (((damage / 2) * this->defense) / 30) -
            // Alea
            ((rand() % 5) - 2)
            );
        this->life = this->life - effective;
        this->display("", false);
        log(" a subi ");
        log(effective, RED);
        log("(");
        log(damage, BLUE);
        log(")");
        logln(" points de dégâts.");
    }
}

/**
 * Comparer 2 Fighter
 * Se base sur la statistique speed pour décréter le premier.
 */
bool Fighter::compare(Fighter* a, Fighter* b) {
    return a->getSpeed() > b->getSpeed();
}
