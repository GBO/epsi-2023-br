#ifndef BATTLEROYALE_ARENA_H
#define BATTLEROYALE_ARENA_H

#include <iostream>
#include <vector>

#include "Fighter.h"

using namespace std;

/** Arena
 * L'arène où tout se déroule, et contenant nos Fighter
 */
class Arena {
private:
    /** Liste interne de Fighter */
    vector<Fighter*> fighters;
    /** Taille de l'arène */
    int width;
    int height;

public:
    /** Constructeur obligeant à spécifier une taille */
    Arena(int width, int height);

    /** Accesseurs (getters) / mutateurs (setters) */
    int getWidth();
    int getHeight();

    /** Ajouter un Fighter dans l'arène */
    void add(Fighter* fighter);

    /** Retourner vrai si un Fighter est dans l'arene ou pas */
    bool contains(Fighter* fighter);
    bool contains(Fighter fighter);

    /** Supprimer Fighter de l'arène */
    void remove(Fighter* fighter);

    /** Défensivement, l'arene n'expose que des Fighter et non des Fighter* */
    /** On ne pourra manipuler que des copies des Fighters originaux. */

    /** Retourne tous les Fighters dans l'Arena */
    vector<Fighter> get();
    /** Retourne tous les Fighters au même emplacement que fighter */
    vector<Fighter> get(Fighter* fighter);
    vector<Fighter> get(Fighter fighter);
    /** Retourne tous les Fighters en x,y */
    vector<Fighter> get(int x, int y);
    /** Retourne tous les Fighters dans le périmètre */
    vector<Fighter> get(int xmin, int ymin, int xmax, int ymax);

    /** Retourne la liste de Fighter ayant l'ID fourni */
    vector<Fighter> getById(string id);

    /** Affichage de l'arène */
    void display();
};

#endif //BATTLEROYALE_ARENA_H
