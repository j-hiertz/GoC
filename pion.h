#ifndef BOOL_H
	#define BOOL_H
	#include "boolean.h"
#endif

typedef enum { NOIR, BlANC} color;


typedef struct Pion pion;
struct Pion{
	color couleur;
	bool visible;
};

Pion* initPion(color);