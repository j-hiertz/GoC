#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../header/file.h"

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

FILE* saveGame(Goban* goban, FILE* file){
	
	printf("\n===== Sauvegarde de la partie =====\n");

	if(file == NULL) {

		// Creation du dossier save, si il existe la commande échoue
		mkdir("./save", 0755);

		// Génération du nom de fichier en fonction de la date
		time_t t = time(NULL);
		char date[20];
		strftime(date, 20, "%Y_%m_%d_%H_%M_%S", localtime(&t));

		printf("date : %s\n", date);

		char nameFile[25];
		sprintf(nameFile, "save/game_%s.sgf", date);

		file = fopen(nameFile, "w");

		if(file == NULL) {
			exit(EXIT_FAILURE);
		}

		strftime(date, 20, "%Y-%m-%d", localtime(&t));

		fprintf(file, "(;RE[W+R]FF[4]GM[1]SZ[%d]US[Mohamed Azzouz & Jordan Hiertz]GN[Go Go MoMo Game Desu]\n", goban->nbCase);
		fprintf(file, "PW[Joueur Blanc]PB[Joueur Noir]PC[CFAI Eckbolsheim]DT[%s]KM[0.5];)", date);

		printf("Fichier correctement créé\n");
	}

	return file;
}

void updateSGF(FILE* file, int colonne, int ligne, colorPion color){

	if(file == NULL) {
		printf("Update File : File not exist\n");
		exit(EXIT_FAILURE);
	}

	char coupStr[6];
	char pion;

	pion = (color == NOIR) ? 'B' : 'W';
	
	sprintf(coupStr, "%c[%c%c];", pion, colonne + 'a', ligne + 'a');

	printf("Enregistrement chaine : %s dans le fichier\n", coupStr);

	// On se met a -1 pour supprimer la paranthèse
	fseek(file, -1, SEEK_END);
	fputs("\n", file);

	// On ajoute le coup dans le fichier
	fseek(file, 0, SEEK_END);
	fputs(coupStr, file);

	// On supprime le dernier ";" et on ferme la paranthèse
	fseek(file, 0, SEEK_END);
	fputs(")", file);
}

// /home/jordan/GoC/save/game_2017_02_14_23_39_00.sgf
void createGameFromFile(FILE* file, Goban *goban, colorPion* tour) {

	char * line = NULL;
    size_t len = 0;
    ssize_t read;
    colorPion last;

    int i = 0;

    int ligne;
    int colonne;

    fseek(file, 0, SEEK_SET);
		
    while ((read = getline(&line, &len, file)) != -1) {

        if(i > 1) {

        	printf("Couleur : %c Colonne : %c Ligne : %c\n", line[0], line[2], line[3]);

        	colonne = line[2] - 'a';
        	ligne = line[3] - 'a';

        	Intersection* intersection = goban->intersections[ligne][colonne];

        	last = (line[0] == 'B') ? NOIR : BLANC;
        	intersection->pion = initPion(last);

        }
        i++;
    }

    *tour = (last == NOIR) ? BLANC : NOIR;
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

int getNbCaseFromFile(FILE* file) {

	char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int nCase = 19;

    read = getline(&line, &len, file);

    for(int i = 0; i < len - 1; i++){

    	if(line[i] == 'S' && line[i+1] == 'Z') {

    		if(line[i+3] == '9') {
    			nCase = 9;
    		}
    		else if(line[i+3] == '1'){

    			if(line[i+4] == '3') {
    				nCase = 13;
    			}
    		}

    		break;
    	}
    }

	return nCase;
}