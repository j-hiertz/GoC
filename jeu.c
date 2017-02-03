#include <stdio.h>
#include <stdlib.h>
#ifndef DESSINE_H
	#define DESSINE_H
	#include "dessine.h"
#endif
#include "menu.h"

int nbCase, espaceCase, tour, courFenetre;

void draw_pion( int x, int y){

	// On ne dessine pas hors du plateau
	if(x < espaceCase || y < espaceCase || x > nbCase * espaceCase || y > nbCase * espaceCase) {
		return;
	}

	// Tour du blanc
	if(tour == -1){
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

	if(height < width) {
		espaceCase = height / (nbCase + 1);
	}
	else {
		espaceCase = width / (nbCase + 1);
	}

	printf("\nEspacement entre ligne : %d\n",espaceCase);
	printf("\nEspacement entre colonne : %d\n",espaceCase);

	int i;

	for(i=0; i < nbCase ; i++){
		line(espaceCase, espaceCase + (espaceCase * i), nbCase*espaceCase, espaceCase + (espaceCase * i));
	}

	for(i=0; i < nbCase ; i++){
		line(espaceCase + (espaceCase * i), espaceCase, espaceCase + (espaceCase * i), espaceCase * nbCase);
	}

	draw_hoshi(width, height);

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
	courFenetre = 3;
	int w = width_win();
	int h = height_win();
	refresh_manager(w, h);
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
	checkClick(x, y);
	draw_pion(x,y);
	tour *= -1;
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

	if (c>' ' && c<'z')
		printf("char: %c \n",c);

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
		nbCase = 9;
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

	init_win(600, 400, "Go Go MoMo Game Desu",0.988,0.807,0.611);
	event_loop();
	return EXIT_SUCCESS;
}
