#ifndef PION_H
	#define PION_H
	#include "pion.h"
#endif

/**
 * Structure représentant une Intersection sur laquelle on peut placer un pion
 * Elle est composée de coordonnée X,Y pour son emplacement,
 * de 4 pointeurs vers les intersections voisines 
 * (sur les bords le pointeur est initialisé à NULL)
 * Un boolean qui indique si l'intersection à déjà été prise
 * en compte dans le calcul des points
 */
typedef struct Intersection Intersection;
struct Intersection{
	int x;
	int y;
	Pion* pion;
	Intersection* interHaut;
	Intersection* interDroite;
	Intersection* interBas;
	Intersection* interGauche;
	bool alreadyUse;
};


/**
 * Initialise une intersection en allouant la mémoire et
 * retourne le pointeur vers l'adresse mémoire.
 * x: La coordonnée sur l'axe X
 * y: La coordonnée sur l'axe Y
 */
Intersection* initIntersection(int x, int y);

/**
 * Met à jour la position d'une intersection après un 
 * redimensionnement de la fenêtre.
 * inter: L'adresse vers l'intersection à modifier
 * x: La nouvelle coordonnée sur l'axe X
 * y: La nouvelle coordonnée sur l'axe Y
 */
void updatePosIntersection(Intersection* inter, int x, int y);