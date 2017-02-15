#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif

/**
 * Structure de donnée représentant le plateau de jeu
 * nbCase: Le nombre de case du plateau 9 / 13 / 19
 * width: La largeur de la fenêtre, nécessaire pour le placement des intersections
 * height: La hauteur de la fenêtre
 * sizeCaseOccuppe: Le nombre d'intersection occupée sur le Goban
 * intersections: Tableau bi-dimensionnel de pointeur de structure d'intersection
 */
typedef struct Goban Goban;
struct Goban{
	int nbCase;
	int width;
	int height;
	int sizeCaseOccuppe;
	Intersection ***intersections;
};

/**
 * Permet d'initialiser et d'allouer la mémoire à la structure Goban
 * width: La largeur de la fenêtre
 * height: La hauteur de la fenêtre
 * nbCase : Le nombre de case du Goban (9 / 13 / 19)
 */
void initPlateau(Goban* goban, int width, int height, int nbCase);


/**
 * Fonction appelé lors d'un click sur le plateau pour placer un pion
 * goban: L'adresse vers la structure goban
 * inter: L'adresse de l'intersection ou on veut placer le pion
 * color: La couleur du pion à placer
 * colonne: La colonne correspondante à l'intersection
 * ligne: La ligne correspondante à l'intersection
 */
bool placerPion(Goban* goban, Intersection* inter, colorPion color, int colonne, int ligne);


/**
 * Vérifie si il est possible de placer un pion à cet endroit
 * goban: L'adresse vers la structure goban
 * inter: L'adresse de l'intersection ou on veut placer le pion
 * color: La couleur du pion à placer
 */
bool checkPosePion(Goban* goban, Intersection* inter, colorPion color);

/**
 * Vérifie si l'intersection à une liberté directe,
 * c'est à dire qu'une case autour est libre
 * inter: L'adresse de l'intersection que l'on souhaite verifier
 */
bool checkLiberte(Intersection* inter);

/**
 * Vérifie si on prend une chaine adverse de manière 
 * recursive en supprimant sa dernière liberté
 * inter: L'adresse de l'intersection que l'on souhaite verifier
 * color: La couleur de la chaine adverse
 * alreadyUse: L'adresse d'un tableau de pointeur d'Intersection déjà utilisée dans la vérification
 * sizeUsed: La taille du précedent tableau
 * prise: Un boolean qui définit si la chaine est prise ou non
 */
bool checkPriseChaine(Intersection* inter, colorPion color, Intersection*** alreadyUse, int* sizeUsed, bool prise);

/**
 * Vérifie si l'intersection qu'on souhaite vérifiée à déjà été utilisée
 * alreadyUse: L'adresse d'un tableau de pointeur d'Intersection déjà utilisée dans la vérification
 * sizeUsed: La taille du précedent tableau
 * inter: L'intersection à vérifier
 */
bool checkAlreadyUse(Intersection*** alreadyUse, int* sizeUsed, Intersection* inter);


/**
 * Supprime les pions d'une chaine prise en désallouant la mémoire
 * chaine: L'adresse d'un tableau de pointeur d'Intersection représentant les pions à supprimer
 * sizeChaine: La taille du précedent tableau
 */
void supprimerChaine(Intersection*** chaine, int* sizeChaine);

/**
 * Vérifie de manière recursive si une chaine alliée voisine possède une liberté
 * inter: L'adresse de l'intersection à vérifier
 * color: La couleur de l'intersection à verifier
 * alreadyUse: L'adresse d'un tableau de pointeur d'Intersection déjà utilisée dans la vérification
 * sizeUsed: La taille du précedent tableau
 * liberte: Un boolean qui définit si la chaine alliée possède une liberté
 */
bool checkLiberteAllie(Intersection* inter, colorPion color, Intersection*** alreadyUse, int* sizeUsed, bool liberte);

/**
 * Réalloue la mémoire du tableau d'intersection à 1 pour verifier les chaines suivantes
 * alreadyUse: L'adresse d'un tableau de pointeur d'Intersection à réallouer
 * sizeUsed: La taille du précedent tableau
 */
void reAllocAlreadyUse(Intersection*** alreadyUse, int* sizeUsed);