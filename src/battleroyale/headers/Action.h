#ifndef BATTLEROYALE_ACTION_H
#define BATTLEROYALE_ACTION_H

#include <iostream>
#include <vector>

#include "Arena.h"
#include "Fighter.h"

#define AP_UNIT 3

using namespace std;

/** Action abstraite
 * Définit une action qu'un Bot peut choisir.
 * Les méthodes isValid et perform sont à implémenter dans les actions concrètes
 */
class Action {
private:
    /** Simple nom de l'action */
    string name;
    /** Cout de l'action en AP (Action Point) */
    int ap;

protected:
    /** Les informations disponibles aux héritiers pour opérer l'action */
    Arena* arena;
    vector<Fighter*> fighters;
    Fighter* fighter;

public:
    /** Constructeur simple avec le nom obligatoire */
    Action(string name, int ap);
    virtual ~Action();

    /** Accesseurs (getters) / mutateurs (setters) */
    string getName();
    int getAp();
    void setArena(Arena* arena);
    void setFighters(vector<Fighter*> fighters);
    void setFighter(Fighter* fighter);

    /** Affichage de l'action : getDisplay retourne une chaine représentant l'action et ses attributs
     * La méthode est virtual pour permettre aux descendants de la redéfinir au besoin.
     * La méthode n'est par contre pas abstraite (pas de = 0) et elle a une implémentation par défaut
     * dans le .cpp */
    virtual string getDisplay();
    /** Affichage de l'action (utilisant getDisplay) */
    void display();

    /** Les 2 méthodes abstraites (grace aux = 0) : */
    /** Retourner vrai sur l'action est valide */
    virtual bool isValid() = 0;
    /** Effectuer l'action */
    virtual void perform() = 0;
};

#endif //BATTLEROYALE_ACTION_H
