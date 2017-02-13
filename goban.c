#include <stdlib.h>
#include <stdio.h>
#include "goban.h"
#ifndef BOOL_H
	#define BOOL_H
	#include "boolean.h"
	#include "dessine.h"
#endif

extern void setTour(colorPion p);

int sizeCaseOccuppe;

int getSizeCaseOccupe() {
	return sizeCaseOccuppe;
}

void initPlateau(Goban* ptrGoban, int width, int height, int nbCase){

	ptrGoban->nbCase = nbCase;
	ptrGoban->width = width;
	ptrGoban->height = height;
	sizeCaseOccuppe = 0;

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
	for(int ligne = nbCase-1; ligne >= 0; ligne--){

		for(int colonne = nbCase-1; colonne >= 0; colonne--) {
			//printf("%d:%d ", intersections[ligne][colonne]->x, intersections[ligne][colonne]->y);
			Intersection* i = intersections[ligne][colonne];

			if(i->interGauche) {
				printf("%d:%d ", i->interGauche->x, i->interGauche->y);
			}
		}

		printf("\n");

	}

}

bool placerPion(FILE* file, Goban* goban, Intersection* intersection, colorPion tour, int colonne, int ligne){

	// Etape 1 : On vérifie que la case est libre
	if(intersection->pion) {
		printf("Un pion est déjà présent sur la case %p\n", intersection);
		return false;
	}

	//char coupStr[6];
	
	// On place le pion avant de vérifier, on supprimera par la suite si nécessaire

	intersection->pion = initPion(tour, true);
	//positionToChar(coupStr, colonne, ligne, 'B');

	// Vérifie qu'on puisse poser un pion ici
	if(checkPosePion(goban, intersection, tour)){

		printf("Place pion case : %d:%d\n",ligne,colonne);

		//updateSGF(file, coupStr);

		sizeCaseOccuppe++;
		return true;
	}

	// Sinon on libère la mémoire du pion
	else {
		printf("Suppression pion initialisé\n");
		free(intersection->pion);
		intersection->pion = NULL;
	}

	return false;
}

bool checkPosePion(Goban* goban, Intersection* intersection, colorPion tour) {

	bool liberte = false;

	// Etape 2 : On regarde si le pion a AU MOINS UNE liberté direct
	if(checkLiberte(intersection)) { 
		liberte = true;
	}

	// Etape 3 : On regarde si on prend une chaine adverse
	Intersection** alreadyUse = malloc(sizeof(Intersection*));
	int sizeUsed = 1;

	printf("Intersection adresse : %p\n", intersection);

	// Chaine de droite
	if(intersection->interDroite && intersection->interDroite->pion && intersection->interDroite->pion->couleur != tour) {

		alreadyUse[0] = intersection->interDroite;

		printf("Taille Already Use = 1 ? : %d\n", sizeUsed);
		if(checkPriseChaine(intersection->interDroite, intersection->interDroite->pion->couleur, &alreadyUse, &sizeUsed, true)) {
			
			supprimerChaine(&alreadyUse, &sizeUsed);
			liberte = true;
		}

	}

	reAllocAlreadyUse(&alreadyUse, &sizeUsed);

	// Chaine du bas
	if(intersection->interBas && intersection->interBas->pion && intersection->interBas->pion->couleur != tour) {

		alreadyUse[0] = intersection->interBas;

		printf("Taille Already Use = 1 ? : %d\n", sizeUsed);
		if(checkPriseChaine(intersection->interBas, intersection->interBas->pion->couleur, &alreadyUse, &sizeUsed, true)) {
			
			supprimerChaine(&alreadyUse, &sizeUsed);
			liberte = true;
		}

	}

	reAllocAlreadyUse(&alreadyUse, &sizeUsed);

	// Chaine de gauche
	if(intersection->interGauche && intersection->interGauche->pion && intersection->interGauche->pion->couleur != tour) {

		alreadyUse[0] = intersection->interGauche;

		printf("Taille Already Use = 1 ? : %d\n", sizeUsed);
		if(checkPriseChaine(intersection->interGauche, intersection->interGauche->pion->couleur, &alreadyUse, &sizeUsed, true)) {
			
			supprimerChaine(&alreadyUse, &sizeUsed);
			liberte = true;
		}

	}

	reAllocAlreadyUse(&alreadyUse, &sizeUsed);

	// Chaine du haut
	if(intersection->interHaut && intersection->interHaut->pion && intersection->interHaut->pion->couleur != tour) {

		alreadyUse[0] = intersection->interHaut;

		printf("Taille Already Use = 1 ? : %d\n", sizeUsed);
		if(checkPriseChaine(intersection->interHaut, intersection->interHaut->pion->couleur, &alreadyUse, &sizeUsed, true)) {
			
			supprimerChaine(&alreadyUse, &sizeUsed);
			liberte = true;
		}

	}

	reAllocAlreadyUse(&alreadyUse, &sizeUsed);
/*
	// Etape 4 : Si on a toujours aucune liberté, on regarde si on gagne une liberté avec une chaine allié
	if(!liberte) {
		// Chaine de droite
		if(intersection->interDroite && intersection->interDroite->pion && intersection->interDroite->pion->couleur == tour) {

			alreadyUse[0] = intersection->interDroite;

			if(checkLiberteAllie(intersection->interDroite, intersection->interDroite->pion->couleur, alreadyUse, &sizeUsed, false)) {
				return true;
			}

		}
	}
*/


	return liberte;
}

