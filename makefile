CFLAGS=-Wall -Wextra -pedantic -g -Wno-implicit-function-declaration -Wno-unused-parameter

SOURCES = hash.c

all: $(SOURCES)
	gcc $(CFLAGS) $^ -o main