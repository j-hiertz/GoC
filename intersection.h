#ifndef PION_H
	#define PION_H
	#include "pion.h"
#endif

typedef struct Intersection Intersection;
struct Intersection{
	int x;
	int y;
	Pion* pion;
	Intersection* interHaut;
	Intersection* interDroite;
	Intersection* interBas;
	Intersection* interGauche;
};

Intersection* initIntersection(int, int);
