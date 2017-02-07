#include <stdlib.h>
#include <stdio.h>
#include "chaine.h"
#ifndef INTERSECTION_H
	#define INTERSECTION_H
	#include "intersection.h"
#endif

Chaine** chaines = NULL;

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
}

int getIndexChaine(Intersection* inter) {
	int size = getSize();
	for(int i = 0; i < size; i++) {
		int sizeChaine = getSizeChaine(i);
		for(int y = 0; y < sizeChaine; y++) {
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
	printf("Bonjour %d!\n", inter->pion->couleur);
	//if (inter->interHaut->pion) {}
	if(inter->interHaut->pion) {
		if(inter->interHaut->pion->couleur == inter->pion->couleur) {
			printf("Chaine detectee en haut, on l'y ajoute");
			addToChaine(inter, inter->interHaut);
		}
	}
}
