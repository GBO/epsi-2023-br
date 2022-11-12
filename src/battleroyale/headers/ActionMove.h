#ifndef BATTLEROYALE_ACTIONMOVE_H
#define BATTLEROYALE_ACTIONMOVE_H

#include <iostream>
#include <vector>

#include "Action.h"

using namespace std;

/** ActionMove
 * Se déplacer dans une direction donnée
 */
class ActionMove : public Action {
private:
    /** La direction en question */
    int x;
    int y;

public:
    /** Constructeur prenant la direction en paramètre */
    ActionMove(int x, int y);

    /** On redéfinit l'affichage */
    virtual string getDisplay();

    /** On implémente les méthodes abstraites */
    virtual bool isValid();
    virtual void perform();
};

#endif //BATTLEROYALE_ACTIONMOVE_H
