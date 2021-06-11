CC=gcc
CFLAGS=-lm

all: lab2 lectura zoom suavizado rotacion

lab2: lab2.c funciones.h
	$(CC) funciones.c lab2.c -o lab2 $(CFLAGS)

lectura: lectura.c funciones.h
	$(CC) funciones.c lectura.c -o lectura $(CFLAGS)

zoom: zoom.c funciones.h
	$(CC) funciones.c zoom.c -o zoom $(CFLAGS)

suavizado: suavizado.c funciones.h
	$(CC) funciones.c suavizado.c -o suavizado $(CFLAGS)

rotacion: rotacion.c funciones.h
	$(CC) funciones.c rotacion.c -o rotacion $(CFLAGS)