void supprimerChaine(Intersection*** chaine, int* taille) {
	for(int i = 0; i < *taille; i++) {
		printf("INTERSECTION %d;%d COULEUR %d\n",chaine[0][i]->x, chaine[0][i]->y, chaine[0][i]->pion->couleur);
		free(chaine[0][i]->pion);
		chaine[0][i]->pion = NULL;
	}
}

void reAllocAlreadyUse(Intersection*** alreadyUse, int* taille) {

	// On ré-initialise un tableau de pointeur d'intersection
	Intersection **temp = realloc(alreadyUse[0], sizeof(Intersection *));
	if(temp == NULL) {
		printf("ERREUR WHEN REALLOC MEMORY\n");
	}
	
	alreadyUse[0] = temp;
	*taille = 1;
}

bool checkLiberte(Intersection* inter) {
	if(inter->interHaut && inter->interHaut->pion == NULL) { return true; }
	if(inter->interBas && inter->interBas->pion == NULL) { return true; }
	if(inter->interGauche && inter->interGauche->pion == NULL) { return true; }
	if(inter->interDroite && inter->interDroite->pion == NULL) { return true; }

	return false;
}

bool checkPriseChaine(Intersection *inter, colorPion color, Intersection*** alreadyUse, int *sizeUsed, bool prise) {

//	printf("Taille du tableau alreadyUse : %d\n", *sizeUsed);
	printf("\nPierre courante, intersection : %p\n", inter);

	if(checkLiberte(inter)){
		return false;
	}

	// On regarde si l'intersection existe
	if(inter->interDroite) {

		if(inter->interDroite->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interDroite)){

				if(prise){
					prise = checkPriseChaine(inter->interDroite, color, alreadyUse, sizeUsed, prise);
				}
			}

		}
	}

	// On regarde si l'intersection existe
	if(inter->interBas) {

		if(inter->interBas->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interBas)){

				if(prise){
					prise = checkPriseChaine(inter->interBas, color, alreadyUse, sizeUsed, prise);
				}
			}

		}
	}

	// On regarde si l'intersection existe
	if(inter->interGauche) {

		if(inter->interGauche->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interGauche)){

				if(prise){
					prise = checkPriseChaine(inter->interGauche, color, alreadyUse, sizeUsed, prise);
				}
			}

		}
	}

	// On regarde si l'intersection existe
	if(inter->interHaut) {

		if(inter->interHaut->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interHaut)){

				if(prise){
					prise = checkPriseChaine(inter->interHaut, color, alreadyUse, sizeUsed, prise);
				}
			}

		}
	}

	return prise;

}

