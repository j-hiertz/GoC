#include <stdlib.h>
#include <stdio.h>
#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif

typedef struct Chaine{
	Intersection** tabIntersection;
} Chaine;

void addPionChaine(Intersection* inter);
