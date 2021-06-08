CC=gcc
CFLAGS=-lm

all: lab2 lectura

lab2: lab2.c funciones.h
	$(CC) funciones.c lab2.c -o lab2 $(CFLAGS)

lectura: lectura.c funciones.h
	$(CC) funciones.c lectura.c -o lectura $(CFLAGS)
