#include <stdio.h>
#include <stdlib.h>
#include "../../header/menu.h"

extern void newParty();
extern void loadParty();
extern void setGoban19();
extern void setGoban13();
extern void setGoban9();
extern void choixJoueur1();
extern void choixJoueur2();
extern void validationAdversaire();
extern void backToMenu();
extern void rejouerGame();
extern void click_pass();
extern void click_deleteMode();
extern void draw_pion(int x, int y, colorPion colorPion);

Button** arrayButton = NULL;
int sizeArray = 0;

void freeButtons() {
	if(arrayButton != NULL) {
		free(arrayButton);
		arrayButton = NULL;
		sizeArray = 0;
	}
}

int checkClick(int x, int y) {
	for(int i = 0; i < sizeArray; i++) {
		if(x > arrayButton[i]->x && x < (arrayButton[i]->x + arrayButton[i]->w) && y > arrayButton[i]->y && y < (arrayButton[i]->y + arrayButton[i]->h)){
				arrayButton[i]->click();
				return 1;
		}
	}
	return 0;
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
	sizeArray = 2;
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

	// Button registering...
	Button* btn1 = init_button(btn1_x, btn1_y, btn1_w, btn1_h, &setGoban19);
	Button* btn2 = init_button(btn1_x, btn2_y, btn1_w, btn1_h, &setGoban13);
	Button* btn3 = init_button(btn1_x, btn3_y, btn1_w, btn1_h, &setGoban9);

	arrayButton = malloc(sizeof(Button) * 3);
	sizeArray = 3;
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

void setLabelButton(char* label, int btn_x, int btn_y, int btn_w, int btn_h, int sizeLabel) {
	int label_x, label_y;

	label_x = btn_x + (btn_w / 2) - (sizeLabel / 2);
	label_y = btn_y + (btn_h / 2) + 3;

	string(label_x, label_y, label);
}

void draw_choix_adversaire(int width, int height, typePlayer selectedPlayer1, typePlayer selectedPlayer2) {
	resizeMenu(width, height);

	char ia[] = "IA";
	char player[] = "Joueur";
	char validation[] = "Valider";
	int sizeLabelIa = 10;
	int sizeLabelPlayer = 30;
	int sizeValidation = 40;

	char first_player[] = "Joueur 1";
	char second_player[] = "Joueur 2";

	// Determines x, y & size of button
	int btn1_w = (width / 5);
	int btn1_h = btn1_w / 2;
	int btn1_x = (width / 4) - (btn1_w / 2);
	int btn1_y = (height / 2) - (btn1_h / 2);

	int btn2_x = (width / 4) * 3 - (btn1_w / 2);

	int btn3_w = width / 4;
	int btn3_h = btn3_w / 3;
	int btn3_x = (width / 2) - (btn3_w / 2);
	int btn3_y = height - (height / 4);

	// Determines x, y & size of label
	int lbl_joueur1_x = (width / 4) - 25;
	int lbl_joueur1_y = height / 4;

	int lbl_joueur2_x = (width / 4) * 3 - 25;

	// Button registering...
	Button* btn1 = init_button(btn1_x, btn1_y, btn1_w, btn1_h, &choixJoueur1);
	Button* btn2 = init_button(btn2_x, btn1_y, btn1_w, btn1_h, &choixJoueur2);
	Button* btn3 = init_button(btn3_x, btn3_y, btn3_w, btn3_h, &validationAdversaire);
	arrayButton = malloc(sizeof(Button) * 3);
	sizeArray = 3;
	arrayButton[0] = btn1;
	arrayButton[1] = btn2;
	arrayButton[2] = btn3;

	// Displaying button & their label
	rectangle(btn1_x, btn1_y, btn1_w, btn1_h);
	rectangle(btn2_x, btn1_y, btn1_w, btn1_h);
	rectangle(btn3_x, btn3_y, btn3_w, btn3_h);

	if(selectedPlayer1 == JOUEUR) { setLabelButton(player, btn1_x, btn1_y, btn1_w, btn1_h, sizeLabelPlayer); }
	else { setLabelButton(ia, btn1_x, btn1_y, btn1_w, btn1_h, sizeLabelIa); }
	if(selectedPlayer2 == JOUEUR) { setLabelButton(player, btn2_x, btn1_y, btn1_w, btn1_h, sizeLabelPlayer); }
	else { setLabelButton(ia, btn2_x, btn1_y, btn1_w, btn1_h, sizeLabelIa); }

	setLabelButton(validation, btn3_x, btn3_y, btn3_w, btn3_h, sizeValidation);

	// Title labels displaying
	string(lbl_joueur1_x, lbl_joueur1_y, first_player);
	string(lbl_joueur2_x, lbl_joueur1_y, second_player);
	line(width / 2, 0, width / 2, btn3_y);
	line(width / 2, btn3_y + btn3_h, width / 2, height);
}

void draw_score_final(int pointsJ1, int pointsJ2, int width, int height) {
	int box_w = 300;
	int box_h = 3*(box_w / 4);
	int box_x = (width / 2) - (box_w / 2);
	int box_y = (height / 2) - (box_h / 2);

	int btn1_w = 100;
	int btn1_h = 60;
	int btn1_x = box_x + 33;
	int btn1_y = box_y + box_h - 80;

	char menu[] = "Menu";
	char rejouer[] = "Rejouer";
	char recap[] = "RECAPITULATIF SCORES";
	char joueur1[22];
	char joueur2[22];
	sprintf(joueur1, "Joueur 1 : %d points", pointsJ1);
	sprintf(joueur2, "Joueur 2 : %d points", pointsJ2);

	int btn2_x = btn1_x + btn1_w + 33;

	freeButtons();
	Button* btn1 = init_button(btn1_x, btn1_y, btn1_w, btn1_h, &backToMenu);
	Button* btn2 = init_button(btn2_x, btn1_y, btn1_w, btn1_h, &rejouerGame);
	arrayButton = malloc(sizeof(Button) * 2);
	arrayButton[0] = btn1;
	arrayButton[1] = btn2;
	sizeArray = 2;

	color(0.988,0.807,0.611);
	filled_rectangle(box_x, box_y, box_w, box_h);

	color(1,1,1);
	filled_rectangle(btn1_x, btn1_y, btn1_w, btn1_h);
	filled_rectangle(btn2_x, btn1_y, btn1_w, btn1_h);

	color(0,0,0);
	rectangle(box_x, box_y, box_w, box_h);
	rectangle(btn1_x, btn1_y, btn1_w, btn1_h);
	rectangle(btn2_x, btn1_y, btn1_w, btn1_h);

	string(box_x + box_w / 2 - 60, box_y + 25, recap);
	string(box_x + 25, box_y + 80, joueur1);
	string(box_x + 25, box_y + 110, joueur2);
	setLabelButton(menu, btn1_x, btn1_y, btn1_w, btn1_h, 25);
	setLabelButton(rejouer, btn2_x, btn1_y, btn1_w, btn1_h, 40);
}

// Dessine les tours de jeu
void draw_tour_jeu(int espaceCase, int nbCase, colorPion tour) {
	color(0, 0, 0);
	char tourLbl[] = "Prochaine pierre";
	int width = width_win();
	int height = height_win();

	string(espaceCase * nbCase + 65, espaceCase + (espaceCase / 2), tourLbl);
	draw_pion(espaceCase * nbCase + 110, espaceCase * 2 + (espaceCase / 4), tour);
}

// Dessine le bouton passer
void draw_menu_game_pass(int espaceCase, int nbCase) {
	color(1, 1, 1);
	int pass_w = 120;
	int pass_h = pass_w / 2;
	int pass_x = espaceCase * nbCase + 50;
	int pass_y = espaceCase * (nbCase / 3) + 60;
	char passerLbl[] = "Passer";

	filled_rectangle(pass_x, pass_y, pass_w, pass_h);
	Button* pass = init_button(pass_x, pass_y, pass_w, pass_h, &click_pass);
	arrayButton = malloc(sizeof(Button) * 2);
	arrayButton[0] = pass;
	sizeArray = 1;

	color(0, 0, 0);
	rectangle(pass_x, pass_y, pass_w, pass_h);
	setLabelButton(passerLbl, pass_x, pass_y, pass_w, pass_h, 30);
}

// Dessine le bouton delete
void draw_menu_game_delete(int espaceCase, int nbCase, bool deleteMode) {
	color(1, 1, 1);
	int del_w = 120;
	int del_h = del_w / 3;
	int del_x = espaceCase * nbCase + 50;
	int del_y = espaceCase * (nbCase / 3) + 140;
	char *deleteLbl = malloc(sizeof(char)*16);
	if(deleteMode) { deleteLbl = "Delete Mode: On "; }
	else { deleteLbl = "Delete Mode: Off"; }

	filled_rectangle(del_x, del_y, del_w, del_h);

	Button* delete = init_button(del_x, del_y, del_w, del_h, &click_deleteMode);
	arrayButton[1] = delete;
	sizeArray = 2;

	color(0, 0, 0);
	rectangle(del_x, del_y, del_w, del_h);
	setLabelButton(deleteLbl, del_x, del_y, del_w, del_h, 85);
}
