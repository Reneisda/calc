CCFLAGS = -Wall -lgmp -lm -fopenmp
DEBUGFLAGS = -g
CC = gcc
WINCC = x86_64-w64-mingw32-gcc


make-dir:
	mkdir bin
compile : main.c func.c calculations.c callfuncs.c
	$(CC) main.c func.c calculations.c callfuncs.c -o bin/calc $(CCFLAGS)

compile-win:
	$(WINCC) main.c func.c calculations.c callfuncs.c -o bin/calc.exe -lm -lgmp

debug : main.c func.c calculations.c callfuncs.c
	$(CC) main.c func.c calculations.c callfuncs.c -o bin/calc $(CCFLAGS) $(DEBUGFLAGS)

clear-screen:
	clear

build: clear-screen compile
all: make-dir compile