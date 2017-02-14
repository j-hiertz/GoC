#include <stdio.h>
#include <stdlib.h>
#include "dessine.h"

typedef struct Button{
	int x, y, w, h;
	void (*click)();
} Button;

typedef enum { IA, JOUEUR} typePlayer;

void freeButtons();
Button* init_button(int, int, int, int, void(*c)());
void setLabelButton(char*, int, int, int, int, int);
int checkClick(int, int);
void draw_menu_load(int, int);
void draw_goban_size(int, int);
void draw_choix_adversaire(int, int, typePlayer, typePlayer);
void draw_score_final(int, int, int, int);
