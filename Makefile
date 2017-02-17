VPATH= src/dessine src/file src/game src/menu src/
SRC = $(wildcard src/dessine/*.c src/file/*.c src/game/*.c src/menu/*.c src/jeu.c)
SRCLIB = $(wildcard src/file/*.c src/game/*.c src/menu/*.c src/jeu.c)
OBJ= $(notdir $(patsubst %.c,%.o,$(SRC)))
OBJLIB= $(notdir $(patsubst %.c,%.o,$(SRCLIB)))
LDFLAGS = -lX11 -Wall
LDFLAGSLIBS = -Llib/ -lSDessine
LDFLAGSLIBD = -Llib/ -lDDessine

all: jeu jeuStatique jeuDynamique

jeu: $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

jeuStatique: $(OBJLIB) libSDessine.a
	gcc -o $@ $(OBJLIB) $(LDFLAGSLIBS) $(LDFLAGS)

jeuDynamique: $(OBJLIB) libDDessine.so
	gcc -o $@ $(OBJLIB) $(LDFLAGSLIBD) $(LDFLAGS)

libDDessine.so: dessine.o
	gcc -o lib/$@ -shared $^

libSDessine.a: dessine.o
	ar -rv lib/$@ $^

%.o: %.c
	gcc -c $< -I./header -fPIC
 

.PHONY: clean

clean:
	rm -rf jeu jeuStatique jeuDynamique *.o lib/*