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
	inter->alreadyUse = false;

	return inter;
}

void updatePosIntersection(Intersection* inter, int x, int y) {
	inter->x = x;
	inter->y = y;
}