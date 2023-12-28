CCFLAGS = -Wall -lgmp -lm
DEBUGFLAGS = -g
CC = gcc



compile : main.c func.c calculations.c callfuncs.c
	$(CC) main.c func.c calculations.c callfuncs.c -o calc $(CCFLAGS)

debug : main.c func.c calculations.c callfuncs.c
	$(CC) main.c func.c calculations.c callfuncs.c -o calc $(CCFLAGS) $(DEBUGFLAGS)

clear-screen:
	clear

build: clear-screen compile
