#ifndef BATTLEROYALE_ACTIONATTACK_H
#define BATTLEROYALE_ACTIONATTACK_H

#include <iostream>
#include <vector>

#include "Action.h"

using namespace std;

/** ActionAttack
 * Attaquer un Fighter
 **/
class ActionAttack : public Action {
private:
    /** Stockage interne du fighter pris pour cible */
    Fighter* target;
    string targetId;
    string targetName;

public:
    /** Constructeur avec fighter en paramètre */
    ActionAttack(Fighter fighter);

    /** On redéfinit l'affichage */
    virtual string getDisplay();

    /** On implémente les méthodes abstraites */
    virtual bool isValid();
    virtual void perform();
};

#endif //BATTLEROYALE_ACTIONATTACK_H
