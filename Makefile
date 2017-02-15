VPATH= src/dessine src/file src/game src/menu src/
SRC = $(wildcard src/dessine/*.c src/file/*.c src/game/*.c src/menu/*.c src/jeu.c)
OBJ= $(notdir $(patsubst %.c,%.o,$(SRC)))
LDFLAGS = -lX11 -Wall

all: jeu

jeu: jeu.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

%.o: %.c
	gcc -c $< -I./header

clean:
	rm jeu *.o