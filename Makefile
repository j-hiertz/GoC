all: jeu

clean:
	rm jeu jeu.o goban.o libdessine.a
	
jeu: jeu.o goban.o intersection.o dessine.h goban.h intersection.h libdessine.a
	gcc -g -o jeu goban.o intersection.o jeu.o -L. -ldessine -lX11

jeu.o : jeu.c
	gcc -o jeu.o -c jeu.c

goban.o: goban.c
	gcc -o goban.o -c goban.c

intersection.o: intersection.c
	gcc -o intersection.o -c intersection.c

libdessine.a: dessine.c dessine.h
	gcc -g -c dessine.c
	ar -r libdessine.a dessine.o
	
