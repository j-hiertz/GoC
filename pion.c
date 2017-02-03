#include "dessine.h"
#include <string.h>
#include "intersection.h"

Pion *initPion(colorPion couleur, bool visible) {
	
	Pion *pion = malloc(sizeof(*pion));
	pion->couleur = couleur;
	pion->visible = visible;

	return pion;
}