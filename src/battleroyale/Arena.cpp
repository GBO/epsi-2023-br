#include <iostream>

#include "Arena.h"
#include "log.h"

using namespace std;

Arena::Arena(int width, int height) {
    this->width = width;
    this->height = height;
}

int Arena::getWidth() { return this->width; }
int Arena::getHeight() { return this->height; }

void Arena::add(Fighter* fighter) {
    fighters.push_back(fighter);
}

bool Arena::contains(Fighter* fighter) { return this->contains(*fighter); }
bool Arena::contains(Fighter fighter) {
    for (Fighter* current : this->fighters) {
        if (current->isMe(fighter)) {
            return true;
        }
    }
    return false;
}

void Arena::remove(Fighter* fighter) {
    unsigned int i = 0;
    while (i < this->fighters.size()) {
        if (this->fighters[i] == fighter) {
            this->fighters.erase(this->fighters.begin() + i);
        } else {
            i++;
        }
    }
}

void Arena::display() {
    string maCase;
    for (int j = 0; j < this->width; j++) {
        log("|", BLUE);
        for (int i = 0; i < this->height; i++) {
            maCase = "";
            for (unsigned int k = 0; k < this->fighters.size() && maCase.size() < 3; k++) {
                if (this->fighters[k]->isHere(i, j)) {
                    maCase += this->fighters[k]->getName()[0];
                }
            }

            if (maCase.size() < 1) {
                maCase += "   ";
            } else if (maCase.size() < 2) {
                maCase += "  ";
            } else if (maCase.size() < 3) {
                maCase += " ";
            }

            log(maCase);
            log("|", BLUE);
        }
        logln("");
    }
}

/** Toutes les déclinaisons de la méthode get pour récupérer des Fighters */
vector<Fighter> Arena::get() { return this->get(0, 0, this->width, this->height); }
vector<Fighter> Arena::get(Fighter* fighter) { return this->get(*fighter); }
vector<Fighter> Arena::get(Fighter fighter) { return this->get(fighter.getX(), fighter.getY()); }
vector<Fighter> Arena::get(int x, int y) { return this->get(x, y, x, y); }
vector<Fighter> Arena::get(int xmin, int ymin, int xmax, int ymax) {
    vector<Fighter> result;
    for (unsigned int k = 0; k < this->fighters.size(); k++) {
        if (this->fighters[k]->getX() >= xmin && this->fighters[k]->getX() <= xmax
        &&  this->fighters[k]->getY() >= ymin && this->fighters[k]->getY() <= ymax) {
            result.push_back(*(this->fighters[k]));
        }
    }
    return result;
}

vector<Fighter> Arena::getById(string id) {
    vector<Fighter> result;
    for (unsigned int k = 0; k < this->fighters.size(); k++) {
        if (this->fighters[k]->getId() == id) {
            result.push_back(*(this->fighters[k]));
        }
    }
    return result;
}
