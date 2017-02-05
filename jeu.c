#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef LIBRARY_H
	#define LIBRARY_H
	#include "dessine.h"
	#include "goban.h"
	#include "menu.h"
	#include "file.h"
#endif

int nbCase, espaceCase, tour, courFenetre;
Goban *goban;
FILE *file;

void draw_pion(int x, int y, colorPion colorPion){

	//checkPosePion();

	// Tour du blanc
	if(colorPion == BLANC){
		color(1,1,1);
	}
	else { // Tour du noir
		color(0,0,0);
	}

	// Taille du pion
	filled_circle(x,y,(espaceCase /2)*0.85);

}

void draw_hoshi(int width, int height){

	int i,j;
	color(0,0,0);
	printf("\nDessine les Hoshis");

	switch(nbCase)
	{
		case 9:
				for(i = 2; i <=6; i+=4){
				for(j= 2; j<= 6; j+=4){
					int posX = espaceCase + (j * espaceCase);
					int posY = espaceCase + (i * espaceCase);
					filled_circle(posX, posY, ((float)1.5 * espaceCase / 50) + 1.9);
				}
			}
			break;
		case 13:
			for(i = 1; i <= 3; i++){
				for(j = 1; j <= 3; j++){
					int posX = espaceCase + (3 * j * espaceCase);
					int posY = espaceCase + (3 * i * espaceCase);
					filled_circle(posX, posY, ((float)2 * espaceCase / 50) + 1.9);
				}
			}
			break;
		case 19:
			for(i = 3; i <=15; i+=6){
				for(j= 3; j<= 15; j+=6){
					int posX = espaceCase + (j * espaceCase);
					int posY = espaceCase + (i * espaceCase);
					filled_circle(posX, posY, ((float)2.5 * espaceCase / 50) + 1.9);
				}
			}
			break;
	}
}

void draw_plateau(int width, int height)
{
	clear_win();
	color(0,0,0);

	// On calcul le ratio pour garder un Goban carré
	if(height < width) {
		espaceCase = height / (nbCase + 1);
	}
	else {
		espaceCase = width / (nbCase + 1);
	}

	printf("\nEspacement entre ligne : %d\n",espaceCase);
	printf("\nEspacement entre colonne : %d\n",espaceCase);

	int i;

	// On redessine le plateau
	for(i=0; i < nbCase ; i++){
		line(espaceCase, espaceCase + (espaceCase * i), nbCase*espaceCase, espaceCase + (espaceCase * i));
	}

	for(i=0; i < nbCase ; i++){
		line(espaceCase + (espaceCase * i), espaceCase, espaceCase + (espaceCase * i), espaceCase * nbCase);
	}

	// On redessine les hoshi
	draw_hoshi(width, height);

	// On réaffecte les positions des intersections puis on redessine les pions
	for(int ligne = 0; ligne < nbCase; ligne++) {

		int posY = espaceCase + (espaceCase * ligne);

		for(int colonne = 0; colonne < nbCase; colonne++) {

			int posX = espaceCase + (espaceCase * colonne);
			updatePosIntersection(goban->intersections[ligne][colonne], posX, posY);

			Intersection* inter = goban->intersections[ligne][colonne];

			if(inter->pion && inter->pion->visible) {
					draw_pion(inter->x, inter->y, inter->pion->couleur);
			}
		}
	}

}

bool checkBoundsGoban(int x, int y){
	// On ne dessine pas hors du plateau
	if(x < espaceCase || y < espaceCase || x > nbCase * espaceCase || y > nbCase * espaceCase) {
		return false;
	}

	return true;
}

// Manage changing window
void refresh_manager(int width, int height)
{
	clear_win();
	freeButtons();
	if(courFenetre == 0) {
		draw_menu_load(width, height);
	} else if (courFenetre == 1) {
		draw_goban_size(width, height);
	} else if (courFenetre == 2) {
		draw_choix_adversaire(width, height);
	} else if (courFenetre == 3) {

		//if(file) { // FAIT PLANTER LE JEU ?
			file = createSGF(nbCase); //TODO check if file exist (charger)
		//}

		draw_plateau(width, height);
	}
}

