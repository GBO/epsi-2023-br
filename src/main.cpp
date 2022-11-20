#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Dumb.h"
#include "Ghislain.h"
#include "Humain.h"

#include "log.h"

using namespace std;

/** Structure des scores */
struct score {
    string bot;
    int score;
};
int nbexaequo = 0;
vector<score> scores;

/** Nombre de tours / bots */
int nbTest = 1;
int nbBot = 1;

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
            // N'ajouter un Humain que lorsqu'il n'y a qu'un seul tour et bot
            // if (nbTest == 1 && nbBot == 1) {
            //     br->recruit(new Humain);
            //     if (i == 0 && j == 0) { scores.push_back(score{ "Humain", 0 }); }
            // }
            br->recruit(new Dumb);
            if (i == 0 && j == 0) { scores.push_back(score{ "Dumb", 0 }); }
            br->recruit(new Ghislain);
            if (i == 0 && j == 0) { scores.push_back(score{ "Ghislain", 0 }); }

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
