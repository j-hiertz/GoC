#include <stdio.h>
#include <stdlib.h>
#include "dessine.h"

typedef struct Button{
	int x, y, w, h;
	void (*click)();
} Button;

typedef enum { IA, JOUEUR} typePlayer;

void freeButtons();
int checkClick(int, int);
Button* init_button(int, int, int, int, void(*c)());
void draw_menu_load(int, int);
void draw_goban_size(int, int);
void setLabelButton(char*, int, int, int, int, int);
void draw_choix_adversaire(int, int, typePlayer, typePlayer);
