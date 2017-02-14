#include "dessine.h"
#include <string.h>
#include "intersection.h"

Pion *initPion(colorPion couleur) {

	Pion *pion = malloc(sizeof(*pion));

	pion->couleur = couleur;

	return pion;
}
