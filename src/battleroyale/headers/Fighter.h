#ifndef BATTLEROYALE_FIGHTER_H
#define BATTLEROYALE_FIGHTER_H

#include <iostream>

using namespace std;

/** Fighter
 * Le combattant de base */
class Fighter {
private:
    /** Nom et identifiants du combattant */
    string name;
    string id;
    string shortId;

    // Statisitques réglables par les héritiers
    /** Niveau d'attaque utilisée pour calculer les dégâts dans la méthode `assault` */
    int attack;
    /** Niveau de défense utilisée pour minimiser les dégâts dans la méthode `suffer` */
    int defense;
    /** Niveau de vitesse utilisée pour comparer (trier) les Fighter entre eux dans la méthode `compare` */
    int speed;
    /** Niveau d'intention utiliser pour enchainser des actions */
    int intention;

    /** Attributs gérés par le moteur de jeu */

    /** Niveau de vie du combattant */
    int life;
    /** Level du Fighter permettant de calculer le max de stats possibles */
    int level;
    /** Nombre d'ActionPoint disponibles */
    int ap;

    /** Position */
    int x, y;

    /** Le statut (moyen de communication ?) */
    string status;

public:
    /** Constructeurs */
    Fighter(string name, int attack, int defense, int speed, int intention);
    virtual ~Fighter();

    /** Accesseurs (getters) / mutateurs (setters) */
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
    void setStats(int attack, int defense, int speed, int intention);
    string getStatus();
    void setStatus(string status);

    /** Affichage simple */
    void display();
    /** Affichage suivi d'un message */
    void display(string message);
    /** Affichage suivi d'un message avec option nouvelle ligne ou non */
    void display(string message, bool newLine);

    /** Test sur la position */
    bool isHere(int x, int y);
    bool isHere(Fighter fighter);
    bool isHere(Fighter* fighter);

    /** Test d'identité : pour savoir si le Fighter en paramètre est le même que this
     * La comparaison se fera sur l'ID */
    bool isMe(Fighter* fighter);
    bool isMe(Fighter fighter);

    /** Déplacer le Fighter à la position cible */
    void moveTo(int x, int y);

    /** Indiquer si le Fighter est KO ou pas */
    bool isKO();

    /** Méthode de comparaison de Fighter : basée sur la rapidité du Fighter
     * La méthode est statique : elle peut être invoquée sans instance associée.
     * C'est une contrainte de la fonction sort utilisée dans BattleRoyale */
    static bool compare(Fighter* a, Fighter* b);

    /** Attaquer et subir des dégâts */
    void assault(Fighter* fighter);
    void suffer(int damage);
    /** Recevoir du soin */
    void heal(int damage);
    /** Incrémenter le niveau */
    void levelup();
    /** Gestion des AP : init en début de tour */
    void initAp();
    /** Consommation à chaque action */
    void consumeAp(int ap);
};

#endif //BATTLEROYALE_FIGHTER_H
