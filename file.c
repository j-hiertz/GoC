#include "file.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

FILE *createSGF(int nbCase){
	time_t t = time(NULL);
	char date[20];
	strftime(date, 20, "%Y_%m_%d_%H_%M_%S", localtime(&t));

	printf("now %s\n", date);

	char nameFile[25];
	sprintf(nameFile, "save/game_%s.sgf", date);

	FILE *fp = fopen(nameFile, "w");

	if(fp == NULL) {
		exit(EXIT_FAILURE);
	}

	strftime(date, 20, "%Y-%m-%d", localtime(&t));

	// Indication :
	// FF[4] Norme 4 du sgf file
	// GM[1] Jeu de GO
	// SZ[19] Plateau de 19
	// US[Auteur]
	// GN[Nom du jeu]
	// PW[Nom joueur blanc]
	// PB[Nom du joueur noir]
	// RE[W+R] Resultat Blanc gagne par Resign R ou 3.5 9.5...
	// PC[Lieu de la partie]
	// DT[Date de la partie]
	// KM[Nombre de point] Komi (Compensation en point pour le joueur blanc)
	// B[dp]; Noir joue sur le case dp => 4:16 (0:13 dans le tableau)
	// W[ic]; Blanc joue sur le case ic => 9:3 (8:2 dans le tableau)
	fprintf(fp, "(;RE[W+R]FF[4]GM[1]SZ[%d]US[Mohamed Azzouz & Jordan Hiertz]GN[Go Go MoMo Game Desu]\n", nbCase);
	fprintf(fp, "PW[Joueur Blanc]PB[Joueur Noir]PC[CFAI Eckbolsheim]DT[%s]KM[0.5];)", date);

	return fp;
}

void updateSGF(FILE* file, char* str){

	if(file == NULL) {
		exit(EXIT_FAILURE);
	}

	// On se met a -1 pour supprimer la paranthèse
	fseek(file, -1, SEEK_END);
	fputs("\n", file);

	// On ajoute le coup
	fseek(file, 0, SEEK_END);
	fputs(str, file);

	// On supprime le dernier ";" et on ferme la paranthèse
	fseek(file, 0, SEEK_END);
	fputs(")", file);
}

void endGameSGF(FILE* file, char* str){

	if(file == NULL) {
		exit(EXIT_FAILURE);
	}

	// On se place au début du fichier et on supprime le résultat
	fseek(file, 0, SEEK_SET);
	fputs(str, file);

	fclose(file);
}