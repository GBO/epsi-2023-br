#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Dumb.h"
#include "Ghislain.h"
#include "Ghislain2.h"
#include "Humain.h"
// #include "Thanos.h"

#include "Abdoulaye.h"
#include "Antoine.h"
#include "Baptiste.h"
#include "Fabien.h"
#include "Guillaume.h"
#include "JoJo.h"
#include "Jq.h"
#include "Maawox.h"
#include "Marin.h"
#include "Matteo.h"
#include "MatthieuH.h"
#include "Quentin.h"
#include "QuentinV.h"
#include "Rambaud.h"
#include "Rosaline.h"
#include "Say_O_Lit.h"
#include "SimonP.h"
#include "Simsim_miamsmiams_grrrt.h"
#include "Sys.h"
#include "Tom.h"
#include "Viko.h"

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
    else if (prenom == "Ghislain2") { bot = new Ghislain2; }
    else if (prenom == "Humain") { bot = new Humain; }
    // else if (prenom == "Thanos") { bot = new Thanos; }

    else if (prenom == "Abdoulaye") { bot = new Abdoulaye; }
    else if (prenom == "Antoine") { bot = new Antoine; }
    else if (prenom == "Baptiste") { bot = new Baptiste; }
    else if (prenom == "Fabien") { bot = new Fabien; }
    else if (prenom == "Guillaume") { bot = new Guillaume; }
    else if (prenom == "JoJo") { bot = new JoJo; }
    else if (prenom == "Jq") { bot = new Jq; }
    else if (prenom == "Maawox") { bot = new Maawox; }
    else if (prenom == "Marin") { bot = new Marin; }
    else if (prenom == "Matteo") { bot = new Matteo; }
    else if (prenom == "MatthieuH") { bot = new MatthieuH; }
    else if (prenom == "Quentin") { bot = new Quentin; }
    else if (prenom == "QuentinV") { bot = new QuentinV; }
    else if (prenom == "Rambaud") { bot = new Rambaud; }
    else if (prenom == "Rosaline") { bot = new Rosalyne; }
    else if (prenom == "Say_O_Lit") { bot = new Say_O_Lit; }
    else if (prenom == "SimonP") { bot = new SimonP; }
    else if (prenom == "Simsim_miamsmiams_grrrt") { bot = new Simsim_miamsmiams_grrrt; }
    else if (prenom == "Sys") { bot = new Sys; }
    else if (prenom == "Tom") { bot = new Tom; }
    else if (prenom == "Viko") { bot = new Viko; }
    else { cout << "Il manque " << prenom << endl; }
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
