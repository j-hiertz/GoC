#ifndef BOOL_H
	#define BOOL_H
	#include "boolean.h"
#endif

typedef enum { NOIR, BLANC} colorPion;


typedef struct Pion Pion;
struct Pion{
	colorPion couleur;
	bool visible;
};

Pion *initPion(colorPion, bool);