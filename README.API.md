# EPSI Battle Royale project



# Action
## Action générique
Classe de base des actions que les `Bot` doivent choisir représentée par :
* `string nom` : Le nom de l'action.
* **V4** `int ap` : Le coût en Action Point de l'action.

Ce composant porte les règles d'exécution d'une `Action` :
* Une méthode `isValid` permet de vérifier la validité de l'action (dépendant de l'action en question).
* Une méthode `perform` permet d'effectuer l'action.

Les paramètres des actions seront fournies par le constructeur à la création de l'action.

## ActionAttack
Action d'attaque d'une cible (`fighter`).

L'attaque est valide si le l'attaquant et sa cible sont aux même coordonnées.

## ActionMove
Action de déplacement dans une direction donnée (`x` et `y`).

Seule le signe des coordonnées fournies est conservées : si `x` vaut `12`, c'est la direction `+1` qui sera conservée, si `x` vaut `-8000`, c'est la direction `-1` qui sera conservée.

Le déplacement est valide si le fighter reste dans l'arène.

## ActionRespe
Action de respécialisation, redéfinition des stats (`attack`, `defense`, `speed`, **V4** `intention`).

Le respécialisation est valide si les stats respectent les règles des statistiques :
* Elles sont toutes supérieures ou égales à 0.
* La somme des stats ne dépasse pas le maximum (**V3** pour le level du `Fighter`).

# BattleRoyale

# Arena

# Fighter

# FighterBot

