#ifndef BATTLEROYALE_ACTIONATTACK_H
#define BATTLEROYALE_ACTIONATTACK_H

#include <iostream>
#include <vector>

#include "Action.h"

using namespace std;

/** ActionAttack
 * Action concrète d'Attack.
 * 
 * Demande un Fighter (cible) à la création.
 * L'attaque n'est possible que si la cible partage les mêmes coordonnées avec l'attaquant.
 **/
class ActionAttack : public Action {
private:
    /** Stockage interne du fighter pris pour cible */
    Fighter* target;
    string targetId;
    string targetName;

public:
    /** Constructeur de ActionAttack
     * @param fighter La cible de l'attaque
     */
    ActionAttack(Fighter fighter);

    /** On redéfinit l'affichage */
    virtual string getDisplay();

    /** On implémente les méthodes abstraites */
    virtual bool isValid();
    virtual void perform();
};

#endif //BATTLEROYALE_ACTIONATTACK_H
