#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif

typedef struct Goban Goban;
struct Goban{
	int nbCase;
	int width;
	int height;
	Intersection ***intersections;
};

void initPlateau(Goban*, int, int, int);

bool placerPion(Goban*, Intersection*, int, int, int);

bool checkPosePion(Goban*, Intersection*, int);