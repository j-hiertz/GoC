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
	bool alreadyUse;
};

Intersection* initIntersection(int, int);

void updatePosIntersection(Intersection*, int, int);

void positionToChar(char*, int, int, char);

int charToPosition(char);
