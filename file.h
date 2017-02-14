#ifndef GOBAN_H
	#define GOBAN_H
	#include "goban.h"
#endif

FILE* saveGame(Goban*, FILE*, int);

void updateSGF(FILE*, int, int, colorPion);

void createGameFromFile(FILE*, Goban*);

void endGameSGF(FILE*, char*);

int getNbCaseFromFile(FILE*);