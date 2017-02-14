#include <stdlib.h>
#include <stdio.h>
#include "intersection.h"

Intersection* initIntersection(int x, int y) {

	Intersection *inter = malloc(sizeof(*inter));

	if(inter == NULL) {
		exit(EXIT_FAILURE);
	}
	
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