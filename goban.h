#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include <stdlib.h>
	#include <stdio.h>
	#include "intersection.h"
#endif


typedef struct Goban Goban;
struct Goban{
	int nbCase;
	int width;
	int height;
	Intersection ***intersections;
};

int getSizeCaseOccupe();

void initPlateau(Goban*, int, int, int);

bool placerPion(Goban*, Intersection*, colorPion, int, int);

bool checkPosePion(Goban*, Intersection*, colorPion);

bool checkIfPion(Goban*, int, int);

bool checkLiberte(Intersection*);

bool checkPriseChaine(Intersection*, colorPion, Intersection***, int*, bool);

bool checkAlreadyUse(Intersection*** intersections, int*, Intersection* inter);

int calculLiberte(Intersection **chaine, int longueurChaine);

void supprimerChaine(Intersection***, int*);

bool checkLiberteAllie(Intersection*, colorPion, Intersection***, int*, bool);

void reAllocAlreadyUse(Intersection***, int*);
