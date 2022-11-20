#ifndef BATTLEROYALE_ACTIONRESPE_H
#define BATTLEROYALE_ACTIONRESPE_H

#include <iostream>
#include <vector>

#include "Action.h"

using namespace std;

/** ActionRespe
 * Permet de mettre à jour ces stats
 */
class ActionRespe : public Action {
private:
    /** Stats */
    int attack;
    int defense;
    int speed;

public:
    /** Constructeur prenant les nouvelles stats en paramètre */
    ActionRespe(int attack, int defense, int speed);

    /** On redéfinit l'affichage */
    virtual string getDisplay();

    /** On implémente les méthodes abstraites */
    virtual bool isValid();
    virtual void perform();
};

#endif //BATTLEROYALE_ACTIONRESPE_H
