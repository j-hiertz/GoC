#ifndef LIBRARY_H
	#define LIBRARY_H
	#include "dessine.h"
	#include "menu.h"
	#include "file.h"
#endif

bool getInitialized();

bool calculTerritoire(Intersection* inter, colorPion *couleur, bool verif, int *count);

void calculPoints();

void draw_pion(int x, int y, colorPion colorPion);
void draw_hoshi(int width, int height);
void click_pass();
void click_deleteMode();
void draw_init_menu_game(int width, int height);
void draw_plateau(int width, int height);
bool checkBoundsGoban(int x, int y);
bool playIA(int ligne, int colonne);
void whoIsPlaying();
void refresh_plateau(int width, int height);
void refresh_manager(int width, int height);
void reinitDefaultValues();
void backToMenu();
void rejouerGame();
void newParty();
void loadParty();
void choixTaille();
void setGoban19();
void setGoban13();
void setGoban9();
void choixAdversaire();
void validationAdversaire();
void choixJoueur1();
void choixJoueur2();
void mouse_clicked(int bouton, int x, int y);
void key_pressed(KeySym code, char c, int x_souris, int y_souris);