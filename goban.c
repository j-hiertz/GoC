#include <stdlib.h>
#include <stdio.h>
#include "goban.h"
#ifndef BOOL_H
	#define BOOL_H
	#include "boolean.h"
	#include "dessine.h"
#endif

void initPlateau(Goban* ptrGoban, int width, int height, int nbCase){

	ptrGoban->nbCase = nbCase;
	ptrGoban->width = width;
	ptrGoban->height = height;

	int espaceCase = 0;

	if(height < width) {
		espaceCase = height / (nbCase + 1);
	}
	else {
		espaceCase = width / (nbCase + 1);
	}

	Intersection ***intersections;

	intersections = malloc(nbCase * sizeof(*intersections));

	if(intersections == NULL){
		// TODO Erreur + quitter programme
	}

	for(int ligne = 0; ligne < nbCase; ligne++){
		intersections[ligne] = malloc(nbCase * sizeof(**intersections));

		if(intersections[ligne] == NULL){
			// TODO Erreur + quitter programme
		}

		int posY = espaceCase + (espaceCase * ligne);

		for(int colonne = 0; colonne < nbCase; colonne++) {
			
			int posX = espaceCase + (espaceCase * colonne);

			intersections[ligne][colonne] = initIntersection(posX, posY);

			// Différent de la première ligne du Goban
			if(colonne > 0) {
				intersections[ligne][colonne]->interGauche = intersections[ligne][colonne-1];
				intersections[ligne][colonne-1]->interDroite = intersections[ligne][colonne];
			}

			// Dernière ligne du Goban
			if(ligne > 0) {
				intersections[ligne][colonne]->interHaut = intersections[ligne-1][colonne];
				intersections[ligne-1][colonne]->interBas = intersections[ligne][colonne];
			}
		}
		
	}

	ptrGoban->intersections = intersections;

	// ============================= TEST PURPOSE =============================
	for(int ligne = 0; ligne < nbCase; ligne++){

		for(int colonne = 0; colonne < nbCase; colonne++) {
			printf("%d:%d ", intersections[ligne][colonne]->x, intersections[ligne][colonne]->y);
		}

		printf("\n");
		
	}

}

Intersection* placerPion(Goban* goban, int tour, int x, int y, int espaceCase){
	int colonne = ((x + (espaceCase /2)) / espaceCase) -1;
	int ligne = ((y + (espaceCase /2)) / espaceCase) -1;
	
	if(tour == 1) { // Pion blanc
		colorPion cp = BLANC;
		goban->intersections[ligne][colonne]->pion = initPion(BLANC, true);
	}
	else { // Pion noir
		goban->intersections[ligne][colonne]->pion = initPion(NOIR, true);
	}
	printf("Place pion case : %d:%d\n",ligne,colonne);

	return goban->intersections[ligne][colonne];
}