bool checkAlreadyUse(Intersection*** intersections, int *taille, Intersection* inter) {

	printf("Il y a %d intersections déjà utilisées\n", *taille);

	int i = 0;


	for(i = 0; i < *taille; i++) {
		printf("Tableau intersection : %p | Intersection vérifié : %p\n", intersections[i], inter);
		// Comparaison des adresses mémoires
		if(intersections[0][i] == inter) {
			printf("Même intersections\n");
			return true;
		}
	}

	// L'intersection n'a pas été utilisée, on l'ajoute au tableau et on incrémente la taille
	Intersection **temp = realloc(intersections[0], sizeof(Intersection *) * (*taille +1 ));
	if(temp == NULL) {
		printf("ERREUR WHEN REALLOC MEMORY\n");
	}
	
	intersections[0] = temp;

	intersections[0][( *taille)++] = inter;

	printf("On ajoute l'intersection au tableau, Taille = %d | I = %d\n", *taille, i);
	return false;
}

bool checkIfPion(Goban* goban, int x, int y) {
	if(goban->intersections[x][y]->pion) { return true; }
	return false;
}

bool checkLiberteAllie(Intersection *inter, colorPion color, Intersection*** alreadyUse, int *sizeUsed, bool liberte) {

	printf("Liberté de chaine alliée \n");
	printf("Taille du tableau alreadyUse : %d\n", *sizeUsed);
	printf("Intersection adresse: %p\n", alreadyUse[0]);

	if(checkLiberte(inter)){
		return true;
	}

	// On regarde si l'intersection existe
	if(inter->interDroite) {

		if(inter->interDroite->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interDroite)){

				if(!liberte) {
					liberte = checkLiberteAllie(inter->interDroite, color, alreadyUse, sizeUsed, liberte);
				}
			}

		}
	}

	// On regarde si l'intersection existe
	if(inter->interBas) {

		if(inter->interBas->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interBas)){

				if(!liberte) {
					liberte = checkLiberteAllie(inter->interBas, color, alreadyUse, sizeUsed, liberte);
				}
			}

		}
	}

	// On regarde si l'intersection existe
/*	if(inter->interGauche) {

		if(inter->interGauche->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interGauche)){

				if(!liberte) {
					liberte = checkLiberteAllie(inter->interGauche, color, alreadyUse, sizeUsed, liberte);
				}
			}

		}
	}
*/	
	// On regarde si l'intersection existe
	if(inter->interHaut) {

		if(inter->interHaut->pion->couleur == color){

			// On regarde si on l'a pas déjà utilisé
			if(!checkAlreadyUse(alreadyUse, sizeUsed, inter->interHaut)){

				if(!liberte) {
					liberte = checkLiberteAllie(inter->interHaut, color, alreadyUse, sizeUsed, liberte);
				}
			}

		}
	}

	return liberte;
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
		colorPion last;
    while ((read = getline(&line, &len, file)) != -1) {

        if(i > 1) {
        	printf("Couleur : %c Colonne : %c Ligne : %c\n", line[0], line[2], line[3]);

        	colonne = charToPosition(line[2]);
        	ligne = charToPosition(line[3]);

        	Intersection* intersection = goban->intersections[ligne][colonne];

        	if(line[0] == 'B') {
        		intersection->pion = initPion(NOIR, true);
						last = NOIR;
        	}
        	else {
        		intersection->pion = initPion(BLANC, true);
						last = BLANC;
        	}
					sizeCaseOccuppe++;
        }
        i++;
    }

		if(last == BLANC) { setTour(NOIR); }
		else { setTour(BLANC); }
}
