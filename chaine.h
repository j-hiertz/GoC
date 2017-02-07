#include <stdlib.h>
#include <stdio.h>
#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif

typedef struct Chaine{
	Intersection** tabIntersection;
	int liberte;
	int size;
} Chaine;

void addPionChaine(Intersection* inter);
