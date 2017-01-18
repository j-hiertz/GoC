#include <stdio.h>
#include <stdlib.h>
#include "dessine.h"

int nbCase;
int courFenetre;

void draw_plateau(int width, int height)
{

	int espaceLigne = (height - 20) / nbCase;
	int espaceCol = (width - 20) / nbCase;

	printf("\nEspacement entre ligne : %d\n",espaceLigne);
	printf("\nEspacement entre colonne : %d\n",espaceCol);

	int i;

	for(i=0; i < nbCase ; i++){
		line(0, 10 + (espaceLigne * i), width-10, 10 + (espaceLigne * i));
	}

	for(i=0; i < nbCase ; i++){
		line(10 + (espaceCol * i), 0, 10 + (espaceCol * i), height-10);
	}


}

/*void draw_menu_title(int width, int height)
{
	color(154, 38, 98);
	string(width / 2,10,"Go Go MoMo Game Desu");
}*/

void draw_menu_load(int width, int height)
{
	if(width < 200) {
		resize_window('w', 200);
	}
	char new_party[] = "Nouvelle partie";
	char load_party[] = "Charger une partie";

	int btn1_w = (width / 5);
	int btn1_h = btn1_w / 2;
	int btn1_x = btn1_w;
	int btn1_y = (height / 2) - (btn1_h / 2);

	int new_party_x = (width / 5) + (btn1_w / 5);
	int new_party_y = btn1_y + (btn1_h / 2);

	rectangle(btn1_x, btn1_y, btn1_w, btn1_h);
	string(new_party_x, new_party_y, new_party);

	int btn2_x = btn1_x + 2 * btn1_w;

	int load_party_x = new_party_x + (2 * btn1_w);
	rectangle(btn2_x, btn1_y, btn1_w, btn1_h);
	string(new_party_x + 2 * btn1_w, new_party_y, load_party);
}

void draw_choix_taille(int width, int height) {

}

void refresh_manager(int width, int height)
{
	clear_win();
	if(courFenetre == 0) {
		draw_menu_load(width, height);
	} else if (courFenetre == 1) {
		draw_plateau(width, height);
	}
}

void mouse_clicked(int bouton, int x, int y)
{
	printf("Bouton %d presse au coord. %d,%d \n",bouton,x,y);
	color( 1.0,0.0,1.0);
	filled_circle(x,y,10);
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
			height = 400;
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
	event_loop();
	return EXIT_SUCCESS;
}
