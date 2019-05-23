CFLAGS=-Wall -Wextra -pedantic -g -Wno-implicit-function-declaration -Wno-unused-parameter

SOURCES = pile.c main.c file.c arbre.c

all: $(SOURCES)
	gcc $(CFLAGS) $^ -o main