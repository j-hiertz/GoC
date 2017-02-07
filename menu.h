#include <stdio.h>
#include <stdlib.h>
#include "dessine.h"

typedef struct Button{
	int x, y, w, h;
	void (*click)();
} Button;

void freeButtons();
int checkClick(int x, int y);
Button* init_button(int x, int y, int w, int h, void(*c)());
void draw_menu_load(int width, int height);
void draw_goban_size(int width, int height);
void draw_choix_adversaire(int width, int height);
