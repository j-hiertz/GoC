#include "dessine.h"
#include <string.h>
#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif

Intersection* initIntersection(int x, int y) {

	Intersection *inter = malloc(sizeof(*inter));
	inter->x = x;
	inter->y = y;
	inter->pion = NULL;
	inter->interHaut = NULL;
	inter->interDroite = NULL;
	inter->interBas = NULL;
	inter->interGauche = NULL;

	return inter;
}

void updatePosIntersection(Intersection* inter, int x, int y) {
	inter->x = x;
	inter->y = y;
}

void positionToChar(char* coupStr, int colonne, int ligne, char couleurPion) {

	char l = ligne + 97;
	char c = colonne + 97;

	sprintf(coupStr, "%c[%c%c];", couleurPion, c, l);
}

int charToPosition(char c) {
	return c - 97;
}
