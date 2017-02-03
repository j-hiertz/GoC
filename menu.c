#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

extern void newParty();
extern void loadParty();
extern void choixTaille();
extern void choixAdversaire();

Button** arrayButton = NULL;

int arraySize() {
	int i = 0;
	while(arrayButton[i] != NULL) {
		i++;
	}
	return i;
}

void freeButtons() {
	free(arrayButton);
	arrayButton = NULL;
}

int checkClick(int x, int y) {
	int size = arraySize();
	printf("PISS: %d",size);
	for(int i = 0; i < size; i++) {
		if(x > arrayButton[i]->x && x < (arrayButton[i]->x + arrayButton[i]->w) && y > arrayButton[i]->y && y < (arrayButton[i]->y + arrayButton[i]->h)){
				printf("Click détecté dans le button n°%d\n", i);
				arrayButton[i]->click();
		}
	}
	printf("ZEIIIIIIIIIIIIIIIII\n");
}

Button* init_button(int x, int y, int w, int h, void(*c)()) {
	Button* btn = malloc(sizeof(Button));
	btn->x = x;
	btn->y = y;
	btn->w = w;
	btn->h = h;
	btn->click = c;
	return btn;
}

// Resize screen under 600 pixel width or 400 pixel height
void resizeMenu(int width, int height) {
	if(width < 600) {
		resize_window(600, 0);
	} else if (height < 400) {
		resize_window(0, 400);
	}
}

void draw_menu_load(int width, int height) {

	resizeMenu(width, height);

	char new_party[] = "Nouvelle partie";
	char load_party[] = "Charger une partie";

	// Determines x, y & size of button
	int btn1_w = (width / 5);
	int btn1_h = btn1_w / 2;
	int btn1_x = btn1_w;
	int btn1_y = (height / 2) - (btn1_h / 2);

	int new_party_x = btn1_x + (btn1_w / 2) - 45;
	int new_party_y = btn1_y + (btn1_h / 2) + 3;

	int btn2_x = btn1_x + 2 * btn1_w;
	int load_party_x = btn2_x + (btn1_w / 2) - 50;

	// Button registering...
	Button* btn1 = init_button(btn1_x, btn1_y, btn1_w, btn1_h, &newParty);
	Button* btn2 = init_button(btn2_x, btn1_y, btn1_w, btn1_h, &loadParty);
	arrayButton = malloc(sizeof(Button) * 2);
	arrayButton[0] = btn1;
	arrayButton[1] = btn2;

	rectangle(btn1_x, btn1_y, btn1_w, btn1_h);
	string(new_party_x, new_party_y, new_party);
	rectangle(btn2_x, btn1_y, btn1_w, btn1_h);
	string(load_party_x, new_party_y, load_party);
}

void draw_goban_size(int width, int height) {

	resizeMenu(width, height);

	char goban19[] = "19 x 19";
	char goban13[] = "13 x 13";
	char goban9[] = "9 x 9";

	int btn1_w = (width / 4);
	int btn1_h = (btn1_w / 2);
	int btn1_x = (width / 2) - (btn1_w / 2);
	int btn1_y = (height / 7);

	int btn2_y = btn1_y + btn1_h + (btn1_h / 5);
	int btn3_y = btn2_y + btn1_h + (btn1_h / 5);

	int goban19_x = btn1_x + (btn1_w / 2) - 18;
	int goban19_y = btn1_y + (btn1_h / 2) + 4;

	int goban13_y = btn2_y + (btn1_h / 2) + 4;
	int goban9_y = btn3_y + (btn1_h / 2) + 4;
	void(*truc)() = &choixTaille;
	// Button registering...
	Button* btn1 = init_button(btn1_x, btn1_y, btn1_w, btn1_h, truc);
	Button* btn2 = init_button(btn1_x, btn2_y, btn1_w, btn1_h, truc);
	Button* btn3 = init_button(btn1_x, btn3_y, btn1_w, btn1_h, truc);

	arrayButton = malloc(sizeof(Button) * 3);
	arrayButton[0] = btn1;
	arrayButton[1] = btn2;
	arrayButton[2] = btn3;

	rectangle(btn1_x, btn1_y, btn1_w, btn1_h);
	string(goban19_x, goban19_y, goban19);
	rectangle(btn1_x, btn2_y, btn1_w, btn1_h);
	string(goban19_x, goban13_y, goban13);
	rectangle(btn1_x, btn3_y, btn1_w, btn1_h);
	string(goban19_x, goban9_y, goban9);
}

void draw_choix_adversaire(int width, int height) {
	resizeMenu(width, height);

	char new_party[] = "IA";
	char load_party[] = "Deux joueurs";

	// Determines x, y & size of button
	int btn1_w = (width / 5);
	int btn1_h = btn1_w / 2;
	int btn1_x = btn1_w;
	int btn1_y = (height / 2) - (btn1_h / 2);

	int new_party_x = btn1_x + (btn1_w / 2) - 5;
	int new_party_y = btn1_y + (btn1_h / 2) + 3;

	int btn2_x = btn1_x + 2 * btn1_w;
	int load_party_x = btn2_x + (btn1_w / 2) - 35;

	// Button registering...
	Button* btn1 = init_button(btn1_x, btn1_y, btn1_w, btn1_h, &choixAdversaire);
	Button* btn2 = init_button(btn2_x, btn1_y, btn1_w, btn1_h, &choixAdversaire);
	arrayButton = malloc(sizeof(Button) * 2);
	arrayButton[0] = btn1;
	arrayButton[1] = btn2;

	rectangle(btn1_x, btn1_y, btn1_w, btn1_h);
	string(new_party_x, new_party_y, new_party);
	rectangle(btn2_x, btn1_y, btn1_w, btn1_h);
	string(load_party_x, new_party_y, load_party);
}
