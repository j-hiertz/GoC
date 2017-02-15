#include <stdlib.h>
#include <stdio.h>
#include "../../header/intersection.h"

Pion *initPion(colorPion couleur) {

	Pion *pion = malloc(sizeof(*pion));

	if(pion == NULL) {
		exit(EXIT_FAILURE);
	}

	pion->couleur = couleur;

	return pion;
}