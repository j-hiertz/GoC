#include "dessine.h"
#include <string.h>
#include "intersection.h"

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