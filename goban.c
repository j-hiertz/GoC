#include <stdlib.h>
#include <stdio.h>
#include "goban.h"

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
}

/*
int checkPosePion(Goban* goban, Intersection* intersection) {
	// TODO : Enregistrement du pion dans l'intersection correspondante
	// couleur = intersection->pion->couleur;
	if(checkLiberte(intersection)) {
		return 1;
	} else {
		//if(intersection->interHaut->pion->couleur == couleur || intersection->interBas->pion->couleur == couleur || intersection->interGauche->pion->couleur == couleur || intersection->interDroite->pion->couleur == couleur)
	}
}

int checkLiberte(Intersection* inter) {
	if(intersection->interHaut == NULL || intersection->interBas == NULL || intersection->interDroite == NULL || intersection->interGauche != NULL) {
		return 1;
	} else {
		return 0;
	}
}

int checkLiberteRecusif(Intersection* inter) {
	int verif = 0;
	if(checkLiberte(inter)) {
		verif = 1;
	} else if (  On check si il y a une pion de même couleur à côté et true si c'est le cas  ) {
		verif = checkLiberteRecusif(inter);
	} else {
		verif = 0;
	}

	return verif;
}
*/
