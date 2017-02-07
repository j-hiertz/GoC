all: jeu

clean:
	rm jeu jeu.o menu.o goban.o intersection.o dessine.o chaine.o libdessine.a

jeu: jeu.o goban.o intersection.o pion.o menu.o file.o chaine.o chaine.h menu.h goban.h intersection.h dessine.h file.h boolean.h libdessine.a
	gcc -g -o jeu menu.o goban.o intersection.o pion.o file.o chaine.o jeu.o -L. -ldessine -lX11

jeu.o: jeu.c
	gcc -o jeu.o -c jeu.c

pion.o: pion.c
	gcc -o pion.o -c pion.c

menu.o: menu.c
	gcc -o menu.o -c menu.c

goban.o: goban.c
	gcc -o goban.o -c goban.c

intersection.o: intersection.c
	gcc -o intersection.o -c intersection.c

file.o: file.c
	gcc -o file.o -c file.c

chaine.o: chaine.c
	gcc -o chaine.o -c chaine.c

libdessine.a: dessine.c dessine.h
	gcc -g -c dessine.c
	ar -r libdessine.a dessine.o
