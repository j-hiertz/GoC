#ifndef GOBAN_H
	#define GOBAN_H
	#include "goban.h"
#endif

/**
 * On sauvegarde le fichier de la partie si celui-ci n'est pas encore initialisé
 * On créé le repertoire save si il n'existe pas encore
 * goban: L'adresse de la structure Goban
 * file: Le pointeur vers le fichier qu'on souhaite enregistrer
 */
FILE* saveGame(Goban* goban, FILE* file);

/**
 * Ajout d'un coup dans le fichier
 * file: le pointeur vers le fichier dans lequel on enregistre les données
 * colonne: La colonne du coup joué
 * ligne: La ligne du coup joué
 * color: La couleur du coup joué
 */
void updateSGF(FILE* file, int colonne, int ligne, colorPion color);


/**
 * Permet de créer une partie en fonction d'un fichier sgf
 * file: Le pointeur vers le fichier ouvert pour charger la partie
 * goban: Le pointeur vers la structure goban à remplir
 * tour: L'adresse du tour représentant le prochain coup à jouer définit avec la dernière entrée du fichier
 */
void createGameFromFile(FILE* file, Goban* goban, colorPion* tour);


/**
 * Indique le score de la partie dans le fichier
 * file: Le pointeur vers le fichier ouvert
 * str: La chaine répresentant le score
 */
void endGameSGF(FILE* file, char* str);

/**
 * Permet de récupérer la taille du plateau pour une partie chargée
 * file: Le pointeur vers le fichier chargé
 */
int getNbCaseFromFile(FILE* file);