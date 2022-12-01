#include <algorithm>
#include <iostream>
#include <vector>

#include "Action.h"
#include "ActionRespe.h"
#include "BattleRoyale.h"
#include "Fighter.h"
#include "log.h"

using namespace std;

/** Les constructeurs et leur valeurs par défaut */
BattleRoyale::BattleRoyale(int size) : BattleRoyale(size, 1000, false) {}
BattleRoyale::BattleRoyale(int size, int roundLimit) : BattleRoyale(size, roundLimit, false) {}
BattleRoyale::BattleRoyale(int size, int roundLimit, bool pause) {
    this->size = size;
    this->roundLimit = roundLimit;
    this->pause = pause;
    this->arena = new Arena(size, size);
}

/** Le desctructeur nettoie le this->arena et tous les bots !! */
BattleRoyale::~BattleRoyale() {
    delete this->arena;
    for (FighterBot* bot : this->bots) {
        delete bot;
    }
}

Arena BattleRoyale::getArena() { return (*this->arena); }
vector<FighterBot*> BattleRoyale::getKos() { return this->kos; }
FighterBot* BattleRoyale::getWinner() { return this->winner; }

void BattleRoyale::recruit(FighterBot* bot) {
    Fighter* fighter = bot->init();
    this->fighters.push_back(fighter);
    // On positionne aléatoirement le Fighter dans l'arène
    fighter->moveTo(rand() % this->size, rand() % this->size);
    this->arena->add(fighter);
    this->bots.push_back(bot);
}

int BattleRoyale::nbFighterAlive() {
    int count = 0;
    for (int i = 0; i < this->bots.size(); i++) {
        if (this->bots[i]->getLife() > 0) {
            count++;
        }
    }
    return count;
}

void BattleRoyale::run() {
    this->winner = nullptr;
    int round = 1;
    // On fait autant de round qu'il est possible d'en faire (le roundLimit est notre limite)
    while (this->nbFighterAlive() > 1 && round < this->roundLimit) {
        logln("");
        // Effacement de la console...
        cout << "\x1B[2J\x1B[H";
        log("#####  ROUND ", GREEN);
        log(round, WHITE);
        logln("  #####", GREEN);
        // Affichage de l'arène avant le ROUND
        this->arena->display();
        // On joue le ROUND
        this->runRound(round);
        // Enfin : Incrémentons du round...
        round++;
        if (this->pause) {
            // ...Puis petite pause pour l'être humain qui regarde.
            log("Appuyez sur entrée . . . ", BLUE);
            cin.ignore();
        }
    }

    // Déclaration de victoire du dernier survivant
    logln("");
    logln("");
    logln("#####  FIN DE LA BATAILLE !  #####", GREEN);
    logln("");
    for (FighterBot* bot : this->bots) {
        if (!bot->isKO()) {
            if (this->nbFighterAlive() == 1) {
                bot->display("", false);
                logln(" est déclaré vainqueur en " + to_string(round-1) + " rounds !!", BLUE);
                this->winner = bot;
                break;
            } else {
                bot->display("", false);
                logln(" est déclaré vainqueur ex aequo", BLUE);
            }
        }
    }
    logln("");
    logln("");
}

void BattleRoyale::runRound(int round) {
    // On retrie notre liste de bot à chaque tour :
    random_shuffle(this->fighters.begin(), this->fighters.end());
    sort(this->fighters.begin(), this->fighters.end(), Fighter::compare);

    for (Fighter* fighter : this->fighters) {
        // Ne jouent que les fighters non KO
        if (!fighter->isKO()) {
            this->runRoundFighter(round, fighter);
        }
    }
}

void BattleRoyale::runRoundFighter(int round, Fighter* fighter) {
    // On retrouve le Bot :
    FighterBot* bot = nullptr;
    for (FighterBot* b : this->bots) {
        if (b->getId() == fighter->getId()) {
            bot = b;
            break;
        }
    }
    log("# ", GREEN);
    // Demandons à notre bot ce qu'il veut faire . . . 
    Action* action = bot->choose(this->getArena());
    // Il renvoie nullptr : il ne veut visiblement rien faire
    if (action == nullptr) {
        bot->display(" ne fait rien . . .");
    } else {
        bot->display(" choisit " + action->getDisplay());
        this->doAction(fighter, bot, action);
        // On sort les Fighter KO de l'arène
        this->cleanArena(round, fighter, bot);
    }
}

void BattleRoyale::doAction(Fighter* fighter, FighterBot* bot, Action* action) {
    // On construit la liste des fighters non KO
    vector<Fighter*> alive;
    for (Fighter* f : this->fighters) {
        if (!f->isKO()) {
            alive.push_back(f);
        }
    }
    // On remplit l'action avec tout le nécessaire à son execution
    action->setArena(this->arena);
    action->setFighters(alive);
    action->setFighter(fighter);
    // On vérifie que le choix est valide
    if (action->isValid()) {
        // Et on l'exécute !
        action->perform();
    } else {
        // ...Sinon, on indique qu'on exécutera pas l'action
        logln("Action interdite !!", RED);
    }
    delete action;
}

void BattleRoyale::cleanArena(int round, Fighter* fighter, FighterBot* fighterbot) {
    for (FighterBot* bot : this->bots) {
        // Les bots KO et toujours dans l'arène
        if (bot->isKO() && this->arena->contains(bot->getFighter())) {
            // ...sont retirés
            bot->display("", false);
            logln(" est évacué de l'arène...", RED);
            this->arena->remove(bot->getFighter());
            // Gestion de la liste des KO
            bot->setKoRound(round);
            this->kos.push_back(bot);
            // On levelup le Fighter ayant provoqué ce KO
            this->levelup(fighter, fighterbot);
        }
    }
}

void BattleRoyale::levelup(Fighter* fighter, FighterBot* bot) {
    // On soigne la moitié des dégats reçus
    fighter->heal((100 - fighter->getLife()) / 2);
    // On soigne la moitié des dégats reçus
    fighter->levelup();
    // On demande le levelup au bot
    ActionRespe* respe = bot->levelup();
    // Par défaut, on augmente les stats : +2 +2 +1
    if (respe == nullptr) {
        respe = new ActionRespe(fighter->getAttack() + 2, fighter->getDefense() + 2, fighter->getSpeed() + 1);
    }
    this->doAction(fighter, bot, respe);
}


