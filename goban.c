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

int checkLiberte(Intersection* inter) {
	if(inter->interHaut->pion == NULL) { return true; }
	if(inter->interBas->pion == NULL) { return true; }
	if(inter->interGauche->pion == NULL) { return true; }
	if(inter->interDroite->pion == NULL) { return true; }

	return false;
}

bool checkPosePion(Goban* goban, Intersection* intersection, int tour) {
	// TODO : Enregistrement du pion dans l'intersection correspondante

	// Etape 1 : On vérifie que la case est libre
	if(intersection->pion) {
		printf("Un pion est déjà présent sur la case %p\n", intersection);
		return false;
	}

	// Etape 2 : On récupère la couleur jouée
	colorPion color;
	if(tour == 1) { color = NOIR; }
	else { color = BLANC; }

	// Etape 3 : On regarde si le pion a AU MOINS UNE liberté, sinon on regarde si il prend un autre pion/chaine
	if(!checkLiberte(intersection)) { printf("PAS DE LIBERTE\n"); return false; }

	return true;
}



bool checkLiberteRecusif(Intersection* inter) {
	int verif = false;
	if(checkLiberte(inter)) {
		verif = true;
	} else if (  1 ) {
		verif = checkLiberteRecusif(inter);
	} else {
		verif = 0;
	}

	return verif;
}

// /home/jordan/GoC/save/game_2017_02_08_18_20_02.sgf
void createGameFromFile(FILE* file, Goban *goban) {

	char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int i = 0;

    int ligne;
    int colonne;

    fseek(file, 0, SEEK_SET);

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
