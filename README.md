# EPSI Battle Royale project


# Configuration de l'espace de travail
La configuration par défaut est proposée pour VS Code, mais il est tout à fait possible de l'adapter pour votre IDE préféré.

* **IDE** :
  * [Visual Studio Code](https://code.visualstudio.com/)
  * [Extension C/C++](https://github.com/microsoft/vscode-cpptools)
* Définition du build dans le [.vscode/tasks.json (section build)](https://github.com/GBO/epsi-br/blob/master/.vscode/tasks.json#L24)
* Définition du debug dans le [.vscode/launch.json](https://github.com/GBO/epsi-br/blob/master/.vscode/launch.json)
* [Aide pour la configuration de Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw)


# Objectif
Produire le Bot le plus efficace pour le mesurer aux autres dans l'arène.

Produire un Bot consiste à créer les 2 fichiers :
* `MonBot.h` : la déclaration de `MonBot` qui sera placé dans le répertoire `src/fighters/headers`.
* `MonBot.cpp` : l'implémentation de `MonBot` qui sera placé dans le répertoire `src/fighters`.

Bots d'exemple :
* `Dumb` : Un Bot idiot qui attend sagement qu'on vienne le voir. Il tape seulement s'il voit quelqu'un sur sa case.
* `Ghislain` : Un Bot qui choisit une cible au hasard et la traque jusqu'au KO, puis recommence avec une autre cible.
* `Humain` (désactivé dans le `main.cpp`) : Un Bot Humain : chaque décision prise par le Bot se traduit par une demande de saisie utilisateur.

Le Bot final est attendu en dernière séance et sera mesuré à tous les autres.


# Objectif Annexe
Trouver le moyen de tricher pour produire un Bot Imbattable, parce que c'est possible.
