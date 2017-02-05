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

bool placerPion(FILE* file, Goban* goban, Intersection* intersection, int tour, int colonne, int ligne){	

	if(checkPosePion(goban, intersection, tour)){

		char coupStr[6];
	
		if(tour == 1) { // Pion noir
			intersection->pion = initPion(NOIR, true);
			positionToChar(coupStr, colonne, ligne, 'B');
		}
		else { // Pion blanc
			intersection->pion = initPion(BLANC, true);
			positionToChar(coupStr, colonne, ligne, 'W');
		}

		printf("Place pion case : %d:%d\n",ligne,colonne);

		updateSGF(file, coupStr);

		return true;
	}

	return false;
}


bool checkPosePion(Goban* goban, Intersection* intersection, int tour) {
	// TODO : Enregistrement du pion dans l'intersection correspondante

	// Etape 1 : On vérifie que la case est libre
	if(intersection->pion) {
		printf("Un pion est déjà présent sur la case %p\n", intersection);
		return false;
	}
	// couleur = intersection->pion->couleur;
	/*if(checkLiberte(intersection)) {
		return 1;
	} else {
		//if(intersection->interHaut->pion->couleur == couleur || intersection->interBas->pion->couleur == couleur || intersection->interGauche->pion->couleur == couleur || intersection->interDroite->pion->couleur == couleur)
	}*/

	return true;
}

/*
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

// /home/jordan/GoC/save/game_2017_02_05_16_25_33.sgf
void createGameFromFile(FILE* file, Goban *goban) {
	printf("%d : %d\n", charToPosition('g'), charToPosition('e'));
	
	char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int i = 0;

    int ligne;
    int colonne;

    while ((read = getline(&line, &len, file)) != -1) {

        if(i > 1) {
        	printf("Couleur : %c Colonne : %c Ligne : %c\n", line[0], line[2], line[3]);

        	colonne = charToPosition(line[2]);
        	ligne = charToPosition(line[3]);

        	Intersection* intersection = goban->intersections[ligne][colonne];

        	if(line[0] == 'B') {
        		intersection->pion = initPion(NOIR, true);
        	}
        	else {
        		intersection->pion = initPion(BLANC, true);
        	}
        }

        i++;
    }
}