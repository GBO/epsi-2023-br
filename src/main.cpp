#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Dumb.h"
#include "Ghislain.h"
#include "Humain.h"
// #include "Thanos.h"

#include "log.h"

using namespace std;

/** Structure des scores */
struct Score {
    string bot;
    int score;
};
int nbexaequo = 0;
vector<Score> scores;

/** Nombre de tours / bots */
int nbTest, nbBot;

/** Fonction Fabrique de Bot & initialisation des scores */
FighterBot* recruit(string prenom) {
    // On commence par fabriquer un Bot à partir de son prenom
    FighterBot* bot;
    if (prenom == "Dumb") { bot = new Dumb; }
    else if (prenom == "Ghislain") { bot = new Ghislain; }
    //else if (prenom == "Thanos") { bot = new Thanos; }
    else { bot = new Dumb(prenom); }
    // On gère les scores (y a-t-il déjà une entrée de score pour ce prénom)
    bool found = false;
    for (Score score: scores) {
        if (score.bot == prenom) { found = true; break; }
    }
    if (!found) { scores.push_back(Score{ prenom, 0 }); }
    /// On retourne le Bot produit
    return bot;
}

int main(int argc, char *argv[])
{
    loginit();
    srand(time(NULL));

    logln("EPSI Battle Royale", BLUE);

    log("Combien de tours ? ", GREEN);
    if (argc > 1) {
        nbTest = stoi(argv[1]);
        logln(nbTest);
    } else {
        cin >> nbTest;
    }
    log("Combien de chaque bot ? ", GREEN);
    if (argc > 2) {
        nbBot = stoi(argv[2]);
        logln(nbBot);
    } else {
        cin >> nbBot;
    }
    logln("");

    // Boucle des tour : un BR à chaque tour
    BattleRoyale* br;
    for (int i = 0; i < nbTest; i++) {
        br = new BattleRoyale(10, 1000, nbTest == 1);
        // Boucle des Bots : Création de nbBot de chaque type
        for (int j = 0; j < nbBot; j++) {
            string botname;
            ifstream istrm("bots.txt");
            while (getline(istrm, botname)) {
                // On se laisse la possibilité de commenter une ligne :
                // le bot est ignoré si la ligne commence par un #
                if (botname[0] != '#') {
                    br->recruit(recruit(botname));
                }
            }
        }
        if (nbTest == 1) {
            log("Appuyez sur entrée pour démarrer . . . ", BLUE);
            cin.ignore();
        }
        br->run();

        for (Fighter fighter : br->getArena().get()) {
            if (!fighter.isKO()) {
                for (int i = 0; i < scores.size(); i++) {
                    if (fighter.getName() == scores[i].bot) {
                        scores[i].score++;
                        break;
                    }
                }
                break;
            }
        }
        if (br->getWinner() == nullptr) {
            nbexaequo++;
        }

        delete br;
    }

    logln("");
    logln("");
    logln("");
    logln("EX AEQUO: " + to_string(nbexaequo), GREEN);
    for (int i = 0; i < scores.size(); i++) {
        logln(scores[i].bot + ": " + to_string(scores[i].score), GREEN);
    }

    return 0;
}
