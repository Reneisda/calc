CCFLAGS = -Wall -lgmp -lm -fopenmp -lOpenCL
OPT = -O3
DEBUGFLAGS = -g
CC = gcc
WINCC = x86_64-w64-mingw32-gcc


make-dir:
	mkdir bin
bin/calc : main.c func.c calculations.c callfuncs.c vector.c matrix.c
	$(CC) main.c func.c calculations.c callfuncs.c vector.c matrix.c -o bin/calc $(CCFLAGS) $(OPT)

compile-win:
	$(WINCC) main.c func.c calculations.c callfuncs.c -o bin/calc.exe -lm -lgmp

debug : main.c func.c calculations.c callfuncs.c vector.c matrix.c
	$(CC) main.c func.c calculations.c callfuncs.c vector.c matrix.c -o bin/calc $(CCFLAGS) $(DEBUGFLAGS)
gpu_ac : gpu_accel.c
	$(CC) gpu_accel.c -o bin/gpu_fac -lOpenCL

clear-screen:
	clear

build: clear-screen bin/calc
all: make-dir bin/calc