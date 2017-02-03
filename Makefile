all: jeu

clean:
	rm jeu jeu.o menu.o dessine.o libdessine.a

jeu: jeu.o menu.o menu.h dessine.h libdessine.a
	gcc -g -o jeu menu.o jeu.o -L. -ldessine -lX11

jeu.o: jeu.c
	gcc -o jeu.o -c jeu.c

menu.o: menu.c
	gcc -o menu.o -c menu.c

libdessine.a: dessine.c dessine.h
	gcc -g -c dessine.c
	ar -r libdessine.a dessine.o
