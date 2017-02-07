#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
	#include "file.h"
#endif

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

int calculLiberte(Intersection**, int);

bool checkAlreadyUse(Intersection**, int, Intersection*);