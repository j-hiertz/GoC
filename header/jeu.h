#ifndef LIBRARY_H
	#define LIBRARY_H
	#include "dessine.h"
	#include "menu.h"
	#include "file.h"
#endif

/**
 * Permet de savoir si la partie est initialisée ou non
 */
bool getInitialized();

/**
 * Détermine recursivement si la zone de case vide est un territoire ou non
 * inter: L'intersection vide
 * couleur: Couleur du pion voisin si il y en a un
 * verif: Permet de savoir si la zone est un territoire ou non
 * count: Compteur de case vide visitées
 */
bool calculTerritoire(Intersection* inter, colorPion *couleur, bool verif, int *count);

/**
 * Calcule le nombre total de points en fonction des pierres posées et des territoires
 */
void calculPoints();

/**
 * Dessine une pierre
 * x: Position x ou dessiner la pierres
 * y: Position y ou dessiner la pierre
 * colorPion: Couleur de la pierre à dessiner
 */
void draw_pion(int x, int y, colorPion colorPion);

/**
 * Dessine les hoshis du goban
 * width: Largeur de la fenetre
 * height: Hauteur de la fenetre
 */
void draw_hoshi(int width, int height);

/**
 * Fonction gerant le clic sur le bouton Passer
 */
void click_pass();

/**
 * Fonction gerant le clic sur le bouton Delete Mode
 */
void click_deleteMode();

/**
 * Gere l'affichage des differents boutons de menu lors d'une partie
 * width: Largeur de la fenetre
 * height: Hauteur de la fenetre
 */
void draw_init_menu_game(int width, int height);

/**
 * Dessine le goban
 * width: Largeur de la fenetre
 * height: Hauteur de la fenetre
 */
void draw_plateau(int width, int height);

/**
 * Verifie si un clic est en dehors du goban ou non
 * x: Position x du clic
 * y: Position y du clic
 */
bool checkBoundsGoban(int x, int y);

/**
 * S'occuppe du tour de jeu de l'IA
 * ligne: Position y ou la pierre sera placee
 * colonne: Position x ou la pierre sera placee
 */
bool playIA(int ligne, int colonne);

/**
 * Permet de savoir si c'est au tour de l'IA de jouer ou non
 */
void whoIsPlaying();

/**
 * Gere le rafraichissement d'affichage du goban apres un resize de la fenetre
 * width: Largeur de la fenetre
 * height: Hauteur de la fenetre
 */
void refresh_plateau(int width, int xheight);

/**
 * Gere la transition entre les fenetres
 * width: Largeur de la fenetre
 * height: Hauteur de la fenetre
 */
void refresh_manager(int width, int height);

/**
 * Reinitialise la partie si le joueur clique sur Rejouer en fin de partie
 */
void reinitDefaultValues();

/**
 * Retourne au menu de depart si le joueur clique sur Menu en fin de partie
 */
void backToMenu();

/**
 * Gere le clic sur le bouton Rejouer
 */
void rejouerGame();

/**
 * Gere le clic sur le bouton Nouvelle partie
 */
void newParty();

/**
 * Gere le clic sur le bouton Charger Partie
 */
void loadParty();

/**
 * Gere le clic sur les boutons de taille de goban
 */
void choixTaille();

/**
 * Gere le clic sur le bouton Goban 19x19
 */
void setGoban19();

/**
 * Gere le clic sur le bouton Goban 13x13
 */
void setGoban13();

/**
 * Gere le clic sur le bouton Goban 9x9
 */
void setGoban9();

/**
 * Gere le clic sur le bouton de changement d'adversaire
 */
void choixAdversaire();

/**
 * Gere la validation des parametres et lance la partie
 */
void validationAdversaire();

/**
 * Change l'adversaire du joueur 1 quand l'utilisateur clique sur le choix d'un adversaire
 */
void choixJoueur1();

/**
 * Change l'adversaire du joueur 2 quand l'utilisateur clique sur le choix d'un adversaire
 */
void choixJoueur2();

/**
 * Gere le clic sur la fenetre
 * bouton: le bouton appuye
 * x: Position x du clic
 * y: Position y du clic
 */
void mouse_clicked(int bouton, int x, int y);