void newParty() {
	courFenetre = 1;
	int w = width_win();
	int h = height_win();
	refresh_manager(w, h);
}

void loadParty() {

	char fileName[255];

	printf("\n========== Chargement de partie ==========\n");
	printf("\nVeuillez indiquer le chemin absolu du fichier SGF : \n");

	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "r");

	if(fp == NULL) {
		printf("ERROR : IMPOSSIBLE D'OUVRIR LE FICHIER : %s\n",fileName);
		loadParty();
	}
	else {
		printf("Chargement de la partie\n");
		createGameFromFile(fp, goban);
		courFenetre = 3;
		int w = width_win();
		int h = height_win();
		refresh_manager(w, h);
	}
}

void choixTaille() {
	courFenetre = 2;
	int w = width_win();
	int h = height_win();
	refresh_manager(w, h);
}

void setGoban19() {
	nbCase =  19;
	choixTaille();
}

void setGoban13() {
	nbCase =  13;
	choixTaille();
}

void setGoban9() {
	nbCase =  9;
	choixTaille();
}

void choixAdversaire() {
	courFenetre = 3;
	int w = width_win();
	int h = height_win();
	refresh_manager(w, h);
}

// Handle user click
void mouse_clicked(int bouton, int x, int y) {

	printf("\nBouton %d presse au coord. %d,%d \n",bouton,x,y);
	
	// Menu purpose
	checkClick(x, y);

	if(checkBoundsGoban(x, y)) {

		// On défini la case la plus proche du click
		int colonne = ((x + (espaceCase /2)) / espaceCase) -1;
		int ligne = ((y + (espaceCase /2)) / espaceCase) -1;

		Intersection *inter = goban->intersections[ligne][colonne];

		// Routine de vérification de placement de pion
		if(placerPion(file, goban, inter, tour, colonne, ligne)) {

			printf("Intersection -> pion %p\n", inter->pion);
			printf("Pion déssiné de couleur : %d visible : %d\n", inter->pion->couleur, inter->pion->visible);
			
			if(tour == 1) {
				draw_pion(inter->x,inter->y,NOIR);
			}
			else {
				draw_pion(inter->x,inter->y,BLANC);
			}
			tour *= -1;
		}
	}
}


/**
 * on a appuyé sur une touche
 * code: code touche x11 (XK_...)
 * c caractère correspondant si caractere
 * x_souris,y_souris position de la souris
 */
void key_pressed(KeySym code, char c, int x_souris, int y_souris)
{
	switch(code)
	{
		case XK_Down:
			printf("bas\n");
			break;
		case XK_Up:
			printf("haut\n");
			break;
		case XK_Left:
			printf("gauche\n");
			break;
		case XK_Right:
			printf("droite\n");
			break;
	//~ case XK_Return:
	//~ case XK_Shift_L:
	//~ case XK_Control_R:
	//~ ....
		default:
			break;
	}

	if (c>' ' && c<'z') {
		printf("char: %c \n",c);

		if(c == 'e'){
			endGameSGF(file, "(;RE[B+R]");
		}
	}

	printf(" avec pos souris: %d,%d \n",x_souris,y_souris);

}

int main(int argc, char **argv) {

	int width, height;
	courFenetre = 0;
	tour = 1;

	if(argc >= 2) {
		sscanf(argv[1],"%d",&nbCase);
	}

	if(nbCase == 0){
		nbCase = 19;
	}

	switch(nbCase)
	{
		case 9:
			width = 500;
			height = 500;
			break;
		case 13:
			width = 700;
			height = 700;
			break;
		case 19:
			width = 900;
			height = 900;
			break;
		default:
			break;
	}

	init_win(width, height, "Go Go MoMo Game Desu",0.988,0.807,0.611);

	goban = malloc(sizeof *goban);
	initPlateau(goban, width, height, nbCase);

	event_loop();
	return EXIT_SUCCESS;
}
