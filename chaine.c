#include <stdlib.h>
#include <stdio.h>
#include "chaine.h"
#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif

Chaine** chaines = NULL;
int sizeChaines = 0;

int getSize() {
	int i = 0;
	if(chaines == NULL) { return i; }
	while(chaines[i] != NULL) {
		i++;
	}
	return i;
}

int getSizeChaine(int index) {
	int i = 0;
	if(chaines[index] == NULL) { return i; }
	while(chaines[index]->tabIntersection[i] != NULL) {
		i++;
	}
	return i;
}

void createChaine(Intersection* inter) {
	int i = getSize();
	chaines[i]->tabIntersection[0] = inter;
	chaines[i]->size = 1;
	sizeChaines++;
}

int getIndexChaine(Intersection* inter) {
	for(int i = 0; i < sizeChaines; i++) {
		for(int y = 0; y < chaines[i]->size; y++) {
			if(inter = chaines[i]->tabIntersection[y]) {
				return i;
			}
		}
	}
	return -1;
}

void addToChaine(Intersection* interAdded, Intersection* interToAddTo) {
	int index = getIndexChaine(interToAddTo);
	if(index == -1) { printf("Il n'y a pas de chaine pour interToAddTo !\n"); }
	else {
		int size = getSizeChaine(index);
		chaines[index]->tabIntersection[size] = interAdded;
		printf("Normalement ajouté à la chaine n°%d !", index);
	}
}

void addPionChaine(Intersection* inter) {
	if(inter->interHaut->pion) {
		if(inter->interHaut->pion->couleur == inter->pion->couleur) {
			printf("Chaine detectee en haut, on l'y ajoute");
			addToChaine(inter, inter->interHaut);
		}
	}
}

int calculLiberte(Intersection **chaine, int longueurChaine) {

	int liberte = 0;
	int lengthUse = 0;

	Intersection** alreadyUse = malloc(1*sizeof(*alreadyUse));

	for(int i = 0; i < longueurChaine; i++) {

		bool detectLib = false;

		if(chaine[i]->interHaut != NULL && chaine[i]->interHaut->pion == NULL &&
			!checkAlreadyUse(alreadyUse, lengthUse, chaine[i]->interHaut)) {

			detectLib = true;
		}

		if(chaine[i]->interBas != NULL && chaine[i]->interBas->pion == NULL &&
			!checkAlreadyUse(alreadyUse, lengthUse, chaine[i]->interBas)) {

			detectLib = true;
		}

		if(chaine[i]->interDroite != NULL && chaine[i]->interDroite->pion == NULL &&
			!checkAlreadyUse(alreadyUse, lengthUse, chaine[i]->interDroite)) {

			detectLib = true;
		}

		if(chaine[i]->interGauche != NULL && chaine[i]->interGauche->pion == NULL &&
			!checkAlreadyUse(alreadyUse, lengthUse, chaine[i]->interGauche)) {

			detectLib = true;
		}

		if(detectLib) {
			liberte++;
			lengthUse++;
			alreadyUse = realloc(alreadyUse, lengthUse*sizeof(*alreadyUse));
		}

	}

	free(alreadyUse);

	return liberte;

}

bool checkAlreadyUse(Intersection** intersections, int taille, Intersection* inter) {

	if(taille == 0) {
		return false;
	}

	for(int i = 0; i < taille; i++) {

		// Comparaison des adresses mémoires
		if(intersections[i] == inter) {
			return true;
		}
	}

	return false;
}
