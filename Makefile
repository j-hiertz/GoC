all: jeu

clean:
	rm jeu jeu.o menu.o goban.o intersection.o dessine.o libdessine.a

jeu: jeu.o goban.o intersection.o menu.o menu.h goban.h intersection.h dessine.h libdessine.a
	gcc -g -o jeu menu.o goban.o intersection.o jeu.o -L. -ldessine -lX11

jeu.o: jeu.c
	gcc -o jeu.o -c jeu.c

menu.o: menu.c
	gcc -o menu.o -c menu.c

goban.o: goban.c
	gcc -o goban.o -c goban.c

intersection.o: intersection.c
	gcc -o intersection.o -c intersection.c

libdessine.a: dessine.c dessine.h
	gcc -g -c dessine.c
	ar -r libdessine.a dessine.o
