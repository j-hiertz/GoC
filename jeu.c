#include <stdio.h>
#include <stdlib.h>
#include "dessine.h"

int nbCase;

void draw_plateau(int width, int height)
{
	clear_win();

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
	init_win(width, height, "Go Go MoMo Game Desu",0.988,0.807,0.611);
	event_loop();
	return EXIT_SUCCESS;
}