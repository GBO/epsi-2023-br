#ifndef BATTLEROYALE_ACTIONRESPE_H
#define BATTLEROYALE_ACTIONRESPE_H

#include <iostream>
#include <vector>

#include "Action.h"

using namespace std;

/** ActionRespe
 * Action concrète de respécialisation
 * 
 * Requiert les nouvelles stats pour se respécialiser.
 * L'action est valide si elle n'enfreint par les règles des stats
 */
class ActionRespe : public Action {
private:
    /** Stats */
    int attack;
    int defense;
    int speed;
    int intention;

public:
    /** Constructeur prenant les nouvelles stats en paramètre */
    ActionRespe(int attack, int defense, int speed, int intention);

    /** On redéfinit l'affichage */
    virtual string getDisplay();

    /** On implémente les méthodes abstraites */
    virtual bool isValid();
    virtual void perform();
};

#endif //BATTLEROYALE_ACTIONRESPE_H
