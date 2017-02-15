#ifndef BOOL_H
	#define BOOL_H
	#include "boolean.h"
#endif

/**
 * Type colorPion pour gérer les tours du jeu ou la couleurs des pions
 */
typedef enum { UNDEFINED, BLANC, NOIR} colorPion;


/**
 * Structure représentant un Pion
 * couleur: Répresente la couleur du pion posé
 */
typedef struct Pion Pion;
struct Pion{
	colorPion couleur;
};


/** 
 * Fonction d'initialisation mémoire d'un pion
 * color: La couleur du pion à initialisé
 */
Pion *initPion(colorPion color);
