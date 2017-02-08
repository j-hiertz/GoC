#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif
#include "file.h"

typedef struct Goban Goban;
struct Goban{
	int nbCase;
	int width;
	int height;
	Intersection ***intersections;
};

void initPlateau(Goban*, int, int, int);

bool placerPion(FILE*, Goban*, Intersection*, int, int, int);

bool checkPosePion(Goban*, Intersection*, int);

void createGameFromFile(FILE*, Goban*);

int calculLiberte(Intersection **chaine, int longueurChaine);
bool checkAlreadyUse(Intersection** intersections, int taille, Intersection* inter);