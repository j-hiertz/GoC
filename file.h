#include <stdlib.h>
#include <stdio.h>

FILE *createSGF(int);

void updateSGF(FILE*, char*);

void endGameSGF(FILE*, char*);

int getNbCaseFromFile(FILE*);