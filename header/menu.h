#include <stdio.h>
#include <stdlib.h>
#include "dessine.h"
#ifndef PION_H
	#define PION_H
	#include "pion.h"
#endif

typedef struct Button{
	int x, y, w, h;
	void (*click)();
} Button;

typedef enum { IA, JOUEUR} typePlayer;

/**
 * Libère les boutons de la memoire
 */
void freeButtons();

/**
 * Initialise un bouton
 * x: Position x du bouton
 * y: Position y du bouton
 * w: Largeur du bouton
 * h: Hauteur du bouton
 * click: Pointeur de fonction pour gerer le clic sur le bouton
 */
Button* init_button(int, int, int, int, void(*c)());

/**
 * Affiche le texte du bouton centre horizontalement et verticalement
 * label: Tableau de char a afficher
 * x: Position x du bouton
 * y: Position y du bouton
 * w: Largeur du bouton
 * h: Hauteur du bouton
 * sizeLabel: Largeur du texte
 */
void setLabelButton(char*, int, int, int, int, int);

/**
 * Gere les clic sur les boutons
 * x: Position x du clic
 * y: Position y du clic
 */
int checkClick(int, int);

/**
 * Affiche le menu Nouvelle part et Charger partie
 * width: Largeur de la fenetre
 * height: Hauteur de ma fenetre
 */
void draw_menu_load(int, int);

/**
 * Affiche le menu de choix de la taille du goban
 * width: Largeur de la fenetre
 * height: Hauteur de ma fenetre
 */
void draw_goban_size(int, int);

/**
 * Affiche le menu de choix d'un adversaire
 * width: Largeur de la fenetre
 * height: Hauteur de ma fenetre
 */
void draw_choix_adversaire(int, int, typePlayer, typePlayer);

/**
 * Affiche le recapitulatif des scores en fin de partie
 * pointsJ1: Points du joueur 1
 * pointsJ2: Points du joueur 2
 * width: Largeur de la fenetre
 * height: Hauteur de ma fenetre
 */
void draw_score_final(int, int, int, int);

/**
 * Affiche le tour de jeu du joueur colorPion
 * width: Largeur de la fenetre
 * height: Hauteur de ma fenetre
 * tour: Couleur du tour du joueur colorPion
 */
void draw_tour_jeu(int, int, colorPion);

/**
 * Affiche le bouton Passer dans une partie
 * width: Largeur de la fenetre
 * height: Hauteur de ma fenetre
 */
void draw_menu_game_pass(int, int);

/**
 * Affiche le bouton de suppression des pions
 * width: Largeur de la fenetre
 * height: Hauteur de ma fenetre
 * deleteMode: Permet de determiner si le texte du bouton affiche On ou Off
 */
void draw_menu_game_delete(int, int, bool);
